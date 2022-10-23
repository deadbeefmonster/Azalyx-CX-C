//
// Created by Chris Humphries on 7/11/22.
//

#ifndef BLITZKRIEG_SERVICE_SMTP_H
#define BLITZKRIEG_SERVICE_SMTP_H

#include <glib.h>
#include <glib/gi18n.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <unistd.h>

#define MAX_LINE 16384

void service_smtp_callback_connection_new(evutil_socket_t listener,
		short event,
		void* arg);

void service_smtp_callback_error(struct bufferevent* bev,
		short error,
		void* ctx);

void service_smtp_callback_read(struct bufferevent* bev, void* ctx);

#endif //BLITZKRIEG_SERVICE_SMTP_H
