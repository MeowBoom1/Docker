# Simple Docker


## Оглавление

[Часть 1. Готовый докер](#часть-1-готовый-докер)  
[Часть 2. Операции с контейнером](#часть-2-операции-с-контейнером)  
[Часть 3. Мини веб-сервер](#часть-3-мини-веб-сервер)  
[Часть 4. Свой докер](#часть-4-свой-докер)  
[Часть 5. Dockle](#часть-5-dockle)  
[Часть 6. Базовый Docker Compose](#часть-6-базовый-docker-compose)  


## Часть 1. Готовый докер

- Скачиваю [официальный](https://hub.docker.com/_/nginx) ngnix образ `docker pull nginx` и проверяю наличие образа `docker images`

![docker pull nginx and docker images](part_1/part1.1.png)

- Запускаю образ `docker run -d nginx` и проверяю, что образ запущен `docker ps`

> -d - запуск контейнера в фоновом режиме

![docker run -d nginx and docker ps](part_1/part1.2.png)

- Информация о контейнере `docker inspect -s`

![docker inspect](part_1/part1.3.png)

> -s --size, добавляет в окно настройки два дополнительных поля

- Размер контейнера

![Размер контейнера](part_1/part1.4.png)

> SizeRootFs: общий размер всех файлов в контейнере в байтах

> SizeRw: размер файлов, созданных или измененных в контейнере, по сравнению с его образом, в байтах

- Список портов

![Список портов](part_1/part1.5.png)

- ip контейнера

![ip контейнера](part_1/part1.6.png)

- Останавливаю контейнер `docker stop`

![docker stop](part_1/part1.7.png)

- Проверяю, что образ остановлен `docker ps`

![docker ps](part_1/part1.8.png)

- Запускаю контейнер с замапленными портами 80 и 443

`docker run -d -p 80:80 -p 443:443 nginx`

![docker run](part_1/part1.9.png)

> -p: используется для публикации портов из контейнера на хост

> -p 80:80сопоставляет порт 80 на хосте с портом 80 в контейнере и также для порта 443

> "Замапить порт" - переадресация принимаемых данных таким образом, чтобы данные, принимаемые на какой-то порт одного компьютера автоматически переадресовывались на какой-то другой порт другого компьютера

- Проверяю стартовую страницу в бразузере

![localhoost](part_1/part1.10.png)

- Перезапускаю контейнер `docker restart` и проверяю, что образ перезапущен `docker ps`

![docker restart and docker ps](part_1/part1.11.png)


## Часть 2. Операции с контейнером

- Читаю конфигурационный файл

> docker exec используется для выполнения команды в работающем контейнере

![nginx.conf](part_2/part2.1.png)

- Создаю на локальной машине конфигурационный файл `touch nginx.conf`

![new nginx.conf](part_2/part2.2.png)

- Копирую файл в nginx `docker cp`

![docker cp](part_2/part2.3.png)

- Перезапускаю nginx `nginx -s reload` и проверяю, что все работает 

![nginx -s reload and localhost/status](part_2/part2.4.png)

- Экспортирую контейнер `docker export` и останавливаю контейнер `docker stop`

![docker export and docker stop](part_2/part2.5.png)

- Удаляю образ `docker rmi`, удаляю контейнер `docker rm`

![docker rmi](part_2/part2.6.png)

> Флаг -f — это принудительный флаг, который приводит к удалению образа Docker без подтверждения. Он используется, чтобы избежать интерактивного запроса на подтверждение удаления.

- Импортирую образ `docker import`

![docker import](part_2/part2.7.png)

- Запускаю контейнер `docker run` и проверяю, что все работает 

![docker run and localhost:80/status](part_2/part2.8.png)


## Часть 3. Мини веб-сервер

- Чтобы создать свой мини веб-сервер, необходимо создать `.c` файл, в котором будет описана логика сервера (в нашем случае - вывод сообщения Hello World!), а также конфиг `nginx.conf`, который будет проксировать все запросы с порта `81` на порт `127.0.0.1:8080`

`server.c`

![server.c](part_3/part3.1.png)

`nginx.conf`

![nginx.conf](part_3/part3.2.png)

- Запускаю контейнер `docker run`, при этом образ ngnix (https://hub.docker.com/_/nginx) автоматически подтягивается 

![docker run](part_3/part3.3.png)

- Копирую файл сервера и конфигурационный файл в контейнер `docker cp`

![docker cp](part_3/part3.4.png)

- Устанавливаю необходимые пакеты в контейнер

![apt-get install](part_3/part3.5.png)

- Компилирую, запускаю и перезапускаю сервер `nginx -s reload`

![gcc and nginx -s reload](part_3/part3.6.png)

- Проверяю, что все работает запускаю в браузере `localhost:81`

![curl localhost:81](part_3/part3.7.png)


## Часть 4. Свой докер

- Напишем свой docker-образ, который собирает исходники 3-й части, запускает на порту 80, после копирует внутрь написанный нами `nginx.conf` и, наконец, запускает nginx (ниже приведены файлы `run.sh` и `Dockerfile`, файлы `nginx.conf` и `server.c` остаются с 3-й части)

`run.sh`

![run](part_4/part4.1.png)

`Dockerfile`

![nginx.conf](part_4/part4.2.png)

- Собираю образ `docker build` и проверяю его наличие `docker images`

![docker build and docker images](part_4/part4.3.png)

> -t: Имя и при необходимости тег в формате name:tag

- Запускаю контейнер `docker run`, проверяю, что все работает `docker ps`, cмотрю `curl localhost`

![docker run](part_4/part4.4.png)

> -v: Привязка монтирования тома

> -i: Держит STDIN открытым, даже если он не подключен

> -t: Выделение псевдо-TTY

> -p: Публикация портов контейнера на хосте

- Теперь добавим в файл `nginx.conf` проксирование странички `/status`, по которой необходимо отдавать статус сервера `nginx`

![nginx.conf](part_4/part4.5.png)

- Проверяю `localhost/status`

![curl localhost/status](part_4/part4.6.png)


## Часть 5. Dockle

- Проверяю образ `salamandra_marth:1.0`

![Dockle](part_5/part5.1.png)

- После правки всех `FATATL` and `WARN` проверяю новый образ с исправлениями `salamandra_marth:2.0`

![Dockle](part_5/part5.2.png)


## Часть 6. Базовый Docker Compose

- Для начала остановим все запущенные контейнеры командой `docker stop`

- Затем изменим и дополним конфигурационные файлы

- Собираю образы `docker compose build`

![compose build](part_6/part6.1.png)

- Запускаю контейнеры и проверяю, что все работает `docker compose up -d`, `curl localhost:80`, `curl localhost/status`

![compose build](part_6/part6.2.png)

> -d: deamon

[Оглавление](#Оглавление)