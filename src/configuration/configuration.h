/**
 * https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html
 * http://www.gtkbook.com/gtkbook/keyfile.html
 *
 * All configuration file stuff
 */

#ifndef AZALYXCX_CONFIGURATION_CONFIGURATION_H
#define AZALYXCX_CONFIGURATION_CONFIGURATION_H

#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <sys/file.h>

#include "service/service.h"

struct settings {
	gchar *configuration_file;
	gint service_enable_dns;
	gint service_enable_http;
	gint service_enable_smtp;
	guint16 service_dns_port;
	guint16 service_http_port;
	guint16 service_smtp_port;
	gchar *http_certfile;
	gchar *http_keyfile;
	gchar *sqlite_database_file;
};

void load_configuration_file(struct settings *);

#endif				/* AZALYXCX_CONFIGURATION_CONFIGURATION_H */
