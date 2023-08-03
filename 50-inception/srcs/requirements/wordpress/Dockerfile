FROM alpine:3.17
RUN apk update &&  \
	apk add php81-fpm php81-json php81-zlib php81-xml php81-xmlwriter php81-simplexml php81-pdo php81-phar php81-openssl php81-pdo_mysql php81-mysqli php81-session php81-gd php81-iconv php81-gmp php81-zip php81-curl php81-opcache php81-ctype php81-apcu php81-intl php81-bcmath php81-dom php81-mbstring php81-xmlreader mysql-client && \
	 apk add curl tini &&  \
	 rm -rf /var/cache/apk/*

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && chmod +x wp-cli.phar && mv wp-cli.phar /usr/bin/wp-cli

COPY ./tools/setup_wordpress.sh /tmp/setup_wordpress.sh
RUN chmod +x /tmp/setup_wordpress.sh
WORKDIR /var/www/html

EXPOSE 9000
ENTRYPOINT ["/sbin/tini", "--"]
CMD ["sh", "-c", "/tmp/setup_wordpress.sh"]
