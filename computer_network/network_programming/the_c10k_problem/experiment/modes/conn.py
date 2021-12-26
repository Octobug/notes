import logging
import socket
from chttp import http_recv, http_req_path
from router import route


def handle_request(req_str):
    http_path = http_req_path(req_str)
    return route(http_path)


def handle_conn(conn: socket.socket, addr):
    logging.debug(f'new client: {addr[0]}:{addr[1]}')
    req_str = http_recv(conn)
    logging.debug(req_str)

    http_resp = handle_request(req_str)
    conn.sendall(http_resp.encode())


def queued_handle_conn(queue):
    while True:
        conn, addr = queue.get()
        handle_conn(conn, addr)
