#define G_LOG_USE_STRUCTURED 1

#include <glib.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <stdlib.h>

#include "cli/cli_arguments.h"
#include "configuration/configuration.h"
#include "crypto/aes/crypto_aes.h"
#include "database/database_sqlite.h"
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
    struct event_base *base;                                 /* LibEvent */
    GArray *ServiceDatas = g_array_new(FALSE, FALSE, sizeof(struct service_data *));    /* Services */

    /* Init glib */
    g_log_set_handler(G_LOG_DOMAIN,
                      G_LOG_LEVEL_MASK,
                      g_log_default_handler,
                      NULL);

    /* Init libevent */
    base = event_base_new();
    if (!base) {
        fprintf(stderr, "FATAL ERROR: event_base_new() failed\n");
        exit(EXIT_FAILURE);
    }

    /* Init configuration */
    conf->service_enable_dns = SERVICE_STATUS_UNKNOWN;
    conf->service_enable_http = SERVICE_STATUS_UNKNOWN;
    conf->service_enable_smtp = SERVICE_STATUS_UNKNOWN;

    /* Read command line arguments */
    cli_args = g_strdupv(argv);
    cli_arguments_parse(cli_args, conf);
    g_strfreev(cli_args);


    /* Service provisioning, setup, and registering. - Create sockets,
     * register callbacks */
    /* TODO: plugin hook */
    if (conf->service_enable_dns == SERVICE_STATUS_ENABLED) {
        /* TODO: plugin hook */

        struct service_data *service_data_dns;
        service_data_dns =
                service_generate(SERVICE_TYPE_DNS, SERVICE_PROTO_UDP, 53, base);
        g_array_append_val(ServiceDatas, service_data_dns);
        g_info("Service DNS Loaded");

        /* TODO: plugin hook */
    }
    if (conf->service_enable_http == SERVICE_STATUS_ENABLED) {
        /* TODO: plugin hook */

        struct service_data *service_data_http;
        service_data_http =
                service_generate(SERVICE_TYPE_HTTP, SERVICE_PROTO_TCP, 80, base);
        g_array_append_val(ServiceDatas, service_data_http);
        g_info("Service HTTP Loaded");

        /* TODO: plugin hook */
    }
    if (conf->service_enable_smtp == SERVICE_STATUS_ENABLED) {
        /* TODO: plugin hook */

        struct service_data *service_data_smtp;
        service_data_smtp =
                service_generate(SERVICE_TYPE_SMTP, SERVICE_PROTO_TCP, 25, base);
        g_array_append_val(ServiceDatas, service_data_smtp);
        g_info("Service SMTP Loaded");

        /* TODO: plugin hook */
    }
    /* TODO: plugin_hook */

    /* TODO: plugin hook */
    event_base_dispatch(base);
    /* TODO: plugin hook */

    /* Cleanup */
    /* XXX - Close all sockets */
    if (conf)
        g_slice_free(struct settings, conf);
    if (ServiceDatas)
        g_array_free(ServiceDatas, TRUE);

    return (EXIT_SUCCESS);
}
