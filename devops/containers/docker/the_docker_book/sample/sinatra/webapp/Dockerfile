FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01

RUN apt-get update -y; apt-get -y install ruby ruby-dev build-essential \
    redis-tools

RUN gem sources --add https://mirrors.tuna.tsinghua.edu.cn/rubygems/ \
    --remove https://rubygems.org/
RUN gem install --no-rdoc --no-ri sinatra:1.4.8 json
RUN gem install --no-rdoc --no-ri redis-client:0.19.1
RUN gem install --no-rdoc --no-ri redis

RUN mkdir -p /opt/webapp

EXPOSE 4567

CMD ["/opt/webapp/bin/webapp"]
