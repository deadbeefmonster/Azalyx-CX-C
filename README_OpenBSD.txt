Building on OpenBSD
===================
## Install required packages/files
pkg_add cmake glib2 git sqlite3 libsoup3

## Get the repo
git clone https://github.com/deadbeefmonster/Azalyx-CX-C

## Create a build directory
mkdir -p build
cd build

## Build it
cmake ..
make

