FROM ubuntu:20.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install wget

VOLUME [ "/var/lib/tomcat8/webapps/" ]
WORKDIR /var/lib/tomcat8/webapps/

ENTRYPOINT [ "wget" ]
CMD [ "-?" ]
