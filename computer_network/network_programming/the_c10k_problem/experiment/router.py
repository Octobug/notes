import logging
from views import index, c10k, server_status


def route(url_path):
    logging.debug(f'url path: {url_path}')
    handlers = {
        '/': index,
        '/c10k': c10k,
        '/status': server_status,
        '/status/': server_status
    }
    try:
        return handlers[url_path]()
    except KeyError:
        return index()
