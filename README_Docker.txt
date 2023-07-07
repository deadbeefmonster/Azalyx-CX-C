# Create the container
docker build -t blitzkreig:ubuntu23.04 .

# Run the container
docker run --rm -v "$(pwd):/blitzkrieg" --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -d --name blitzkrieg  -i blitzkreig:ubuntu23.04

# Build the package
docker exec -it blitzkrieg /blitzkrieg/linux_build/build.sh


