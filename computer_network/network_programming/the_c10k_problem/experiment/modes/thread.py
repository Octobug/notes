import threading
import socket
from .conn import handle_conn_block


def thread_server(s: socket.socket):
    class HTTPThread (threading.Thread):
        def __init__(self, id, conn, addr):
            threading.Thread.__init__(self)
            self.id = id
            self.conn = conn
            self.addr = addr

        def run(self):
            handle_conn_block(self.conn, self.addr, True)

    children = []
    tid = 0
    try:
        while True:
            conn, addr = s.accept()
            t = HTTPThread(tid, conn, addr)
            t.start()
            children.append(t)
            tid += 1
    finally:
        for t in children:
            if t.is_alive():
                t.conn.close()
                t.join()
