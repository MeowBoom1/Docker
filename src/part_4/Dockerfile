FROM nginx
WORKDIR /home/
COPY run.sh /home/run.sh
COPY server.c /home/
COPY nginx.conf /etc/nginx/nginx.conf
RUN apt update && apt install -y gcc spawn-fcgi libfcgi-dev
ENTRYPOINT [ "sh", "./run.sh" ]