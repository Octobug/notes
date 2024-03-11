FROM jenkins/jenkins:2.375.4
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01

USER root
# RUN echo "deb http://archive.debian.org/debian stretch main" > /etc/apt/sources.list
RUN sed -i "s@http://\(deb\|security\).debian.org@https://mirrors.tuna.tsinghua.edu.cn@g" /etc/apt/sources.list
RUN apt-get update
RUN apt-get install -y sudo
RUN echo "jenkins ALL=NOPASSWD:ALL" >> /etc/sudoers
RUN curl -o docker-latest.tgz https://get.docker.com/builds/Linux/x86_64/docker-latest.tgz
RUN tar -xzf docker-latest.tgz
RUN mv docker/* /usr/bin/

USER jenkins
# GFW took my life
RUN jenkins-plugin-cli --plugins junit
RUN jenkins-plugin-cli --plugins git
RUN jenkins-plugin-cli --plugins git-client
RUN jenkins-plugin-cli --plugins ssh-slaves
RUN jenkins-plugin-cli --plugins greenballs
RUN jenkins-plugin-cli --plugins chucknorris
RUN jenkins-plugin-cli --plugins ws-cleanup
