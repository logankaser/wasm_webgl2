FROM debian:sid

WORKDIR /root

COPY scripts/docker_setup.sh /root/docker_setup.sh

RUN ./docker_setup.sh
