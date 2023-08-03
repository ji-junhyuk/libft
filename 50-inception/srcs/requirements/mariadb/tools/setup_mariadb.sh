set -e 

mkdir -p /run/mysqld /var/lib/mysql
chown -R mysql:mysql /var/lib/mysql /run/mysqld

mariadb-install-db --user=mysql --datadir=/var/lib/mysql

sed -i "s/skip-networking/# skip-networking/g" /etc/my.cnf.d/mariadb-server.cnf
sed -i "s/.*bind-address\s*=.*/bind-address=0.0.0.0\nport=3306/g" /etc/my.cnf.d/mariadb-server.cnf

mariadbd --user=mysql --bootstrap << EOF
USE mysql;
FLUSH PRIVILEGES;
CREATE DATABASE IF NOT EXISTS $MYSQL_DB_NAME;
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PW';
GRANT ALL PRIVILEGES ON $MYSQL_DB_NAME.* TO '$MYSQL_USER'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PW';
ALTER USER '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PW';
FLUSH PRIVILEGES;
EOF

/usr/bin/mysqld -u mysql
