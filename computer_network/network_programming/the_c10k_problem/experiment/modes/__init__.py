SINGLE = 'single'
PROCESS = 'process'
THREAD = 'thread'
SELECT = 'select'
POLL = 'poll'
EPOLL = 'epoll'
KQUEUE = 'kqueue'
SIGNAL = 'signal'
ASYNC = 'async'

ALL = (SINGLE, PROCESS, THREAD, SELECT, POLL, EPOLL, KQUEUE, SIGNAL, ASYNC)
NONBLOCKINGS = ALL[3:]
