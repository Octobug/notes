import email
import logging
import socket
from io import StringIO
from cerror import EOFError


def parse_req_header(request: str):
    if not len(request):
        raise EOFError('request is EOF')
    first_line, headers = request.split('\r\n', 1)

    # construct a message from the request string
    message = email.message_from_file(StringIO(headers))

    # construct a dictionary containing the headers
    headers = dict(message.items())

    method, path, _ = first_line.split(' ')
    headers['method'] = method
    headers['path'] = path

    return headers


def parse_resp_header(response: str):
    _, body = response.split('\r\n\r\n')
    return body


def http_response(body: str):
    header = ('HTTP/1.1 200 OK\r\n'
              'Server: C10K Server\r\n'
              'Accept-Ranges: bytes\r\n'
              'Vary: Accept-Encoding\r\n'
              f'Content-Length: {len(body)}\r\n'
              'Keep-Alive: timeout=15, max=99\r\n'
              'Connection: Keep-Alive\r\n'
              'Content-Type: text/html; charset=utf-8\r\n'
              '\r\n')
    return header + body


def http_recv(conn: socket.socket):
    buf_size = 1024
    req_str = ''
    while True:
        req_bytes = conn.recv(buf_size)
        logging.debug(f'bytes: {len(req_bytes)}')
        if req_bytes:
            req_str += req_bytes.decode()
            if req_str.endswith('\r\n\r\n'):
                break
            if len(req_bytes) < buf_size:
                break
        else:
            break

    return req_str


def http_req_path(req_str):
    req_header = parse_req_header(req_str)
    logging.info(f'{req_header["method"]} {req_header["path"]}')
    logging.debug(req_header)
    return req_header['path']
