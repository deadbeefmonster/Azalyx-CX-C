#include "service.h"

struct service_data *
service_generate(gint service_type,
                 gint service_proto,
                 gint port,
                 struct event_base *base) {
    struct service_data *data;
    evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event *listener_event;

    data = g_slice_new(struct service_data);
    data->service_type = service_type;
    data->service_proto = service_proto;
    data->port = port;

    g_debug("service_type=%i", data->service_type);
    g_debug("service_proto=%i", data->service_proto);
    g_debug("port=%i", data->port);

    /* Create socket */
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;/* XXX support specifying the IP address to bind on */
    sin.sin_port = htons(port);
    if (service_proto == SERVICE_PROTO_TCP) {
        listener = socket(AF_INET, SOCK_STREAM, 0);
    } else if (service_proto == SERVICE_PROTO_UDP) {
        listener = socket(AF_INET, SOCK_DGRAM, 0);
    } else {
        fprintf(stderr, "Unable to discern service proto '%i'\n", service_proto);
        exit(EXIT_FAILURE);
    }
    evutil_make_socket_nonblocking(listener);
    data->socket = listener;

    /* Bind the socket */
    g_debug("Calling bind()");
    if (bind(listener, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        /* XXX - Extract this out to a specific error handler that is more dynamic */
        GString *service_type_str;
        GString *service_proto_str;
        if (service_type == SERVICE_TYPE_DNS) {
            service_type_str = g_string_new("DNS");
        } else if (service_type == SERVICE_TYPE_HTTP) {
            service_type_str = g_string_new("HTTP");
        } else if (service_type == SERVICE_TYPE_SMTP) {
            service_type_str = g_string_new("SMTP");
        }
        else {
            service_type_str = g_string_new("UNKNOWN");
        }
        if (service_proto == SERVICE_PROTO_TCP) {
            service_proto_str = g_string_new("TCP");
        }
        else if (service_proto == SERVICE_PROTO_UDP) {
            service_proto_str = g_string_new("UDP");
        } else {
            service_proto_str = g_string_new("UNKNOWN");
        }
        fprintf(stderr, "FATAL ERROR: bind() failed for proto %s service %s on port %i\n", service_proto_str->str, service_type_str->str, port);
        exit(EXIT_FAILURE);
    } else {
        g_debug("bind() passed");
    }
    data->sin = sin;

    if (service_proto == SERVICE_PROTO_TCP) {
        g_debug("Calling listen()");
        if (listen(listener, 16) < 0) {
            perror("listen()");
            fprintf(stderr, "FATAL ERROR: unable to list on TCP port %i socket\n", port);
            exit(EXIT_FAILURE);
        } else {
            g_debug("listen() passed");
        }
    }
    /* Register callbacks to libevent */
    if (data->service_type == SERVICE_TYPE_DNS) {
        g_debug("Adding listener for DNS");
        listener_event = event_new(base,
                                   listener,
                                   EV_READ | EV_PERSIST,
                                   service_dns_callback_conn_new,
                                   (void *) base);
    } else if (data->service_type == SERVICE_TYPE_SMTP) {
        g_debug("Adding listener for SMTP");
        listener_event = event_new(base,
                                   listener,
                                   EV_READ | EV_PERSIST,
                                   service_smtp_callback_connection_new,
                                   (void *) base);
    } else if (data->service_type == SERVICE_TYPE_HTTP) {
        g_debug("Adding listener for HTTP");
        listener_event = event_new(base,
                                   listener,
                                   EV_READ | EV_PERSIST,
                                   service_http_callback_connection_new,
                                   (void *) base);
    } else {
        fprintf(stderr, "FATAL ERROR: Unable to discern service type when setting up libevent listener events\n");
        exit(EXIT_FAILURE);
    }
    g_debug("Adding listener event");
    event_add(listener_event, NULL);

    return (data);
}
