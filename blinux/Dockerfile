FROM opensuse:13.2
MAINTAINER Thomas Dufour <thomas.dufour@epitech.eu>

RUN zypper --gpg-auto-import-keys -n update
RUN zypper -n install \
    clang             \
    gcc gcc-c++       \
    libX11-devel      \
    libXext-devel     \
    make              \
    which
RUN zypper -n install \
    ksh               \
    tcsh              \
    zsh
RUN zypper -n install \
    ltrace
RUN zypper -n install          \
    libSDL-devel libSDL2-devel \
    ncurses ncurses-devel      \
    boost-devel                \
    php5                       \
    php5-mbstring              \
    python-numpy               \
    python3                    \
    python3-pip                \
    python3-numpy              \
    ruby
RUN pip3 install -Iv pexpect==4.0.1
RUN zypper -n install \
    tmux              \
    valgrind          \
    zip unzip
RUN zypper -n install \
    glibc-locale

ADD minilibx /usr/src/minilibx
RUN make -C /usr/src/minilibx install
RUN make -C /usr/src/minilibx clean

ADD xterm-noapp /usr/share/terminfo/x/xterm-noapp
ADD .bashrc /etc/skel/.bashrc
ADD bugs /usr/bin/bugs
