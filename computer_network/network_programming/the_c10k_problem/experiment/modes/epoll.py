import select
import multiprocessing

from conn import handle_conn, queued_handle_conn


def epoll_server(s_main, timeout=1, use_worker=False):
    '''Single process epoll() with non-blocking accept() and recv().'''
    peers = {}  # {fileno: socket}
    flag = (select.EPOLLIN |
            select.EPOLLET |
            select.EPOLLERR |
            select.EPOLLHUP)

    try:
        max_peers = 0

        if use_worker:
            queue = multiprocessing.Queue()
            worker = multiprocessing.Process(target=queued_handle_conn,
                                             args=(queue,))
            worker.start()

        epoll = select.epoll()
        epoll.register(s_main, select.EPOLLIN | select.EPOLLET)
        while True:
            max_peers = max(max_peers, len(peers))
            actionable = epoll.poll(timeout=timeout)

            for fd, event in actionable:
                if fd == s_main.fileno():
                    while True:
                        try:
                            conn, addr = s_main.accept()
                            conn.setblocking(0)

                            peers[conn.fileno()] = conn
                            epoll.register(conn, flag)
                        except Exception:
                            break

                elif event & select.EPOLLIN:
                    epoll.unregister(fd)
                    conn, addr = peers[fd], peers[fd].getpeername()

                    if use_worker:
                        queue.put((conn, addr))
                    else:
                        handle_conn(conn, addr)

                elif event & select.EPOLLERR or event & select.EPOLLHUP:
                    epoll.unregister(fd)
                    peers[fd].close()
    finally:
        if use_worker and worker.is_alive():
            worker.terminate()
        epoll.close()

        print(f'Max. number of connections: {max_peers}')
