//
// Created by Chris Humphries on 7/11/22.
//

#ifndef AZALYXCX_SERVICE_H
#define AZALYXCX_SERVICE_H

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>

#include "service_dns.h"
#include "service_http.h"
#include "service_smtp.h"

#define SERVICE_STATUS_UNKNOWN 0
#define SERVICE_STATUS_DISABLED 1
#define SERVICE_STATUS_ENABLED 2

#define SERVICE_PROTO_TCP 1
#define SERVICE_PROTO_UDP 2
/*#define SERVICE_PROTO_UNIX  4*/

#define SERVICE_TYPE_DNS 1
#define SERVICE_TYPE_SMTP 2
#define SERVICE_TYPE_HTTP 4
/*#define SERVICE_TYPE_UNIX    8*/

struct service_data {
    gint service_proto;
    gint service_type;
    gint port;
    evutil_socket_t socket;
    struct sockaddr_in sin;
};

struct service_data *service_generate(gint, gint, gint, struct event_base *);

#endif //AZALYXCX_SERVICE_H
