FROM epitechcontent/blinux:lapin
MAINTAINER Thomas Dufour <thomas.dufour@epitech.eu>

RUN zypper -n install \
    emacs             \
    nano              \
    vim

ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

RUN useradd -md /home/bill bill
USER bill
WORKDIR /home/bill/workspace
ENTRYPOINT exec /bin/bash
