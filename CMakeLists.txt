cmake_minimum_required(VERSION 3.23)
project(AzalyxCX C)

set(CMAKE_C_STANDARD 99)

include(FindPkgConfig)
pkg_check_modules(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(GIO REQUIRED IMPORTED_TARGET gio-2.0)
pkg_check_modules(LIBSOUP REQUIRED IMPORTED_TARGET libsoup-3.0)

find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)

include_directories(${GLIB_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR} ${SQLite3_INCLUDE_DIRS})
include_directories( src )
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
        src/database/database.c
        src/database/database.h
        src/service/service.c
        src/service/service.h
        src/service/dns/service_dns.c
        src/service/dns/service_dns.h
        src/service/http/service_http.c
        src/service/http/service_http.h
        src/service/smtp/service_smtp.c
        src/service/smtp/service_smtp.h
        src/database/sqlite3/sqlite3.h
        src/database/sqlite3/sqlite3.c
        src/database/sqlite3/tables/envelope.c
        src/database/sqlite3/tables/envelope.h
        src/database/sqlite3/tables/envelope_body.c
        src/database/sqlite3/tables/envelope_body.h
        src/database/sqlite3/tables/envelope_chunk.c
        src/database/sqlite3/tables/envelope_chunk.h
        src/database/sqlite3/tables/envelope_fault.c
        src/database/sqlite3/tables/envelope_fault.h
        src/database/sqlite3/tables/envelope_headers.c
        src/database/sqlite3/tables/envelope_headers.h
        src/database/sqlite3/tables/log.c
        src/database/sqlite3/tables/log.h
        src/database/sqlite3/tables/service.c
        src/database/sqlite3/tables/service.h
        src/database/sqlite3/tables/session.c
        src/database/sqlite3/tables/session.h
        src/database/sqlite3/tables/queue.c
        src/database/sqlite3/tables/queue.h
        src/database/sqlite3/tables/request_response.c
        src/database/sqlite3/tables/request_response.h
)
target_link_libraries(${PROJECT_NAME}
    PkgConfig::GLIB PkgConfig::GIO PkgConfig::LIBSOUP
    OpenSSL::SSL OpenSSL::Crypto
    ${SQLite3_LIBRARIES}
)
