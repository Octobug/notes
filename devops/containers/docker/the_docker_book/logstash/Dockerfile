FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01
RUN apt-get update
RUN apt-get -y install wget gnupg2 openjdk-8-jdk
RUN wget -qO - https://artifacts.elastic.co/GPG-KEY-elasticsearch | apt-key add -
RUN echo "deb https://artifacts.elastic.co/packages/5.x/apt stable main" | tee -a /etc/apt/sources.list.d/elastic-5.x.list

RUN apt-get update
RUN apt-get install -y logstash

WORKDIR /usr/share/logstash
ADD logstash.conf /usr/share/logstash/
ENTRYPOINT [ "bin/logstash" ]
CMD [ "-f", "logstash.conf", "--config.reload.automatic" ]
