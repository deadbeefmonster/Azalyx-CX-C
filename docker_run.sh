#!/bin/sh
#
mkdir -p linux_build
docker run --rm -v "$(pwd):/blitzkrieg" --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -d --name blitzkrieg  -i blitzkreig:ubuntu23.04
