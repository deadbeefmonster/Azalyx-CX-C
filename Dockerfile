FROM ubuntu:23.04
ENV LC_CTYPE C.UTF-8
ENV DEBIAN_FRONTEND=noninteractive
run apt-get update && apt-get -y install build-essential gcc cmake libevent-dev libssl-dev pkg-config libglib2.0-dev
