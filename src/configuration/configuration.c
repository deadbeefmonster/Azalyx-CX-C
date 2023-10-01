#include "configuration/configuration.h"

void
load_configuration_file(struct settings *conf) {
    GKeyFile *keyfile;
    GKeyFileFlags flags;
    GError *error = NULL;
    gboolean service_enable_dns, service_enable_http, service_enable_smtp;
    guint16 service_dns_port, service_http_port, service_smtp_port;
    gchar *http_keyfile_path, *http_certfile_path;
    gchar *sqlite_database_path;

    /* Test if file is available for read-only access */
    int fd = g_open(conf->configuration_file, O_WRONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd == -1) {
        g_printf("FATAL ERROR: Unable to open '%s' for reading\n", conf->configuration_file);
        exit(EXIT_FAILURE);
    }
    close(fd);

    /* Create a new GKeyFile object and a bitwise list of flags. */
    keyfile = g_key_file_new();
    flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;
    if (!g_key_file_load_from_file(keyfile,
                                   conf->configuration_file,
                                   flags,
                                   &error)) {
        g_printerr("FATAL ERROR: Unable to load configuration from configuration file '%s': %s\n",
                conf->configuration_file,
                error->message);
        exit(EXIT_FAILURE);
    }
    service_enable_dns =
            g_key_file_get_boolean(keyfile, "service", "enable_dns", NULL);
    service_enable_http =
            g_key_file_get_boolean(keyfile, "service", "enable_http", NULL);
    service_enable_smtp =
            g_key_file_get_boolean(keyfile, "service", "enable_smtp", NULL);
    service_dns_port =
            g_key_file_get_integer(keyfile, "dns", "port", NULL);
    service_http_port =
            g_key_file_get_integer(keyfile, "http", "port", NULL);
    service_smtp_port =
            g_key_file_get_integer(keyfile, "smtp", "port", NULL);
    http_keyfile_path = g_key_file_get_string(keyfile, "http", "keyfile", NULL);
    http_certfile_path = g_key_file_get_string(keyfile, "http", "certfile", NULL);
    sqlite_database_path = g_key_file_get_string(keyfile, "sqlite", "database_file", NULL);

    if (sqlite_database_path && conf->sqlite_database_file == NULL) {
        conf->sqlite_database_file = sqlite_database_path;
    }

    if (http_keyfile_path) {
        conf->http_keyfile = http_keyfile_path;
    }
    if (http_certfile_path) {
        conf->http_certfile = http_certfile_path;
    }

    /* Store only if it hasn't been stored before (do not override CLI
     * args) */
    if (conf->service_enable_dns == SERVICE_STATUS_UNKNOWN) {
        conf->service_enable_dns =
                (gint) (service_enable_dns ? SERVICE_STATUS_ENABLED
                                           : SERVICE_STATUS_DISABLED);
    }
    if (conf->service_enable_http == SERVICE_STATUS_UNKNOWN) {
        conf->service_enable_http =
                (gint) (service_enable_http ? SERVICE_STATUS_ENABLED
                                            : SERVICE_STATUS_DISABLED);
    }
    if (conf->service_enable_smtp == SERVICE_STATUS_UNKNOWN) {
        conf->service_enable_smtp =
                (gint) (service_enable_smtp ? SERVICE_STATUS_ENABLED
                                            : SERVICE_STATUS_DISABLED);
    }
    if (conf->service_dns_port == 0) {
        conf->service_dns_port = (guint16) service_dns_port;
    }
    if (conf->service_http_port == 0) {
        conf->service_http_port = (guint16) service_http_port;
    }
    if (conf->service_smtp_port == 0) {
        conf->service_smtp_port = (guint16) service_smtp_port;
    }
}
