import argparse
import multiprocessing
import socket
import time

from chttp import parse_resp_header
from utils import logging


TIMEOUT = 30  # 30 seconds operation timeout
FAILED = -1


NONSENSE = (
    'hi',
    'what',
    'ever',
    'does',
    'not',
    'matter',
    'i\'m a long message',
    'i\'m a super loooooooooooooooooooooooooooong message',
)


def send_request(request_id):
    HOST, PORT = 'c10k.test', 8000

    start = time.time()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(TIMEOUT)
    try:
        http_header_lines = (
            'GET /test HTTP/1.1',
            f'Host: {HOST}:{PORT}',
            'Connection: keep-alive',
            'User-Agent: C10K Client',
            'Accept: text/html',
            '\r\n'
        )
        http_req = '\r\n'.join(http_header_lines)

        data = http_req.encode()

        s.connect((HOST, PORT))
        s.sendall(data)
        reply = s.recv(65535)

        print(f'{request_id}: {parse_resp_header(reply.decode())}')

        finish = time.time()
        response_time = finish - start

        return response_time
    except Exception as e:
        logging.error(e)
        return FAILED
    finally:
        s.close()


def main():
    argparser = argparse.ArgumentParser()
    argparser.add_argument('requests', type=int,
                           help='Total number of requests')
    argparser.add_argument('--workers', type=int, default=1,
                           help=('Number of workers to generate requests in '
                                 'parallel'))
    args = argparser.parse_args()
    workers = multiprocessing.Pool(args.workers)

    start = time.time()
    results = []
    for i in range(args.requests):
        workers.apply_async(send_request, args=(i,), callback=results.append)
    workers.close()
    workers.join()
    finish = time.time()

    succeeds = [i for i in results if i >= 0]
    errors = [i for i in results if i < 0]
    overall = sum(succeeds)
    if succeeds:
        avg = overall / len(succeeds) * 1000  # in ms.
    else:
        avg = 0
    time_spent = finish - start
    rps = args.requests / time_spent

    msg = ('\nErrors: %s, Succeeds: %s\n'
           'Response time (avg.): %s ms\n'
           'Requests per second (avg.): %s req/s\n'
           'Time spent: %s s')
    msg = msg % (len(errors), len(succeeds), avg, rps, time_spent)
    print(msg)


if __name__ == '__main__':
    main()
