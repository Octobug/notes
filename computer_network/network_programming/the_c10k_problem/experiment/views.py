import logging
import psutil
import subprocess
from chttp import http_response, render


def get_process_info(pid, port):
    process = psutil.Process(pid)
    pchildren = process.children()
    mem_in_bytes = process.memory_info().rss
    conns = len(process.connections())

    for p in pchildren:
        try:
            conns += len(p.connections())
            mem_in_bytes += p.memory_info().rss
        except Exception as e:
            logging.error(e)

    mem_in_mb = round(mem_in_bytes / 1024 / 1024, 2)
    cpu_times = process.cpu_times()
    cpu = (cpu_times.user + cpu_times.system +
           cpu_times.children_user + cpu_times.children_system)
    conn_cmd = f'netstat -an | grep {port} | wc -l'
    conn_res = subprocess.check_output(conn_cmd, shell=True)
    # conns = int(conn_res.decode())
    threads = process.num_threads()
    children = len(pchildren)
    ctx_switches = process.num_ctx_switches()

    info = {
        'pid': pid,
        'cpu': f'{round(cpu, 2)}s',
        'mem': f'{mem_in_mb}MB',
        'conns': conns,
        'children': children,
        'threads': threads,
        'ctx_switches': ctx_switches
    }

    return info


def server_status(**args):
    pid, port = args['pid'], args['port']
    proc_info = get_process_info(pid, port)

    resp_body = render('status.html', proc_info)
    return http_response(resp_body)


def index(**_):
    return http_response('Hello, world!')


def test(**_):
    return 'short_str'


def handle(url_path: dict, **args):
    handlers = {
        '/': index,
        '/test': test,
        '/status': server_status,
        '/status/': server_status
    }
    try:
        return handlers[url_path](**args)
    except KeyError:
        return index(**args)
