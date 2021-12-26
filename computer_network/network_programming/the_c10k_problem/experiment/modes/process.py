import multiprocessing
import socket
from .conn import handle_conn_block


def process_server(s: socket.socket):
    children = []
    try:
        while True:
            conn, addr = s.accept()
            p = multiprocessing.Process(
                target=handle_conn_block, args=(conn, addr, True)
            )
            p.start()
            children.append(p)
    finally:
        [p.terminate() for p in children if p.is_alive()]
