FROM ubuntu:rolling

RUN apt-get update && apt-get install -y \
    tmux htop wget autoconf automake pkg-config \
    cmake build-essential libboost-all-dev \
    cppcheck libgtest-dev libgmock-dev \
    python3-dev python3-venv python3-pip python3-pytest

RUN cd /usr/src/googletest/googletest && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=RELEASE -DBUILD_SHARED_LIBS=ON .. && \
    make && \
    cp lib/libgtest* /usr/lib/ && \
    cd .. && \
    rm -rf build

WORKDIR /mnt/data

RUN pip3 install websockets
