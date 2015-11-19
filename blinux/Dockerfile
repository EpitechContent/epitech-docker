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

ENV MLX_PATH /usr/src/minilibx
ADD minilibx $MLX_PATH
RUN make -C $MLX_PATH install
RUN make -C $MLX_PATH clean

ENV SFML_PATH /usr/src/SFML-2.3
ADD SFML-2.3 $SFML_PATH
RUN cmake -L -B$SFML_PATH -H$SFML_PATH
RUN make -C $SFML_PATH all
RUN make -C $SFML_PATH install

ENV LAPIN_PATH /usr/src/liblapin
ADD liblapin $LAPIN_PATH
RUN make -C $LAPIN_PATH  title erase all-quiet
RUN make -C $LAPIN_PATH install

ADD .bashrc /etc/skel/.bashrc
ADD bugs /usr/bin/bugs
