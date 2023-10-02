#define G_LOG_USE_STRUCTURED 1

#include <glib.h>
#include <gio/gio.h>
#include <libsoup/soup.h>

#include "cli/cli_arguments.h"
#include "configuration/configuration.h"
#include "crypto/aes/crypto_aes.h"
#include "database/database.h"
#include "service/service.h"


#define AZALYXCX_VERSION "0.1.0"
#define AZALYXCX_DEVELOPER "Christoff Humphries <christoff@deadbeef.monster>"
#define AZALYXCX_COPYRIGHT "(c)2023"

gboolean NO_COLOR = FALSE;

static void
quit(int sig)
{
	g_print("\nExiting now.\n");
	exit(0);
}


int
main(int argc, char **argv)
{
	/* Include support for NO_COLOR ~> https://no-color.org/ */
	const gchar *no_color_env = g_getenv("NO_COLOR");
	if (no_color_env != NULL && no_color_env[0] != '\0') {
		NO_COLOR = TRUE;
	}
	printf("%s v%s: A protocol research and C programming project.\n", "AzalyxCX", AZALYXCX_VERSION);
	printf("%s, %s\n\n\n", AZALYXCX_COPYRIGHT, AZALYXCX_DEVELOPER);
	signal(SIGINT, quit);

	gchar **cli_args;	/* CLI arguments */
	struct settings *conf = g_slice_new(struct settings);	/* All settings */

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
	conf->http_keyfile = NULL;
	conf->http_certfile = NULL;
	conf->sqlite_database_file = NULL;


	/* Read command line arguments */
	cli_args = g_strdupv(argv);
	cli_arguments_parse(cli_args, conf);
	g_strfreev(cli_args);

	/* Service provisioning, setup, and registering. */
	/* TODO: plugin hook */
	if (conf->service_enable_dns == SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		/* Ensure sane port defaults if none specified */
		if (conf->service_dns_port == 0) {
			g_debug("Ensuring sane DNS port 0 -> 53");
			conf->service_dns_port = 53;
		}
		g_info("Service DNS Loaded");

		/* TODO: plugin hook */
	}
	if (conf->service_enable_http == SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		/* Ensure sane port defaults if none specified */
		if (conf->service_http_port == 0) {
			if (conf->http_keyfile && conf->http_certfile) {
				g_debug("Ensuring sane HTTP port 0 -> 443 (HTTPS files are configured)");
				conf->service_http_port = 443;
			} else {
				g_debug("Ensuring sane HTTP port 0 -> 80");
				conf->service_http_port = 80;
			}
		}
		GError *http_error = NULL;
		SoupServer *http_server;

		/* https://gitlab.gnome.org/GNOME/libsoup/blob/master/examples/
		 * simple-httpd.c */
		if (conf->http_keyfile && conf->http_certfile) {
			GTlsCertificate *cert = g_tls_certificate_new_from_files(conf->http_certfile, conf->http_keyfile,
			    &http_error);
			if (http_error) {
				g_printerr("FATAL ERROR: Could not load certificate for http service: %s\n", http_error->message);
				g_error_free(http_error);
				return (EXIT_FAILURE);
			}
			http_server = soup_server_new("server-header", "http-server",
			    "tls-certificate", cert,
			    NULL);
			g_object_unref(cert);

			soup_server_listen_all(http_server, conf->service_http_port, SOUP_SERVER_LISTEN_HTTPS, &http_error);
			if (http_error != NULL) {
				g_printerr("FATAL ERROR: Could not create http server (with certificate services): %s\n",
				    http_error->message);
				g_error_free(http_error);
				return (EXIT_FAILURE);
			}
		} else {
			http_server = soup_server_new("server-header", "http-server", NULL);
			soup_server_listen_all(http_server, conf->service_http_port, 0, &http_error);
			if (http_error != NULL) {
				g_printerr("FATAL ERROR: Could not create http server: %s\n", http_error->message);
				g_error_free(http_error);
				return (EXIT_FAILURE);
			}
		}
		soup_server_add_handler(http_server, NULL, http_handle_request, NULL, NULL);

		if (conf->http_keyfile && conf->http_certfile) {
			g_info("Service HTTP Loaded with HTTPS capabilities");
		} else {
			g_info("Service HTTP Loaded");
		}
		/* TODO: plugin hook */
	}
	if (conf->service_enable_smtp == SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		/* Ensure sane port defaults if none specified */
		if (conf->service_smtp_port == 0) {
			g_debug("Ensuring sane DNS port 0 -> 25");
			conf->service_dns_port = 25;
		}
		g_info("Service SMTP Loaded");

		/* TODO: plugin hook */
	}
	/* TODO: plugin_hook */


	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);




	/* Cleanup */
	if (conf) {
        g_free(conf->sqlite_database_file);
        g_slice_free(struct settings, conf);
    }


	return (EXIT_SUCCESS);
}
