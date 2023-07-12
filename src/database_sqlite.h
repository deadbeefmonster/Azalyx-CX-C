
#ifndef BLITZKRIEG_DATABASE_SQLITE_H
#define BLITZKRIEG_DATABASE_SQLITE_H

#include <glib.h>
#include <glib/gi18n.h>
#include <sqlite3.h>

struct database_data_log {
    gint *id;
    GString *message;
    GString *scope;
    GString *subject;
    gint *create_ts;
};

struct database_data_session {
    gint id;
    GString *uuid;
    GString *data;
    gint create_ts;
    gint update_ts;
    gint expire_ts;
};

struct database_data_service {
    gint id;
    GString *name;
    GString *type;
    GString *proto;
    gint port;
    gboolean is_active;
    gint create_ts;
    gint update_ts;
};

struct database_data_request_response {
    gint session_id; // database_data_session->id
    gint service_id; // database_data_service->id
    GByteArray *request_bytes;
    GByteArray *response_bytes;
    GString *sender;
    GString *recipient;
    gint create_ts;
    gint update_ts;
};

struct database_data_envelope {
    gint id;
    GString *uuid;
    GByteArray *data_bytes;
    gint create_ts;
};

struct database_data_envelope_headers {
    gint id;
    GString *envelope_uuid; // database_data_envelope->uuid (one to many)
    GString *header_key;
    GString *header_value;
    gint create_ts;
};

struct database_data_envelope_body {
    gint id;
    GString *uuid;
    GString *envelope_uuid; // database_data_envelope->uuid (one to many)
    GByteArray *data_bytes;
    gint create_ts;
};

struct database_data_envelope_fault {
    gint id;
    GString uuid;
    GString envelope_uuid; // database_data_envelope->uuid (one to many)
    GString envelope_body_uuid; // database_data_envelope_body->uuid
    GByteArray data_bytes;
    gint create_ts;
};

struct database_data_envelope_chunk {
    gint64 id;
    GString envelope_uuid; // database_data_envelope->uuid (one to many)
    gint64 start_byte_position;
    gint64 chunk_size;
    gboolean is_transferred;
    gboolean is_acknowledged_required;
    gboolean is_acknowledged;
    gint create_ts;
    gint transferred_ts;
    gint acknowledged_ts;
};

struct database_data_queue {
    gint id;
    GString *session_uuid; // database_data_session->uuid
    GByteArray *data_bytes;
    gint create_ts;
    gint update_ts;
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
struct database_data_envelope_headers* database_get_envelope_headers_by_envelope(struct database_data_envelope*);

gboolean database_set_envelope_body(struct database_data_envelope_body*);
struct database_data_envelope_body* database_get_envelope_body_by_id(gint);
struct database_data_envelope_body* database_get_envelope_body_by_envelope(struct database_data_envelope*);

gboolean database_set_envelope_fault(struct database_data_envelope_fault*);
struct database_data_envelope_fault* database_get_envelope_fault_by_id(gint);
struct database_data_envelope_fault* database_get_envelope_fault_by_envelope(struct database_data_envelope*);
struct database_data_envelope_fault* database_get_envelope_fault_by_envelope_body(struct database_data_envelope_body*);

gboolean database_set_envelope_chunk(struct database_data_envelope_chunk*);
struct database_data_envelope_chunk* database_get_envelope_chunk_by_id(gint);
struct database_data_envelope_chunk* database_get_envelope_chunk_by_envelope(struct database_data_envelope*);

gboolean database_set_queue(struct database_data_queue*);
struct database_data_queue* database_get_queue_by_id(gint);


#endif //BLITZKRIEG_DATABASE_SQLITE_H
