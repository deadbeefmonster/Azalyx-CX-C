apt-get update
apt-get -y install build-essential gcc cmake libssl-dev pkg-config libglib2.0-dev libsqlite3-dev

mkdir build
cd build
cmake ..
make
