import proc
from chttp import http_response
from chtml import render


def server_status():
    proc_info = proc.get_process_info()
    resp_body = render('chtml/status.html', proc_info)
    return http_response(resp_body)


def index():
    return http_response('Hello, world!')


def c10k():
    resp_body = render('chtml/c10k.html')
    return http_response(resp_body)
