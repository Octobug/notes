# Version: 0.0.1
FROM ubuntu:18.04
LABEL maintainer="octobug"
RUN apt-get update; apt-get install -y nginx
RUN echo 'Hi, I am in your container' \
    > /var/www/html/index.html
RUN apt-get install -y curl
EXPOSE 80
ENV RVM_PATH /home/rvm/
ENTRYPOINT ["/usr/sbin/nginx"]
CMD ["-h"]
HEALTHCHECK --interval=10s --timeout=1m --retries=5 CMD curl http://localhost || exit 1
