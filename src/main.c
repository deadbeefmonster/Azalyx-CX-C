#define G_LOG_USE_STRUCTURED 1

#include <glib.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <stdlib.h>

#include "cli_arguments.h"
#include "configuration.h"
#include "crypto_aes.h"
#include "service.h"

GString* bytes_to_hex(unsigned char* bytes, int bytes_len)
{
	GString* hex_data = g_string_new("");
	char hex_datum[2] = {0};

	for (int i = 0; i!=bytes_len; i++) {
		snprintf(hex_datum, 2, "%02hhX", bytes[i]);
		g_string_append(hex_data, hex_datum);
	}

	return hex_data;
}

int
main(int argc, char** argv)
{
	gchar** cli_args;    /* CLI arguments */
	struct settings* conf = g_slice_new(struct settings);    /* All settings */
	struct event_base* base;/* LibEvent */
	GArray* ServiceDatas = g_array_new(FALSE, FALSE, sizeof(struct server_data*));    /* Services */

	/* Init glib */
	g_log_set_handler(G_LOG_DOMAIN,
			G_LOG_LEVEL_MASK,
			g_log_default_handler,
			NULL);

	/* Init libevent */
	base = event_base_new();
	if (!base)
		g_error("event_base_new() failed");

	/* Init configuration */
	conf->configuration_file = "Azalyx_CX.ini";
	conf->service_enable_dns = SERVICE_STATUS_UNKNOWN;
	conf->service_enable_http = SERVICE_STATUS_UNKNOWN;
	conf->service_enable_smtp = SERVICE_STATUS_UNKNOWN;

	/* Read command line arguments */
	cli_args = g_strdupv(argv);
	cli_arguments_parse(cli_args, conf);
	g_strfreev(cli_args);

	/* Configuration file handling */
	load_configuration_file(conf);


	/*
	 * TESTING STUFF
	 */
	unsigned char* plaintext, * plaintext2, * ciphertext;
	int plaintext_len, ciphertext_len, plaintext2_len;
	struct aes_key* aes_key;

	aes_key = g_slice_new(struct aes_key);
	ciphertext = g_slice_alloc0(plaintext_len*2);

	plaintext = (unsigned char*)"Hello, this is just a test!";
	plaintext_len = strlen((const char*)plaintext)+1;
	plaintext2 = malloc(plaintext_len);

	g_debug("creating random key and iv");
	if (1!=aes_generate_new_key_iv(aes_key)) {
		g_error("aes_generate_new_key_iv() failed!");
	}
	g_debug("done creating random key and iv");
	g_debug("calling bytes_to_hex");
	GString* aes_key_key_bytes = bytes_to_hex(aes_key->key, 32);
	g_debug("aes_key->key=%s", aes_key_key_bytes->str);
	g_debug("calling bytes_to_hex");
	GString* aes_key_iv_bytes = bytes_to_hex(aes_key->iv, 16);
	g_debug("aes_key->iv=%s", aes_key_iv_bytes->str);


//  g_debug(aes_key->iv);
	g_debug("encrypting plaintext: %s", plaintext);
	ciphertext_len = aes_encrypt(plaintext, plaintext_len, aes_key, ciphertext);
	g_debug("ciphertext_len=%i", ciphertext_len);

	g_debug("calling bytes_to_hex");
	GString* ciphertext_bytes = bytes_to_hex(ciphertext, ciphertext_len);
	g_debug("ciphertext_bytes=%s", ciphertext_bytes->str);

	g_debug("decrypting ciphertext now");
	//int aes_decrypt(unsigned char *ciphertext, int ciphertext_len, struct aes_key *aes_key, unsigned char *plaintext) {
	plaintext2_len = aes_decrypt(ciphertext, ciphertext_len, aes_key, plaintext2);
	g_debug("plaintext2=%s", plaintext2);
	g_slice_free1(plaintext_len*2, ciphertext);
	free(plaintext2);
	g_slice_free(struct aes_key, aes_key);

	/* Service provisioning, setup, and registering. - Create sockets,
	 * register callbacks */
	/* TODO: plugin hook */
	if (conf->service_enable_dns==SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		struct service_data* service_data_dns;
		service_data_dns =
				service_generate(SERVICE_TYPE_DNS, SERVICE_PROTO_UDP, 53, base);
		g_array_append_val(ServiceDatas, service_data_dns);
		g_info("Service DNS Loaded");

		/* TODO: plugin hook */
	}
	if (conf->service_enable_http==SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		struct service_data* service_data_http;
		service_data_http =
				service_generate(SERVICE_TYPE_HTTP, SERVICE_PROTO_TCP, 80, base);
		g_array_append_val(ServiceDatas, service_data_http);
		g_info("Service HTTP Loaded");

		/* TODO: plugin hook */
	}
	if (conf->service_enable_smtp==SERVICE_STATUS_ENABLED) {
		/* TODO: plugin hook */

		struct service_data* service_data_smtp;
		service_data_smtp =
				service_generate(SERVICE_TYPE_SMTP, SERVICE_PROTO_TCP, 25, base);
		g_array_append_val(ServiceDatas, service_data_smtp);
		g_info("Service SMTP Loaded");

		/* TODO: plugin hook */
	}
	/* TODO: plugin_hook */

	/* TODO: plugin hook */
	event_base_dispatch(base);
	/* TODO: plugin hook */

	/* Cleanup */
	/* XXX - Close all sockets */
	if (conf)
		g_slice_free(struct settings, conf);
	if (ServiceDatas)
		g_array_free(ServiceDatas, TRUE);

	return (EXIT_SUCCESS);
}
