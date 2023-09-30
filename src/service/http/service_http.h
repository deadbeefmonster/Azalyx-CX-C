

#ifndef AZALYXCX_SERVICE_SERVICE_HTTP_H
#define AZALYXCX_SERVICE_SERVICE_HTTP_H

#include <glib.h>
#include <glib/gi18n.h>
#include <gio/gio.h>

gboolean http_handle_request(GSocketService *service,
                             GSocketConnection *connection,
                             GObject *source_object,
                             gpointer user_data);


#endif //AZALYXCX_SERVICE_SERVICE_HTTP_H
