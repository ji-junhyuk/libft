FROM alpine:3.17

RUN apk update &&  \
	apk add nginx openssl tini &&  \
	rm -rf /var/cache/apk/*

COPY ./conf/nginx.conf /etc/nginx/http.d
COPY ./tools/setup_openssl.sh /tmp/setup_openssl.sh
RUN chmod +x /tmp/setup_openssl.sh

EXPOSE 443
ENTRYPOINT ["/sbin/tini", "--"]
CMD ["/bin/sh", "-c", "/tmp/setup_openssl.sh"]
