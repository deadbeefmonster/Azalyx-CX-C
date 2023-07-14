/* https://www.ietf.org/rfc/rfc1035.txt */


#include "service_dns.h"

void
service_dns_request_debug(struct dns_request *request) {
    g_debug("service_dns_request_debug(): request->header->id = %i", request->header->id);
    g_debug("service_dns_request_debug(): request->header->qr = %i", request->header->qr);
    g_debug("service_dns_request_debug(): request->header->opcode = %i", request->header->opcode);
    g_debug("service_dns_request_debug(): request->header->aa = %i", request->header->aa);
    g_debug("service_dns_request_debug(): request->header->tc = %i", request->header->tc);
    g_debug("service_dns_request_debug(): request->header->rd = %i", request->header->rd);
    g_debug("service_dns_request_debug(): request->header->ra = %i", request->header->ra);
    g_debug("service_dns_request_debug(): request->header->z = %i", request->header->z);
    g_debug("service_dns_request_debug(): request->header->rcode = %i", request->header->rcode);
    g_debug("service_dns_request_debug(): request->header->qdcount = %i", request->header->qdcount);
    g_debug("service_dns_request_debug(): request->header->ancount = %i", request->header->ancount);
    g_debug("service_dns_request_debug(): request->header->nscount = %i", request->header->nscount);
    g_debug("service_dns_request_debug(): request->header->arcount = %i", request->header->arcount);

    int i = (int) request->header->qdcount - 1;
    for(;i > -1; i--) {
        struct dns_question *question;
        question = g_array_index(request->questions, struct dns_question *, i);
        g_debug("service_dns_request_debug(): question->qname->str  = %s (idx = %i)", question->qname->str, i);
        g_debug("service_dns_request_debug(): question->qtype  = %i (idx = %i)", question->qtype, i);
        g_debug("service_dns_request_debug(): question->qclass = %i (idx = %i)", question->qclass, i);
    }
}

void
service_dns_request_parse(guchar *buffer,
                          struct dns_request *request,
                          glong request_size) {
    guint id, flags, qdcount, ancount, nscount, arcount;

    id = 0;
    flags = 0;
    qdcount = 0;
    ancount = 0;
    nscount = 0;
    arcount = 0;
    request->header->qr = 0;
    request->header->opcode = 0;
    request->header->aa = 0;
    request->header->tc = 0;
    request->header->rd = 0;
    request->header->ra = 0;
    request->header->z = 0;
    request->header->rcode = 0;

    /* HEADER */
    memcpy(&id, &buffer[0], 2);
    memcpy(&flags, &buffer[2], 2);
    memcpy(&qdcount, &buffer[4], 2);
    memcpy(&ancount, &buffer[6], 2);
    memcpy(&nscount, &buffer[8], 2);
    memcpy(&arcount, &buffer[10], 2);
    id = ntohs(id);
    flags = ntohs(flags);
    qdcount = ntohs(qdcount);
    ancount = ntohs(ancount);
    nscount = ntohs(nscount);
    arcount = ntohs(arcount);

    request->header->id = id;
    request->header->qdcount = qdcount;
    request->header->ancount = ancount;
    request->header->nscount = nscount;
    request->header->arcount = arcount;

    /* Mask the value and bit shift, so it is at the start of the bytes. */
    request->header->qr = (guint) flags & header_mask_qr;
    request->header->opcode = (guint) flags & header_mask_opcode;
    request->header->opcode = request->header->opcode >> 11;
    request->header->aa = (guint) flags & header_mask_aa;
    request->header->aa = request->header->aa >> 10;
    request->header->tc = (guint) flags & header_mask_tc;
    request->header->tc = request->header->tc >> 9;
    request->header->rd = (guint) flags & header_mask_rd;
    request->header->rd = request->header->rd >> 8;
    request->header->ra = (guint) flags & header_mask_ra;
    request->header->ra = request->header->ra >> 7;
    request->header->z = (guint) flags & header_mask_z;
    request->header->z = request->header->z >> 4;
    request->header->rcode = (guint) flags & header_mask_rcode;
    request->header->rcode = request->header->rcode >> 0;

//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->qr     = %.16x -> %.16x (%i)",
//            header_mask_qr,
//            request->header->qr,
//            request->header->qr);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->opcode = %.16x -> %.16x (%i)",
//            header_mask_opcode,
//            request->header->opcode,
//            request->header->opcode);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->aa     = %.16x -> %.16x (%i)",
//            header_mask_aa,
//            request->header->aa,
//            request->header->aa);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->tc     = %.16x -> %.16x (%i)",
//            header_mask_tc,
//            request->header->tc,
//            request->header->tc);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->rd     = %.16x -> %.16x (%i)",
//            header_mask_rd,
//            request->header->rd,
//            request->header->rd);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->ra     = %.16x -> %.16x (%i)",
//            header_mask_ra,
//            request->header->ra,
//            request->header->ra);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->z      = %.16x -> %.16x (%i)",
//            header_mask_z,
//            request->header->z,
//            request->header->z);
//    g_debug("flags                   = %.16x", flags);
//    g_debug("request->header->rcode  = %.16x -> %.16x (%i)",
//            header_mask_rcode,
//            request->header->rcode,
//            request->header->rcode);
//
//    g_debug("request->header->id        = %.16x, %i",
//            request->header->id,
//            request->header->id);
//    g_debug("request->header->qdcount   = %.16x, %i",
//            request->header->qdcount,
//            request->header->qdcount);
//    g_debug("request->header->ancount   = %.16x, %i",
//            request->header->ancount,
//            request->header->ancount);
//    g_debug("request->header->nscount   = %.16x, %i",
//            request->header->nscount,
//            request->header->nscount);
//    g_debug("request->header->arcount   = %.16x, %i",
//            request->header->arcount,
//            request->header->arcount);

    /* QUESTIONS */
    gint buffer_count = 12;
    gint qname_chunk_size = (gint) buffer[buffer_count];
    buffer_count++;
    for (qdcount = request->header->qdcount; qdcount > 0; qdcount--) {
        struct dns_question *question = g_slice_new(struct dns_question);
        GString *qname = g_string_new(NULL);

        while (qname_chunk_size != 0) {
            for (int i = 0; i < qname_chunk_size; i++) {
                char c = (char) buffer[buffer_count];
                buffer_count++;
                qname = g_string_append_c(qname, c);
            }
            qname_chunk_size = (gint) buffer[buffer_count];
            buffer_count++;
            if (qname_chunk_size != 0)
                g_string_append_c(qname, '.');
        }
        question->qname = qname;

//        g_debug("question->qname = %s", question->qname->str);

        question->qtype = (uint8_t) buffer[buffer_count];
        buffer_count++;
        question->qtype += (uint8_t) buffer[buffer_count];
        buffer_count++;

//        g_debug("question->qtype = %i", question->qtype);


        question->qclass = (uint8_t) buffer[buffer_count];
        buffer_count++;
        question->qclass += (uint8_t) buffer[buffer_count];
        buffer_count++;

//        g_debug("question->qclass = %i", question->qclass);


        g_array_append_val(request->questions, question);
    }
}

void
service_dns_request_process(struct dns_request *request) {
    g_debug("in service_dns_request_process");

    /* Iterate through each question */
    int i = (int) request->header->qdcount - 1;
    for(;i >= 0; i--) {
        struct dns_question *question;
        question = g_array_index(request->questions, struct dns_question *, i);

        g_debug("service_dns_request_process(): question->qtype = %i", question->qtype);

        if (question->qtype == DNS_QTYPE_A) {
            g_debug("A Request, expecting at least one IP for '%s'",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_AAAA) {
            g_debug("AAAA Request, expecting at least one IPv6 for '%s'",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_NS) {
            g_debug("NS Request, expecting at least one hostname or IP for '%s'",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_MD) {
        } else if (question->qtype == DNS_QTYPE_MF) {
        } else if (question->qtype == DNS_QTYPE_CNAME) {
            g_debug("CNAME Request, expecting at least one hostname or IP for '%s'",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_SOA) {
            g_debug("SOA Request for '%s', need to look this up how it works",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_MB) {
        } else if (question->qtype == DNS_QTYPE_MG) {
        } else if (question->qtype == DNS_QTYPE_MR) {
        } else if (question->qtype == DNS_QTYPE_NULL) {
        } else if (question->qtype == DNS_QTYPE_WKS) {
        } else if (question->qtype == DNS_QTYPE_PTR) {
        } else if (question->qtype == DNS_QTYPE_HINFO) {
        } else if (question->qtype == DNS_QTYPE_MINFO) {
        } else if (question->qtype == DNS_QTYPE_MX) {
            g_debug("MX Request, expecting at least one hostname or IP for '%s'",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_TXT) {
            g_debug("TXT Request for '%s', need to look this up how it works",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_AXFR) {
            g_debug(
                    "AXFR Request for '%s', need to look this up how it works... It should be TCP only",
                    question->qname->str);
        } else if (question->qtype == DNS_QTYPE_MAILB) {
        } else if (question->qtype == DNS_QTYPE_MAILA) {
        } else if (question->qtype == DNS_QTYPE_ALL) {
            g_debug(
                    "* Request for '%s', all the things?? need to look this up how it works",
                    question->qname->str);
        } else {
            g_warning("No idea what type of QTYPE this is: %i", question->qtype);
        }
    }
    g_debug("service_dns_request_process(): done processing");
}

void
service_dns_callback_conn_new(evutil_socket_t listener, short event, void *arg) {
    struct event_base *base;
    struct sockaddr_in server_sin;
    struct dns_request *request;
    socklen_t server_sz;
    guchar buffer[512] = {0};
    glong request_size;

    /* Initialize variables */
    base = arg;
    server_sz = sizeof(server_sin);
    request_size = 0;

    request = g_slice_new(struct dns_request);
    request->header = g_slice_new(struct dns_header);
    request->questions = g_array_new(FALSE, FALSE, sizeof(struct dns_question *));


    /* Read the request from the client, max 512 bytes for UDP */
    request_size = recvfrom(listener,
                            buffer,
                            512,
                            0,
                            (struct sockaddr *) &server_sin,
                            &server_sz);
    if (request_size == -1) {
        perror("recvfrom()");
        event_base_loopbreak(base);
        g_error("service_dns_callback_connection_new: recvfrom() failed");
    }
    /* Parse the request from a stream of bits to a usable data structure */
    service_dns_request_parse(buffer, request, request_size);
    service_dns_request_debug(request);

    /* Process the request data structure into a response data structure */
    service_dns_request_process(request);

    /* Process the response into a stream of bits to send back to the
     * client */
    /* XXX - inject data in here */


    /* Send the response back to the client */
    /* if (sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)
     * &server_sin, server_sz) == -1 ) { perror("sendto()");
     * event_base_loopbreak(base); } */



    /* Cleanup */
    if (request->questions)
        g_array_free(request->questions, TRUE);
    if (request->header)
        g_slice_free(struct dns_header, request->header);
    if (request)
        g_slice_free(struct dns_request, request);

}
