import logging
import psutil
import subprocess
from chttp import http_response, render


def server_status(**args):
    pid, port = args['pid'], args['port']
    process = psutil.Process(pid)
    mem_in_bytes = process.memory_info().rss
    mem_in_mb = round(mem_in_bytes / 1024 / 1024, 2)
    cpu = process.cpu_percent()
    # conns = len(process.connections()) - 1
    conn_cmd = f'netstat -an | grep {port} | wc -l'
    conn_res = subprocess.check_output(conn_cmd, shell=True)
    # conns = int(conn_res.decode())
    threads = process.num_threads()
    pchildren = process.children()

    # count active conns
    conns = 0
    for p in pchildren:
        try:
            conns += len(p.connections())
        except Exception as e:
            logging.error(e)
    print(conns)

    children = len(pchildren)
    ctx_switches = process.num_ctx_switches()

    tmpl_args = {
        'pid': pid,
        'cpu': f'{cpu}%',
        'mem': f'{mem_in_mb}MB',
        'conns': conns,
        'children': children,
        'threads': threads,
        'ctx_switches': ctx_switches
    }
    resp_body = render('status.html', tmpl_args)
    return http_response(resp_body)


def index(**_):
    return http_response('Hello, world!')


def handle(url_path: dict, **args):
    handlers = {
        '/': index,
        '/status': server_status,
        '/status/': server_status
    }
    try:
        return handlers[url_path](**args)
    except KeyError:
        return index(**args)
