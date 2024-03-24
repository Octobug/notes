FROM consul:1.15.4

ADD consul.json /consul/config/

EXPOSE 8400

VOLUME [ "/consul/data" ]

ENTRYPOINT ["docker-entrypoint.sh", "agent"]

CMD []
