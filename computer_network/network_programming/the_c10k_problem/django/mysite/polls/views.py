import time
from django.http import HttpResponse


def index(request):
    return HttpResponse("Hello, world. You're at the polls index.")


def sleep(request):
    sleep_in_sec = 3
    time.sleep(sleep_in_sec)
    return HttpResponse(f"I slept for {sleep_in_sec} secs.")
