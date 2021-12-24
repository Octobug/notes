import argparse
import multiprocessing
import select
import socket
import sys
from utils import eprint, get_logger
from chttp import parse_request
from views import handle


# conn_baks = []

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


def handle_request(req_str):
    http_req = parse_request(req_str)
    logger.info(f'{http_req["method"]} {http_req["path"]}')
    return handle(http_req['path'])


def handle_conn(conn: socket.socket, addr):
    logger.info(f'new client: {addr[0]}:{addr[1]}')
    chunk_size = 1024
    req_str = ''
    while True:
        tmp_bytes = conn.recv(chunk_size)
        req_str += tmp_bytes.decode()
        if req_str.endswith('\r\n\r\n'):
            break

    logger.debug(req_str)

    http_resp = handle_request(req_str)
    conn.sendall(http_resp.encode())
    # conn_baks.append(conn)
    conn.close()


def queued_handle_conn(queue):
    while True:
        conn, addr = queue.get()
        handle_conn(conn, addr)


def select_server(socket_, timeout=1, use_worker=False):
    '''Single process select() with non-blocking accept() and recv().'''
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
            readable, w, e = select.select(peers + [socket_], [], [], timeout)

            for s in readable:
                if s is socket_:
                    while True:
                        try:
                            conn, addr = socket_.accept()
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
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()

        print(f'Max. number of connections: {max_peers}')


def poll_server(socket_, timeout=1, use_worker=False):
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
        poll.register(socket_, select.POLLIN)
        while True:
            max_peers = max(max_peers, len(peers))
            actionable = poll.poll(timeout)

            for fd, event in actionable:
                if fd == socket_.fileno():
                    while True:
                        try:
                            conn, addr = socket_.accept()
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


def epoll_server(socket_, timeout=1, use_worker=False):
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
        epoll.register(socket_, select.EPOLLIN | select.EPOLLET)
        while True:
            max_peers = max(max_peers, len(peers))
            actionable = epoll.poll(timeout=timeout)

            for fd, event in actionable:
                if fd == socket_.fileno():
                    while True:
                        try:
                            conn, addr = socket_.accept()
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


def process_server(s: socket.socket):
    child = []
    try:
        while True:
            conn, addr = s.accept()

            p = multiprocessing.Process(target=handle_conn, args=(conn, addr))
            p.start()
            child.append(p)
    finally:
        [p.terminate() for p in child if p.is_alive()]


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
        elif args.mode == 'select':
            select_server(s, timeout, use_worker=args.worker)
        elif args.mode == 'poll':
            poll_server(s, timeout, use_worker=args.worker)
        elif args.mode == 'epoll':
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
    HOST = '0.0.0.0'
    PORT = 8000

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
