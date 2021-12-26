import logging
import sys


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def set_logging(verbose=4):
    if verbose == 1:
        level = logging.FATAL
    elif verbose == 2:
        level = logging.ERROR
    elif verbose == 3:
        level = logging.WARN
    elif verbose == 5:
        level = logging.DEBUG
    else:
        level = logging.INFO

    logging.basicConfig(format='[%(asctime)s][%(levelname)s] %(message)s',
                        datefmt='%Y/%m/%d %H:%M:%S',
                        level=level)
