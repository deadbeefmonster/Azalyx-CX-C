Building on OpenBSD
===================
## Install required packages/files
pkg_add cmake
pkg_add openssl # Pick whatever 3.1.x version is available
pkg_add glib2
pkg_add libevent
pkg_add git

## Get the repo
git clone https://github.com/deadbeefmonster/Blitzkrieg.git

## Create a build directory
mkdir - build
cd build

## Build the project
# Ensure OpenSSL library is used instead of LibreSSL
cmake -DOPENSSL_CRYPTO_LIBRARY=/usr/local/lib/eopenssl31/libcrypto.a -DOPENSSL_INCLUDE_DIR=/usr/local/include/eopenssl31/ ..
make




cmake output (example)
======================
-- The C compiler identification is Clang 13.0.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found PkgConfig: /usr/bin/pkg-config (found version "0.29.2")
-- Checking for module 'glib-2.0'
--   Found glib-2.0, version 2.74.6
-- Checking for module 'libevent'
--   Found libevent, version 2.1.12-stable
-- Found OpenSSL: /usr/local/lib/eopenssl31/libcrypto.a (found version "3.1.0")
-- Configuring done
-- Generating done
-- Build files have been written to: /home/christoff/Blitzkrieg/build



make output earnings
====================
bio_sock.c:280 (crypto/bio/bio_sock.c:280)(libcrypto-lib-bio_sock.o:(BIO_accept) in archive /usr/local/lib/eopenssl31/libcrypto.a): warning: strcpy() is almost always misused, please use strlcpy()
bio_sock.c:282 (crypto/bio/bio_sock.c:282)(libcrypto-lib-bio_sock.o:(BIO_accept) in archive /usr/local/lib/eopenssl31/libcrypto.a): warning: strcat() is almost always misused, please use strlcat()
dso_dlfcn.c:0 (crypto/dso/dso_dlfcn.c:0)(libcrypto-lib-dso_dlfcn.o:(dlfcn_name_converter) in archive /usr/local/lib/eopenssl31/libcrypto.a): warning: sprintf() is often misused, please use snprintf()

