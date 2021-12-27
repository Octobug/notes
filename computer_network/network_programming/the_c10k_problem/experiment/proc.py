import logging
import os
import subprocess
import psutil

import config

PID = os.getpid()


def get_process_info():
    process = psutil.Process(PID)
    pchildren = process.children()
    mem_in_bytes = process.memory_info().rss
    conns = len(process.connections())

    for p in pchildren:
        try:
            conns += len(p.connections())
            mem_in_bytes += p.memory_info().rss
        except Exception as e:
            logging.error(f'get_process_info: {e}')

    mem_in_mb = round(mem_in_bytes / 1024 / 1024, 2)
    cpu_times = process.cpu_times()
    cpu = (cpu_times.user + cpu_times.system +
           cpu_times.children_user + cpu_times.children_system)
    conn_cmd = f'netstat -an | grep {config.PORT} | wc -l'
    conn_res = subprocess.check_output(conn_cmd, shell=True)
    # conns = int(conn_res.decode())
    threads = process.num_threads()
    children = len(pchildren)
    ctx_switches = process.num_ctx_switches()
    loadavg = os.getloadavg()

    info = {
        'pid': PID,
        'loadavg': loadavg,
        'cpu': f'{round(cpu, 2)}s',
        'mem': f'{mem_in_mb}MB',
        'conns': conns,
        'children': children,
        'threads': threads,
        'ctx_switches': ctx_switches
    }

    return info
