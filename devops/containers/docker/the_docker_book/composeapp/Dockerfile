FROM python:2.7
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

ADD . /composeapp

WORKDIR /composeapp

RUN pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
RUN pip install -r requirements.txt
