all:
	@make up

up:
	@mkdir -p /home/$$USER/data/mariadb
	@mkdir -p /home/$$USER/data/wordpress
	@echo "127.0.0.1 $$USER.42.fr" | sudo tee --append /etc/hosts
	@docker compose --file ./srcs/docker-compose.yml up --detach --build

stop:
	@docker compose --file ./srcs/docker-compose.yml stop

restart:
	@docker restart $$(docker ps -q)

clean:
	@docker compose --file ./srcs/docker-compose.yml down --remove-orphans --rmi local --volumes

fclean:
	@make clean
	docker system prune --all --volumes

re:
	@make fclean
	@make all;

.PHONY: all up stop down clean fclean re
