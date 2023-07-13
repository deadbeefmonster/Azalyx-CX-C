# Create the container
docker build -t azalyxcx:ubuntu23.04 .

# Run the container
docker run --rm -v "$(pwd):/azalyxcx" --cap-add=SYS_PTRACE --security-opt seccomp=unconfined -d --name azalyxcx  -i azalyxcx:ubuntu23.04

# Build the package
docker exec -it azalyxcx /azalyxcx/linux_build/build.sh


