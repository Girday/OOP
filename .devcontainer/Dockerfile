FROM gcc:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    strace \
    sudo \
    && rm -rf /var/lib/apt/lists/*

ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=1000
RUN groupadd --gid ${USER_GID} ${USERNAME} \
    && useradd -s /bin/bash --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} \
    && echo '${USERNAME} ALL=(ALL) NOPASSWD:ALL' > /etc/sudoers.d/${USERNAME} \
    && chmod 0440 /etc/sudoers.d/${USERNAME}

WORKDIR /work
USER ${USERNAME}

CMD ["bash"]
