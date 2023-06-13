cmake_minimum_required(VERSION 3.23)
project(Blitzkrieg C)

set(CMAKE_C_STANDARD 99)

include(FindPkgConfig)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(LIBEVENT REQUIRED IMPORTED_TARGET libevent)

find_package(OpenSSL REQUIRED)

include_directories(${LIBEVENT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
        src/main.c
        src/cli_arguments.c src/cli_arguments.h
        src/configuration.c src/configuration.h
        src/service.c src/service.h
        src/service_smtp.c src/service_smtp.h
        src/service_http.c src/service_http.h
        src/service_dns.c src/service_dns.h
        src/crypto_aes.c src/crypto_aes.h
        src/crypto_rsa.c src/crypto_rsa.h)
target_link_libraries(${PROJECT_NAME} PkgConfig::GLIB PkgConfig::LIBEVENT OpenSSL::SSL OpenSSL::Crypto)
