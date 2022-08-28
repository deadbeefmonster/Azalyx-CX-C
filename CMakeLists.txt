cmake_minimum_required(VERSION 3.23)
project(ClutchingPearls C)

set(CMAKE_C_STANDARD 99)

include(FindPkgConfig)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(LIBEVENT REQUIRED IMPORTED_TARGET libevent)

find_package(OpenSSL REQUIRED)

include_directories(${LIBEVENT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
        main.c
        cli_arguments.h cli_arguments.c configuration.c configuration.h service.c service.h service_smtp.c service_smtp.h service_http.c service_http.h service_dns.c service_dns.h crypto_aes.c crypto_aes.h crypto_rsa.c crypto_rsa.h)
target_link_libraries(${PROJECT_NAME} PkgConfig::GLIB PkgConfig::LIBEVENT OpenSSL::SSL OpenSSL::Crypto)
