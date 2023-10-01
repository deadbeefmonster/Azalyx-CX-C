
#include <stdio.h>
#include "service/http/service_http.h"


// gboolean http_handle_request(GSocketService *service,
//                              GSocketConnection *connection,
//                              GObject *source_object,
//                              gpointer user_data) {
//
//    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
//    gchar message[10000] = {0};
//    g_input_stream_read  (istream,
//                          message,
//                          10000,
//                          NULL,
//                          NULL);
//    g_debug("http_handle_request(): Message was: \"%s\"\n", message);
//
//    GOutputStream *ostream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
//    GString *reply = g_string_new("Hello World.");
//    g_output_stream_write(ostream, reply->str, reply->len, NULL, NULL);
//
//    return(TRUE);
//}

void http_handle_request(SoupServer        *server,
                             SoupServerMessage *msg,
                             const char        *path,
                             GHashTable        *query,
                             gpointer           user_data) {
    char *file_path;
    SoupMessageHeadersIter iter;
    SoupMessageBody *request_body;
    const char *name, *value;

    g_debug ("http_handle_request(): %s %s HTTP/1.%d", soup_server_message_get_method (msg), path,
             soup_server_message_get_http_version (msg));
    soup_message_headers_iter_init (&iter, soup_server_message_get_request_headers (msg));
    while (soup_message_headers_iter_next (&iter, &name, &value))
        g_debug ("http_handle_request(): %s: %s", name, value);

    request_body = soup_server_message_get_request_body (msg);
    if (request_body->length)
        g_debug ("http_handle_request(): %s", request_body->data);

    g_debug("http_handle_request(): path = %s", path);
//    file_path = g_strdup_printf (".%s", path);

//    if (soup_server_message_get_method (msg) == SOUP_METHOD_GET || soup_server_message_get_method (msg) == SOUP_METHOD_HEAD)
//        do_get (server, msg, file_path);
//    else if (soup_server_message_get_method (msg) == SOUP_METHOD_PUT)
//        do_put (server, msg, file_path);
//    else
//        soup_server_message_set_status (msg, SOUP_STATUS_NOT_IMPLEMENTED, NULL);

    soup_server_message_set_status (msg, SOUP_STATUS_OK, NULL);
    GString *reply = g_string_new("Hello World from Soup!");
    soup_server_message_set_response (msg, "text/html", SOUP_MEMORY_COPY,
                                      reply->str, reply->len);

    g_debug ("http_handle_request(): -> %d %s\n\n", soup_server_message_get_status (msg), soup_server_message_get_reason_phrase (msg));

}