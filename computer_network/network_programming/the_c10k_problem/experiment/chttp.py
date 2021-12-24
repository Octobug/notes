import email
from io import StringIO


def parse_request(request: str):
    first_line, headers = request.split('\r\n', 1)

    # construct a message from the request string
    message = email.message_from_file(StringIO(headers))

    # construct a dictionary containing the headers
    headers = dict(message.items())

    method, path, _ = first_line.split(' ')
    headers['method'] = method
    headers['path'] = path

    return headers


def parse_response(response: str):
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


def render(tmpl_path, data):
    with open(tmpl_path, 'r') as f:
        tmpl = f.read()

    return tmpl.format(**data)
