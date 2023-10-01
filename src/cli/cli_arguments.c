/*
 * To show verbose and debug messages
 * G_MESSAGES_DEBUG=all ./AzalyxCX ...
 * https://people.gnome.org/~ryanl/glib-docs/glib-Message-Logging.html
 * Will control better with another logging manager, probably my own g_log handler.
 *
 */

#include "cli/cli_arguments.h"
#include "configuration/configuration.h"

void
cli_arguments_parse(gchar **args, struct settings *conf) {
    GError *error = NULL;
    GOptionContext *context;

    static gboolean cli_argument_service_enable_dns;
    static gboolean cli_argument_service_enable_http;
    static gboolean cli_argument_service_enable_smtp;
    static gchar *cli_argument_configuration_file;
    static guint16 cli_dns_port = 0;
    static guint16 cli_http_port = 0;
    static guint16 cli_smtp_port = 0;
    static gchar *cli_http_certfile;
    static gchar *cli_http_keyfile;



    static GOptionEntry cli_argument_options[] =
            {
                    {"service-enable-dns",  0,   0, G_OPTION_ARG_NONE,
                            &cli_argument_service_enable_dns,  "Enable DNS Service (UDP)",  NULL},
                    {"service-dns-port", 0, 0, G_OPTION_ARG_INT, &cli_dns_port, "DNS Service Port (UDP)"},
                    {"service-enable-http", 0,   0, G_OPTION_ARG_NONE,
                            &cli_argument_service_enable_http, "Enable HTTP Service", NULL},
                    {"service-http-port", 0, 0, G_OPTION_ARG_INT, &cli_http_port, "HTTP Service Port"},
                    {"service-enable-smtp", 0,   0, G_OPTION_ARG_NONE,
                            &cli_argument_service_enable_smtp, "Enable SMTP Service", NULL},
                    {"service-smtp-port", 0, 0, G_OPTION_ARG_INT, &cli_smtp_port, "SMTP Service Port (UDP)"},
                    {"configuration-file",  'c', 0, G_OPTION_ARG_FILENAME,
                            &cli_argument_configuration_file,  "Configuration File",  NULL},
                    {"http-certfile", 0, 0, G_OPTION_ARG_FILENAME, &cli_http_certfile, "HTTP certificate cert file path", NULL},
                    {"http-keyfile", 0, 0, G_OPTION_ARG_FILENAME, &cli_http_keyfile, "HTTP certificate key file path", NULL},
                    {NULL}
            };

    /* Defaults */
    context = g_option_context_new("");
    g_option_context_add_main_entries(context, cli_argument_options, NULL);
    if (!g_option_context_parse_strv(context, &args, &error)) {
        g_printerr("FATAL ERROR: command line argument parsing failed: %s\n", error->message);
        exit(EXIT_FAILURE);
    }

    // Parse the configuration file
    if (cli_argument_configuration_file) {
        g_debug("Setting conf->configuration_file from '%s' to '%s'",
                conf->configuration_file,
                cli_argument_configuration_file);
        conf->configuration_file = cli_argument_configuration_file;
        load_configuration_file(conf);
        g_debug("Set conf->configuration_file, it is now '%s'",
                conf->configuration_file);
    }
    if (cli_argument_service_enable_dns) {
        g_debug("Enabling DNS service via CLI argument override");
        conf->service_enable_dns = SERVICE_STATUS_ENABLED;
    }
    if (cli_argument_service_enable_http) {
        g_debug("Enabling HTTP service via CLI argument override");
        conf->service_enable_http = SERVICE_STATUS_ENABLED;
    }
    if (cli_argument_service_enable_smtp) {
        g_debug("Enabling SMTP service via CLI argument override");
        conf->service_enable_smtp = SERVICE_STATUS_ENABLED;
    }
    if (cli_dns_port) {
        g_debug("Enabling DNS service port CLI argument override (port %i)", cli_dns_port);
        conf->service_dns_port = cli_dns_port;
    }
    if (cli_http_port) {
        g_debug("Enabling HTTP service port CLI argument override (port %i)", cli_http_port);
        conf->service_http_port = cli_http_port;
    }
    if (cli_smtp_port) {
        g_debug("Enabling SMTP service port CLI argument override (port %i)", cli_smtp_port);
        conf->service_smtp_port = cli_smtp_port;
    }
    if (cli_http_keyfile) {
        g_debug("HTTPS certificate key file override: %s", cli_http_keyfile);
        conf->http_keyfile = cli_http_keyfile;
    }
    if (cli_http_certfile) {
        g_debug("HTTPS certificate cert file override: %s", cli_http_certfile);
        conf->http_certfile = cli_http_certfile;
    }

    g_option_context_free(context);
}
