import multiprocessing
import select

from conn import handle_conn, queued_handle_conn


def poll_server(s_main, timeout=1, use_worker=False):
    '''Single process poll() with non-blocking accept() and recv().'''
    peers = {}
    flag = (select.POLLIN |
            select.POLLERR |
            select.POLLHUP)

    try:
        max_peers = 0

        if use_worker:
            queue = multiprocessing.Queue()
            worker = multiprocessing.Process(target=queued_handle_conn,
                                             args=(queue,))
            worker.start()

        poll = select.poll()
        poll.register(s_main, select.POLLIN)
        while True:
            max_peers = max(max_peers, len(peers))
            actionable = poll.poll(timeout)

            for fd, event in actionable:
                if fd == s_main.fileno():
                    while True:
                        try:
                            conn, addr = s_main.accept()
                            conn.setblocking(0)

                            peers[conn.fileno()] = conn
                            poll.register(conn, flag)
                        except Exception:
                            break

                elif event & select.POLLIN:
                    poll.unregister(fd)
                    conn, addr = peers[fd], peers[fd].getpeername()

                    if use_worker:
                        queue.put((conn, addr))
                    else:
                        handle_conn(conn, addr)

                elif event & select.POLLERR or event & select.POLLHUP:
                    poll.unregister(fd)
                    peers[fd].close()
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()

        print(f'Max. number of connections: {max_peers}')
