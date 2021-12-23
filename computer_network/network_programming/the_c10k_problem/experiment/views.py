import os
import psutil
from chttp import http_response, render


def server_status():
    pid = os.getpid()
    process = psutil.Process(pid)
    mem_in_bytes = process.memory_info().rss
    mem_in_mb = round(mem_in_bytes / 1024 / 1024, 2)
    cpu = process.cpu_percent()
    conns = len(process.connections()) - 1
    threads = process.num_threads()
    children = len(process.children())
    ctx_switchs = process.num_ctx_switches()

    tmpl_args = {
        'pid': pid,
        'cpu': f'{cpu}%',
        'mem': f'{mem_in_mb}MB',
        'conns': conns,
        'children': children,
        'threads': threads,
        'ctx_switchs': ctx_switchs
    }
    resp_body = render('status.html', tmpl_args)
    return http_response(resp_body)


def index():
    return http_response('Hello, world!')


def handle(url_path: dict):
    handlers = {
        '/': index,
        '/status': server_status,
        '/status/': server_status
    }
    try:
        return handlers[url_path]()
    except KeyError:
        return index()
