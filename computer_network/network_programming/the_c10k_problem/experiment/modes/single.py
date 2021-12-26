import socket
from .conn import handle_conn


def single_server(s: socket.socket):
    while True:
        conn, addr = s.accept()
        handle_conn(conn, addr)
        conn.close()
