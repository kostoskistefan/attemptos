FROM gcc:latest

RUN apt update
RUN apt upgrade -y
RUN apt install -y nasm
RUN apt install -y grub-pc-bin
RUN apt install -y grub-common
RUN apt install -y xorriso

VOLUME /root/env
WORKDIR /root/env
