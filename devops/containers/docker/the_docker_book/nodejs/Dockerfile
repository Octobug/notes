FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install build-essential
RUN apt-get -y install nodejs --fix-missing
RUN apt-get -y install npm --fix-missing

# RUN ln -s /usr/bin/nodejs /usr/bin/node
RUN mkdir -p /var/log/nodepp

ADD nodeapp /opt/nodeapp/

WORKDIR /opt/nodeapp/
RUN npm install

VOLUME [ "/var/log/nodeapp" ]

EXPOSE 3000

ENTRYPOINT [ "nodejs", "server.js" ]
