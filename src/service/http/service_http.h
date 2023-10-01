

#ifndef AZALYXCX_SERVICE_SERVICE_HTTP_H
#define AZALYXCX_SERVICE_SERVICE_HTTP_H

#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>
#include <libsoup/soup.h>

void http_handle_request(SoupServer        *server,
                             SoupServerMessage *msg,
                             const char        *path,
                             GHashTable        *query,
                             gpointer           user_data);


#endif //AZALYXCX_SERVICE_SERVICE_HTTP_H
