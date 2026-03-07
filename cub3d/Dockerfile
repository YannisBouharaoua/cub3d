FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential clang make git pkg-config \
    xorg-dev libx11-dev libxext-dev libbsd-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work
