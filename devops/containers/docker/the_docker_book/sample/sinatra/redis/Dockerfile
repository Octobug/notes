FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01
RUN apt-get -y update; apt-get -y install redis-server redis-tools
EXPOSE 6379
ENTRYPOINT [ "/usr/bin/redis-server" ]
CMD []
