
#include "service/http/service_http.h"


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


    soup_server_message_set_status (msg, SOUP_STATUS_OK, NULL);
    GString *reply = g_string_new("Hello World from Soup!");
    soup_server_message_set_response (msg, "text/html", SOUP_MEMORY_COPY,
                                      reply->str, reply->len);

    g_debug ("http_handle_request(): -> %d %s\n\n", soup_server_message_get_status (msg), soup_server_message_get_reason_phrase (msg));

}