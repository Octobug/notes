import argparse
import multiprocessing
import threading
import os
import select
import socket
import sys
from utils import eprint, get_logger
from chttp import parse_request
from views import handle


conn_refs = []

PID = os.getpid()
HOST = '0.0.0.0'
PORT = 8000


class D2C():
    def __init__(self, modes):
        for key in modes:
            setattr(self, key, modes[key])


MODES = {
    'SINGLE': 'single',
    'PROCESS': 'process',
    'THREAD': 'thread',
    'SELECT': 'select',
    'POLL': 'poll',
    'EPOLL': 'epoll',
    'SIGNAL': 'signal',
    'ASYNC': 'async'
}


MODE_LIST = tuple(MODES.values())
MODE = D2C(MODES)
DOMAIN = 'c10k.test'


def get_s_key(addr):
    return f'{addr[0]}:{addr[1]}'


def handle_request(req_str):
    http_req = parse_request(req_str)
    logger.info(f'{http_req["method"]} {http_req["path"]}')
    return handle(http_req['path'], pid=PID, port=PORT)


def save_conn_ref(conn):
    conn_refs.append(conn)


def handle_read(conn: socket.socket, addr, results: dict):
    logger.info(f'new client: {get_s_key(addr)}')
    max_header_size = 65535
    req_bytes = conn.recv(max_header_size)
    req_str = req_bytes.decode()

    logger.debug(req_str)

    http_resp = handle_request(req_str)
    results[get_s_key(addr)] = http_resp


def handle_write(conn: socket.socket, addr, results: dict):
    try:
        http_resp = results[get_s_key(addr)]
        conn.sendall(http_resp.encode())
        del results[get_s_key(addr)]
        # save_conn_ref(conn)
        conn.close()
    except KeyError:
        pass


def handle_conn(conn: socket.socket, addr):
    logger.info(f'new client: {addr[0]}:{addr[1]}')
    max_header_size = 65535
    req_bytes = conn.recv(max_header_size)
    req_str = req_bytes.decode()

    logger.debug(req_str)

    http_resp = handle_request(req_str)
    conn.sendall(http_resp.encode())

    # save_conn_ref(conn)
    conn.close()


def queued_handle_conn(queue):
    while True:
        conn, addr = queue.get()
        handle_conn(conn, addr)


def select_server(s_main, timeout=1, use_worker=False):
    '''Single process select() with non-blocking accept() and recv().'''
    inputs = []
    outputs = []
    peers = []

    try:
        max_peers = 0

        if use_worker:
            queue = multiprocessing.Queue()
            worker = multiprocessing.Process(target=queued_handle_conn,
                                             args=(queue,))
            worker.start()

        while True:
            max_peers = max(max_peers, len(peers))
            reads, _w, _e = select.select(
                peers + [s_main], [], [], timeout
            )

            for s in reads:
                if s is s_main:
                    while True:
                        try:
                            conn, addr = s_main.accept()
                            conn.setblocking(0)

                            peers.append(conn)
                        except Exception:
                            break
                else:
                    peers.remove(s)
                    conn, addr = s, s.getpeername()

                    if use_worker:
                        queue.put((conn, addr))
                    else:
                        handle_conn(conn, addr)
                        # handle_read(conn, addr, results)
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()

        print(f'Max. number of connections: {max_peers}')


def poll_server(s_main, timeout=1, use_worker=False):
    '''Single process poll() with non-blocking accept() and recv().'''
    peers = {}  # {fileno: socket}
    flag = (select.POLLIN |
            select.POLLERR |
            select.POLLHUP)

    try:
        max_peers = 0

        if use_worker:
            queue = multiprocessing.Queue()
            worker = multiprocessing.Process(target=queued_handle_conn,
                                             args=(queue,))
            worker.start()

        poll = select.poll()
        poll.register(s_main, select.POLLIN)
        while True:
            max_peers = max(max_peers, len(peers))
            actionable = poll.poll(timeout)

            for fd, event in actionable:
                if fd == s_main.fileno():
                    while True:
                        try:
                            conn, addr = s_main.accept()
                            conn.setblocking(0)

                            peers[conn.fileno()] = conn
                            poll.register(conn, flag)
                        except Exception:
                            break

                elif event & select.POLLIN:
                    poll.unregister(fd)
                    conn, addr = peers[fd], peers[fd].getpeername()

                    if use_worker:
                        queue.put((conn, addr))
                    else:
                        handle_conn(conn, addr)

                elif event & select.POLLERR or event & select.POLLHUP:
                    poll.unregister(fd)
                    peers[fd].close()
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()

        print(f'Max. number of connections: {max_peers}')


def epoll_server(s_main, timeout=1, use_worker=False):
    '''Single process epoll() with non-blocking accept() and recv().'''
    peers = {}  # {fileno: socket}
    flag = (select.EPOLLIN |
            select.EPOLLET |
            select.EPOLLERR |
            select.EPOLLHUP)

    try:
        max_peers = 0

        if use_worker:
            queue = multiprocessing.Queue()
            worker = multiprocessing.Process(target=queued_handle_conn,
                                             args=(queue,))
            worker.start()

        epoll = select.epoll()
        epoll.register(s_main, select.EPOLLIN | select.EPOLLET)
        while True:
            max_peers = max(max_peers, len(peers))
            actionable = epoll.poll(timeout=timeout)

            for fd, event in actionable:
                if fd == s_main.fileno():
                    while True:
                        try:
                            conn, addr = s_main.accept()
                            conn.setblocking(0)

                            peers[conn.fileno()] = conn
                            epoll.register(conn, flag)
                        except Exception:
                            break

                elif event & select.EPOLLIN:
                    epoll.unregister(fd)
                    conn, addr = peers[fd], peers[fd].getpeername()

                    if use_worker:
                        queue.put((conn, addr))
                    else:
                        handle_conn(conn, addr)

                elif event & select.EPOLLERR or event & select.EPOLLHUP:
                    epoll.unregister(fd)
                    peers[fd].close()
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()
        epoll.close()

        print(f'Max. number of connections: {max_peers}')


def thread_server(s: socket.socket):
    class TCPThread (threading.Thread):
        def __init__(self, id, conn, addr):
            threading.Thread.__init__(self)
            self.id = id
            self.conn = conn
            self.addr = addr

        def run(self):
            handle_conn(self.conn, self.addr)

    children = []
    try:
        tid = 0
        while True:
            tid += 1
            conn, addr = s.accept()

            t = TCPThread(tid, conn, addr)
            t.start()

            children.append(t)
    finally:
        [t.join() for t in children if t.is_alive()]


def process_server(s: socket.socket):
    children = []
    try:
        while True:
            conn, addr = s.accept()

            p = multiprocessing.Process(target=handle_conn, args=(conn, addr))
            p.start()
            children.append(p)
    finally:
        [p.terminate() for p in children if p.is_alive()]


def single_server(s: socket.socket):
    while True:
        conn, addr = s.accept()
        handle_conn(conn, addr)


def run_server(host, port, args):
    timeout = args.timeout / 1000
    # TCP socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 允许重用被 TIME_WAIT TCP 占用的地址
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    if args.mode in (MODE.SELECT, MODE.POLL, MODE.EPOLL):
        s.setblocking(False)

    try:
        s.bind((host, port))
        s.listen(args.backlog)
        logger.info(f'listening on {host}:{port}')
        logger.info(f'open in browser: http://{DOMAIN}:{port}')

        if args.mode == MODE.SINGLE:
            single_server(s)
        elif args.mode == MODE.PROCESS:
            process_server(s)
        elif args.mode == MODE.THREAD:
            thread_server(s)
        elif args.mode == MODE.SELECT:
            select_server(s, timeout, use_worker=args.worker)
        elif args.mode == MODE.POLL:
            poll_server(s, timeout, use_worker=args.worker)
        elif args.mode == MODE.EPOLL:
            epoll_server(s, timeout, use_worker=args.worker)
    except KeyboardInterrupt:
        pass
    finally:
        s.close()


def set_args():
    argparser = argparse.ArgumentParser()
    argparser.add_argument('mode', help=('Operating mode of the server: %s'
                                         % ', '.join(MODE_LIST)))
    argparser.add_argument('--backlog', type=int, default=0,
                           help='socket.listen() backlog')
    argparser.add_argument('--timeout', type=int, default=1000,
                           help='select/poll/epoll timeout in ms')
    argparser.add_argument('--verbose', type=int, default=4,
                           help=('logger level'
                                 '1: FATAL'
                                 '2: ERROR'
                                 '3: WARNING'
                                 '4: INFO'
                                 '5: DEBUG'))
    argparser.add_argument('--worker', action='store_true',
                           help=('spawn a worker to process request in '
                                 'select/poll/epoll mode. '
                                 'NOTE: The sole purpose of this option is '
                                 'experiment, it does not really help shorten '
                                 'the response time.'))
    return argparser.parse_args()


def main():
    args = set_args()

    if args.mode not in MODE_LIST:
        errmsg = 'Availble operating modes: %s' % ', '.join(MODE_LIST)
        eprint(errmsg)
        sys.exit(1)

    global logger
    logger = get_logger(args.verbose)

    logger.info(f'mode: {args.mode}')
    run_server(HOST, PORT, args)


if __name__ == '__main__':
    main()
