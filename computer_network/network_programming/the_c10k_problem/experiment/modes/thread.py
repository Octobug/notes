import threading
import socket
from conn import handle_conn


def thread_server(s: socket.socket):
    class TCPThread (threading.Thread):
        def __init__(self, id, conn, addr):
            threading.Thread.__init__(self)
            self.id = id
            self.conn = conn
            self.addr = addr

        def run(self):
            handle_conn(self.conn, self.addr)

    children = []
    try:
        tid = 0
        while True:
            tid += 1
            conn, addr = s.accept()

            t = TCPThread(tid, conn, addr)
            t.start()

            children.append(t)
    finally:
        [t.join() for t in children if t.is_alive()]
