/*
 * Note:
 * - all timestamps are stored and passed around in structs as epoch integers.
 * - uuid will be generated via https://docs.gtk.org/glib/func.uuid_string_random.html
 * - uuid will be used when referencing things
 *
 */


#ifndef AZALYXCX_DATABASE_DATABASE_H
#define AZALYXCX_DATABASE_DATABASE_H

#include <glib.h>
#include <glib/gi18n.h>

/* Table: envelope */
struct database_data_envelope {
	guint32 id;
	GString *uuid;
	GByteArray *data_bytes;
	guint32 create_ts;
};
/* Table: envelope_body */
struct database_data_envelope_body {
	guint32 id;
	GString *uuid;
	GString *envelope_uuid;	/* References database_data_envelope.uuid */
	GByteArray *data_bytes;
	guint32 create_ts;
};
/* Table: envelope_chunk */
struct database_data_envelope_chunk {
	guint32 id;
	GString *envelope_uuid;	/* References database_data_envelope.uuid */
	guint32 start_byte_position;
	guint32 chunk_size;
	gboolean is_transferred;
	gboolean is_acknowledged_required;
	gboolean is_acknowledged;
	guint32 create_ts;
	guint32 transferred_ts;
	guint32 acknowledged_ts;
};
/* Table: envelope_fault */
struct database_data_envelope_fault {
	guint32 id;
	GString *uuid;
	GString *envelope_uuid;	/* References database_data_envelope.uuid */
	GString *envelope_body_uuid;
	GByteArray *data_bytes;
	guint32 create_ts;
};
/* Table: envelope_headers */
struct database_data_envelope_headers {
	guint32 id;
	GString *envelope_uuid;	/* References database_data_envelope.uuid */
	GString *header_key;
	GString *header_value;
	guint32 create_ts;
};
/* Table: log */
struct database_data_log {
	guint32 id;
	GString *message;
	GString *scope;
	GString *subject;
	guint32 create_ts;
};
/* Table: queue */
struct database_data_queue {
	guint32 id;
	GString *session_uuid;	/* References database_data_session.uuid */
	GByteArray *data_bytes;
	guint32 create_ts;
	guint32 update_ts;
};
/* Table: request_response */
struct database_data_request_response {
	guint32 id;
	GString *session_uuid;	/* References database_data_session.uuid */
	GString *service_uuid;	/* References database_data_service.uuid */
	GByteArray *request_bytes;
	GByteArray *response_bytes;
	GString *sender;
	GString *recipient;
	guint32 create_ts;
	guint32 update_ts;
};
/* Table: service */
struct database_data_service {
	guint32 id;
	GString *uuid;
	GString *name;
	GString *type;
	GString *proto;
	guint32 port;
	gboolean is_active;
	guint32 create_ts;
	guint32 update_ts;
};
/* Table: session */
struct database_data_session {
	guint32 id;
	GString *uuid;
	GString *data;
	guint32 create_ts;
	guint32 update_ts;
	guint32 expire_ts;
};




#endif				/* AZALYXCX_DATABASE_DATABASE_H */
