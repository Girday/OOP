FROM mcr.microsoft.com/devcontainers/cpp:latest

RUN apt-get update && apt-get install -y wget \
    && wget https://github.com/Kitware/CMake/releases/download/v4.1.1/cmake-4.1.1-linux-x86_64.tar.gz \
    && tar -xzf cmake-4.1.1-linux-x86_64.tar.gz \
    && mv cmake-4.1.1-linux-x86_64 /opt/cmake \
    && rm -f /usr/local/bin/cmake /usr/local/bin/ctest /usr/local/bin/cpack /usr/local/bin/ccmake /usr/local/bin/cmake-gui \
    && ln -s /opt/cmake/bin/* /usr/local/bin/ \
    && rm cmake-4.1.1-linux-x86_64.tar.gz
