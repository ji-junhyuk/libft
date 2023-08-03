mkdir -p /etc/nginx/ssl
openssl req  \
	-x509  \
	-nodes  \
	-days 365  \
	-newkey rsa:2048  \
	-keyout /etc/nginx/ssl/self_signed_key  \
	-out /etc/nginx/ssl/self_signed_crt  \
	-subj "/C=KR/ST=Seoul/L=Gangnam-gu/O=42Seoul/OU=IT Department/CN=junji.42.fr"

rm -rf /etc/nginx/http.d/default.conf

nginx -g 'daemon off;'
