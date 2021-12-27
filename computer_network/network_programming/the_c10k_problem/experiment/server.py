import argparse
import logging
import socket
import sys
# custom libs
import config
import modes
from modes.single import single_server
from modes.process import process_server
from modes.thread import thread_server
from modes.select import select_server
from modes.poll import poll_server
from modes.epoll import epoll_server
from utils import eprint, set_logging


conn_refs = []


def save_conn_ref(conn):
    conn_refs.append(conn)


def run_server(host, port, args):
    timeout = args.timeout / 1000
    # TCP socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 允许重用被 TIME_WAIT TCP 占用的地址
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    if args.mode in modes.NONBLOCKINGS:
        s.setblocking(False)

    try:
        s.bind((host, port))
        s.listen(args.backlog)
        logging.info(f'listening on {host}:{port}')
        logging.info(f'open in browser: http://{config.DOMAIN}:{port}')

        if args.mode == modes.SINGLE:
            single_server(s)
        elif args.mode == modes.PROCESS:
            process_server(s)
        elif args.mode == modes.THREAD:
            thread_server(s)
        elif args.mode == modes.SELECT:
            select_server(s, timeout, use_worker=args.worker)
        elif args.mode == modes.POLL:
            poll_server(s, timeout, use_worker=args.worker)
        elif args.mode == modes.EPOLL:
            epoll_server(s, timeout, use_worker=args.worker)
    except KeyboardInterrupt:
        pass
    finally:
        s.close()


def set_args():
    argparser = argparse.ArgumentParser()
    argparser.add_argument(
        'mode', help=(
            'Operating mode of the server: %s'
            % ', '.join(modes.ALL)
        )
    )
    argparser.add_argument(
        '--backlog', type=int, default=0,
        help='socket.listen() backlog')
    argparser.add_argument(
        '--timeout', type=int, default=1000,
        help=f'{"/".join(modes.NONBLOCKINGS)} timeout in ms'
    )
    argparser.add_argument(
        '--verbose', type=int, default=4,
        help=(
            '''
            logging level
            1: FATAL
            2: ERROR
            3: WARNING
            4: INFO
            5: DEBUG
            '''
        )
    )
    argparser.add_argument(
        '--worker', action='store_true',
        help=('spawn a worker to process request in '
              f'{"/".join(modes.NONBLOCKINGS)} mode. '
              'NOTE: The sole purpose of this option is '
              'experiment, it does not really help shorten '
              'the response time.')
    )
    return argparser.parse_args()


def main():
    args = set_args()
    set_logging(args.verbose)

    if args.mode not in modes.ALL:
        errmsg = 'Availble operating modes: %s' % ', '.join(modes.ALL)
        eprint(errmsg)
        sys.exit(1)

    global logging
    logging.info(f'mode: {args.mode}')
    run_server(config.HOST, config.PORT, args)


if __name__ == '__main__':
    main()
