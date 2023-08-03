set -e

sed -i 's/;chdir = \/var\/www/chdir = \/var\/www\/html/g' /etc/php81/php-fpm.d/www.conf && \
sed -i 's/listen = 127.0.0.1:9000/listen = 0.0.0.0:9000/g' /etc/php81/php-fpm.d/www.conf

if [ ! -f "/var/www/html/wp-config.php" ]; then
	wp-cli core download

	wp-cli config create  \
		--dbname=$MYSQL_DB_NAME  \
		--dbuser=$MYSQL_USER  \
		--dbpass=$MYSQL_PW  \
		--dbhost=$MYSQL_DB_HOST

	wp-cli core install  \
		--url=$WP_URL  \
		--title=$WP_TITLE  \
		--admin_user=$WP_ADMIN_NAME  \
		--admin_password=$WP_ADMIN_PW  \
		--admin_email=$WP_ADMIN_MAIL

	wp-cli user create $WP_USER_NAME $WP_USER_MAIL
		--role $WP_USER_ROLE
		--user_pass=$WP_USER_PW
fi

php-fpm81 -F
