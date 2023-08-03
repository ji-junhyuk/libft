FROM alpine:3.17

RUN apk update &&  \
	 apk add mariadb mariadb-client &&  \
	 apk add tini &&  \
	 rm -rf /var/cache/apk/*

COPY ./tools/setup_mariadb.sh /tmp/setup_mariadb.sh
RUN chmod +x /tmp/setup_mariadb.sh

EXPOSE 3306
ENTRYPOINT ["/sbin/tini", "--"]
CMD ["/bin/sh", "-c", "/tmp/setup_mariadb.sh"]
