import multiprocessing
import select

from conn import handle_conn, queued_handle_conn


def select_server(s_main, timeout=1, use_worker=False):
    '''Single process select() with non-blocking accept() and recv().'''
    peers = []

    try:
        max_peers = 0

        if use_worker:
            queue = multiprocessing.Queue()
            worker = multiprocessing.Process(target=queued_handle_conn,
                                             args=(queue,))
            worker.start()

        while True:
            max_peers = max(max_peers, len(peers))
            reads, _w, _e = select.select(
                peers + [s_main], [], [], timeout
            )

            for s in reads:
                if s is s_main:
                    while True:
                        try:
                            conn, addr = s_main.accept()
                            conn.setblocking(0)

                            peers.append(conn)
                        except Exception:
                            break
                else:
                    peers.remove(s)
                    conn, addr = s, s.getpeername()

                    if use_worker:
                        queue.put((conn, addr))
                    else:
                        handle_conn(conn, addr)
                        # handle_read(conn, addr, results)
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()

        print(f'Max. number of connections: {max_peers}')
