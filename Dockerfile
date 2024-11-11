FROM ubuntu:22.04 AS build

LABEL maintainer="Jorik Devreese"
LABEL version="0.1"
LABEL description="docker image for hosting a GTS server injecting remote code into gen 4 Pokémon games."

RUN DEBIAN_FRONTEND=noninteractive apt-get update -y &&  \
    DEBIAN_FRONTEND=noninteractive apt-get upgrade -y &&  \
    DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y build-essential git libpng-dev gdebi-core python3 python3-pip cmake automake libnewlib-arm-none-eabi libnewlib-dev libstdc++-arm-none-eabi-dev libstdc++-arm-none-eabi-newlib gcc-arm-none-eabi mono-devel && \
    DEBIAN_FRONTEND=noninteractive apt-get update -y

ADD build /tmp
RUN pip install -r /tmp/requirements.txt && rm /tmp/requirements.txt

EXPOSE 80
EXPOSE 53/tcp
EXPOSE 53/udp
