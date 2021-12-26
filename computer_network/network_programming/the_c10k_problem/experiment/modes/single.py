import socket
from .conn import handle_conn_block


def single_server(s: socket.socket):
    while True:
        conn, addr = s.accept()
        handle_conn_block(conn, addr)
        conn.close()
