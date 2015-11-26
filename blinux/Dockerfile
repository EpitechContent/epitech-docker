FROM opensuse:13.2
MAINTAINER Thomas Dufour <thomas.dufour@epitech.eu>

RUN zypper --gpg-auto-import-keys -n update
RUN zypper --non-interactive install \
    clang             \
    gcc gcc-c++       \
    libX11-devel      \
    libXext-devel     \
    make
RUN zypper --non-interactive install \
    ksh               \
    tcsh              \
    zsh
RUN zypper --non-interactive install \
    ltrace
RUN zypper --non-interactive install          \
    libSDL-devel libSDL2-devel \
    ncurses ncurses-devel      \
    boost-devel                \
    php5                       \
    python-numpy               \
    python3                    \
    python3-numpy              \
    ruby
RUN zypper --non-interactive install \
    tmux              \
    valgrind          \
    zip unzip
RUN zypper --non-interactive install \
    glibc-locale

# Debug stuff
#RUN zypper --non-interactive install \
#    emacs-nox \
#    less \
#    strace
#ADD lapin /root/lapin

# lib_lapin dependencies
RUN zypper --non-interactive install \
    freetype-devel \
    libjpeg8-devel \
    xorg-x11-devel \
    libXrandr-devel \
    xcb \
    libX11-xcb1 \
    libxcb-randr0 \
    xcb-util-image-devel \
    libQt5OpenGL5 \
    flac-devel \
    libogg-devel \
    libvorbis-devel \
    libvorbisenc2 \
    libvorbisfile3 \
    openal-soft-devel \
    pthread-stubs-devel \
    libudev-devel \
    cmake

ADD .bashrc /etc/skel/.bashrc
ADD bugs /usr/bin/bugs

WORKDIR /usr/src/minilibx
ADD minilibx .
RUN make install
RUN make clean

WORKDIR /usr/src/SFML-2.3
ADD SFML-2.3 . 
RUN cmake -L 
RUN make all
RUN make install
RUN make clean


WORKDIR /usr/src/liblapin
ADD liblapin .
RUN make title erase all-quiet
RUN make install
RUN make fclean

ENV LD_LIBRARY_PATH /usr/local/lib
ENV DISPLAY 0.0

WORKDIR /