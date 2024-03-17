FROM ubuntu:20.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install build-essential
RUN DEBIAN_FRONTEND=noninteractive TZ=Asia/UTC apt-get -y install tzdata
RUN apt-get -y install ruby ruby-dev nodejs --fix-missing
RUN gem sources --add https://mirrors.tuna.tsinghua.edu.cn/rubygems/ \
    --remove https://rubygems.org/
RUN gem install faraday:2.8.1 faraday-net_http:3.0.2
RUN gem install jekyll:2.5.3

VOLUME /data
VOLUME /var/www/html
WORKDIR /data

ENTRYPOINT [ "jekyll", "build", "--destination=/var/www/html" ]
