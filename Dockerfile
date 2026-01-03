FROM debian:bookworm-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        make \
        xorg \
        libx11-dev \
        libxext-dev \
        libbsd-dev \
        zlib1g-dev \
        valgrind \
    && rm -rf /var/lib/apt/lists/*

COPY docker/entrypoint.sh /usr/local/bin/cub3d-entrypoint.sh
RUN chmod +x /usr/local/bin/cub3d-entrypoint.sh

WORKDIR /workspace

ENV VALGRIND_FLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes"

ENTRYPOINT ["/usr/local/bin/cub3d-entrypoint.sh"]
CMD ["bash"]
