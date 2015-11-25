FROM epitechcontent/blinux:lapin
MAINTAINER Thomas Dufour <thomas.dufour@epitech.eu>

ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

RUN useradd -md /home/bill bill
USER bill

WORKDIR /home/bill/workspace
ADD make_and_test.sh /home/bill/make_and_test.sh
ADD norme_deepthought.py /home/bill/norme_deepthought.py
ENTRYPOINT exec /home/bill/make_and_test.sh
