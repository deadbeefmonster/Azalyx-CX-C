#define G_LOG_USE_STRUCTURED 1

#include <glib.h>
#include <gio/gio.h>
#include <stdlib.h>

#include "cli/cli_arguments.h"
#include "configuration/configuration.h"
#include "crypto/aes/crypto_aes.h"
#include "database/database.h"
#include "service/service.h"


#define AZALYXCX_VERSION "0.1.0"
#define AZALYXCX_DEVELOPER "Christoff Humphries <christoff@deadbeef.monster>"
#define AZALYXCX_COPYRIGHT "(c)2023"

gboolean NO_COLOR = FALSE;

int
main(int argc, char **argv) {
    /* Include support for NO_COLOR ~> https://no-color.org/ */
    const gchar *no_color_env = g_getenv("NO_COLOR");
    if (no_color_env != NULL && no_color_env[0] != '\0') {
        NO_COLOR = TRUE;
    }

    printf("%s v%s: A protocol research and C programming project.\n", "AzalyxCX", AZALYXCX_VERSION);
    printf("%s, %s\n\n\n", AZALYXCX_COPYRIGHT, AZALYXCX_DEVELOPER);

    gchar **cli_args;                                        /* CLI arguments */
    struct settings *conf = g_slice_new(struct settings);    /* All settings */
    GArray *ServiceDatas = g_array_new(FALSE, FALSE, sizeof(struct service_data *));    /* Services */

    /* Init glib */
    g_log_set_handler(G_LOG_DOMAIN,
                      G_LOG_LEVEL_MASK,
                      g_log_default_handler,
                      NULL);


    /* Init configuration */
    conf->service_enable_dns = SERVICE_STATUS_UNKNOWN;
    conf->service_dns_port = 0;
    conf->service_enable_http = SERVICE_STATUS_UNKNOWN;
    conf->service_http_port = 0;
    conf->service_enable_smtp = SERVICE_STATUS_UNKNOWN;
    conf->service_smtp_port = 0;
    conf->configuration_file = NULL;


    /* Read command line arguments */
    cli_args = g_strdupv(argv);
    cli_arguments_parse(cli_args, conf);
    g_strfreev(cli_args);

    /* Service provisioning, setup, and registering. - Create sockets,
     * register callbacks */
    /* TODO: plugin hook */
    if (conf->service_enable_dns == SERVICE_STATUS_ENABLED) {
        /* TODO: plugin hook */

        /* Ensure sane port defaults if none specified */
        if (conf->service_dns_port == 0) {
            g_debug("Ensuring sane DNS port 0 -> 53");
            conf->service_dns_port = 53;
        }

        //struct service_data *service_data_dns;
        //g_array_append_val(ServiceDatas, service_data_dns);
        g_info("Service DNS Loaded");

        /* TODO: plugin hook */
    }
    if (conf->service_enable_http == SERVICE_STATUS_ENABLED) {
        /* TODO: plugin hook */

        /* Ensure sane port defaults if none specified */
        if (conf->service_http_port == 0) {
            g_debug("Ensuring sane HTTP port 0 -> 80");
            conf->service_http_port = 80;
        }

        struct service_data *service_data_http = g_slice_new(struct service_data);

        GError *http_error = NULL;
        GSocketService *http_service = g_threaded_socket_service_new(100);
        g_socket_listener_add_inet_port((GSocketListener *)http_service, conf->service_http_port, NULL, &http_error);

        if (http_error != NULL) {
            fprintf(stderr, "FATAL ERROR: Could not create http socket listener: %s\n", http_error->message);
            g_error_free (http_error);
            return (EXIT_FAILURE);
        }

        g_signal_connect(http_service, "run", G_CALLBACK(http_handle_request), NULL);
        g_socket_service_start(http_service);

        service_data_http->service = http_service;
        service_data_http->port = conf->service_http_port;
        service_data_http->service_proto = SERVICE_PROTO_TCP;
        service_data_http->service_type = SERVICE_TYPE_HTTP;

        g_array_append_val(ServiceDatas, service_data_http);
        g_info("Service HTTP Loaded");

        /* TODO: plugin hook */
    }
    if (conf->service_enable_smtp == SERVICE_STATUS_ENABLED) {
        /* TODO: plugin hook */

        /* Ensure sane port defaults if none specified */
        if (conf->service_smtp_port == 0) {
            g_debug("Ensuring sane DNS port 0 -> 25");
            conf->service_dns_port = 25;
        }

        //struct service_data *service_data_smtp;
        //g_array_append_val(ServiceDatas, service_data_smtp);
        g_info("Service SMTP Loaded");

        /* TODO: plugin hook */
    }
    /* TODO: plugin_hook */


    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);




    /* Cleanup */
    if (conf)
        g_slice_free(struct settings, conf);

    if (ServiceDatas) {
        int i;
        for (i = 0; i  < ServiceDatas->len; i++) {
            struct service_data *tmp = g_array_index(ServiceDatas, struct service_data *, i);
            g_socket_service_stop(tmp->service);
        }
        g_array_free(ServiceDatas, TRUE);

    }

    return (EXIT_SUCCESS);
}
