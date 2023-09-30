
#include <stdio.h>
#include "service/http/service_http.h"


 gboolean http_handle_request(GSocketService *service,
                              GSocketConnection *connection,
                              GObject *source_object,
                              gpointer user_data) {

    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
    gchar message[10000] = {0};
    g_input_stream_read  (istream,
                          message,
                          10000,
                          NULL,
                          NULL);
    g_debug("http_handle_request(): Message was: \"%s\"\n", message);

    GOutputStream *ostream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    GString *reply = g_string_new("Hello World.");
    g_output_stream_write(ostream, reply->str, reply->len, NULL, NULL);

    return(TRUE);
}