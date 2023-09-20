/*
 * Note:
 * - all timestamps are stored and passed around in structs as epoch integers.
 * - uuid will be generated via https://docs.gtk.org/glib/func.uuid_string_random.html
 * - uuid will be used when referencing things
 *
 */


#ifndef AZALYXCX_DATABASE_SQLITE_H
#define AZALYXCX_DATABASE_SQLITE_H

#include <glib.h>
#include <glib/gi18n.h>
#include <sqlite3.h>

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
    GString *envelope_uuid; /* References database_data_envelope.uuid */
    GByteArray *data_bytes;
    guint32 create_ts;
};

/* Table: envelope_chunk */
struct database_data_envelope_chunk {
    guint32 id;
    GString *envelope_uuid; /* References database_data_envelope.uuid */
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
    GString *envelope_uuid; /* References database_data_envelope.uuid */
    GString *envelope_body_uuid;
    GByteArray *data_bytes;
    guint32 create_ts;
};

/* Table: envelope_headers */
struct database_data_envelope_headers {
    guint32 id;
    GString *envelope_uuid; /* References database_data_envelope.uuid */
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
    GString *session_uuid; /* References database_data_session.uuid */
    GByteArray *data_bytes;
    guint32 create_ts;
    guint32 update_ts;
};

/* Table: request_response */
struct database_data_request_response {
    guint32 id;
    GString *session_uuid; /* References database_data_session.uuid */
    GString *service_uuid; /* References database_data_service.uuid */
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


gboolean database_set_log(struct database_data_log*);
struct database_data_log* database_get_log_by_id(gint);

gboolean database_set_session(struct database_data_session*);
struct database_data_session* database_get_session_by_id(gint);
struct database_data_session* database_get_session_by_uuid(GString*);

gboolean database_set_service(struct database_data_service*);
struct database_data_service* database_get_service_by_id(gint);

gboolean database_set_request_response(struct database_data_request_response*);
struct database_data_request_response* database_get_request_response_by_id(gint);

gboolean database_set_envelope(struct database_data_envelope*);
struct database_data_envelope* database_get_envelope_by_id(gint);
struct database_data_envelope* database_get_envelope_by_uuid(GString*);

gboolean database_set_envelope_headers(struct database_data_envelope_headers*);
struct database_data_envelope_headers* database_get_envelope_headers_by_id(gint);
// Returns a GArray of struct database_data_envelope_headers*
GArray* database_get_envelope_headers_by_envelope(struct database_data_envelope*);
gboolean database_get_envelope_headers_by_envelope_free(GArray*);

gboolean database_set_envelope_body(struct database_data_envelope_body*);
struct database_data_envelope_body* database_get_envelope_body_by_id(gint);
// Returns a GArray of struct database_data_envelope_body*
GArray * database_get_envelope_body_by_envelope(struct database_data_envelope*);
gboolean database_get_envelope_body_by_envelope_free(GArray*);

gboolean database_set_envelope_fault(struct database_data_envelope_fault*);
struct database_data_envelope_fault* database_get_envelope_fault_by_id(gint);
// Returns a GArray of struct database_data_envelope_fault*
GArray * database_get_envelope_fault_by_envelope(struct database_data_envelope*);
gboolean database_get_envelope_fault_by_envelope_free(GArray*);
// Returns a GArray of struct database_data_envelope_fault*
GArray * database_get_envelope_fault_by_envelope_body(struct database_data_envelope_body*);
gboolean database_get_envelope_fault_by_envelope_body_free(GArray*); // Same thing, convenience


gboolean database_set_envelope_chunk(struct database_data_envelope_chunk*);
struct database_data_envelope_chunk* database_get_envelope_chunk_by_id(gint);
// Returns a GArray of struct database_data_envelope_chunk*
GArray* database_get_envelope_chunk_by_envelope(struct database_data_envelope*);
gboolean database_get_envelope_chunk_by_envelope_free(GArray*);

gboolean database_set_queue(struct database_data_queue*);
struct database_data_queue* database_get_queue_by_id(gint);
// Returns a GArray of struct database_data_queue*
GArray * database_get_queue_by_session(struct database_data_session*);
gboolean database_get_queue_by_session_free(GArray*);



#endif //AZALYXCX_DATABASE_SQLITE_H
