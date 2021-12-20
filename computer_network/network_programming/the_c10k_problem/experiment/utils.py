import sys
import logging


__all__ = ['eprint', 'logging']


logging.basicConfig(format='[%(asctime)s][%(levelname)s] %(message)s',
                    datefmt='%Y/%m/%d %H:%M:%S',
                    level=logging.DEBUG)


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)
