cmake_minimum_required(VERSION 3.23)
project(AzalyxCX C)

set(CMAKE_C_STANDARD 99)

include(FindPkgConfig)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(LIBEVENT REQUIRED IMPORTED_TARGET libevent)

find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)

include_directories(${LIBEVENT_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${SQLite3_INCLUDE_DIRS})
include_directories(
        src
        src/database
        src/crypto
        src/crypto/aes
        src/crypto/rsa
        src/configuration
        src/cli
        src/service
        src/service/http
        src/service/smtp
        src/service/dns
)
add_executable(${PROJECT_NAME}
        src/main.c
        src/cli/cli_arguments.c
        src/cli/cli_arguments.h
        src/configuration/configuration.c
        src/configuration/configuration.h
        src/crypto/aes/crypto_aes.c
        src/crypto/aes/crypto_aes.h
        src/crypto/rsa/crypto_rsa.c
        src/crypto/rsa/crypto_rsa.h
        src/database/database_sqlite.c
        src/database/database_sqlite.h
        src/service/service.c
        src/service/service.h
        src/service/dns/service_dns.c
        src/service/dns/service_dns.h
        src/service/http/service_http.c
        src/service/http/service_http.h
        src/service/smtp/service_smtp.c
        src/service/smtp/service_smtp.h
        )
target_link_libraries(${PROJECT_NAME} PkgConfig::GLIB PkgConfig::LIBEVENT OpenSSL::SSL OpenSSL::Crypto ${SQLite3_LIBRARIES})
