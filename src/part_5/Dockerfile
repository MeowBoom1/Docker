FROM nginx
WORKDIR /home/
COPY server/run.sh /home/run.sh
COPY server/server.c /home/
COPY nginx/nginx.conf /etc/nginx/nginx.conf
RUN apt-get update && apt-get install -y gcc spawn-fcgi libfcgi-dev; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    chown -R nginx:nginx /home; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid; \
    rm -rf /var/lib/apt/lists
USER nginx
ENTRYPOINT [ "bash", "./run.sh" ]
HEALTHCHECK NONE