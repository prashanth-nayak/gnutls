/*
 *  Copyright (C) 2003 Nikos Mavroyanopoulos
 *
 *  This file is part of GNUTLS.
 *
 *  The GNUTLS library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public   
 *  License as published by the Free Software Foundation; either 
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 */

/* This file contains the types and prototypes for the X.509
 * certificate and CRL parsing functions.
 */

#ifndef GNUTLS_X509_H
# define GNUTLS_X509_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gnutls/gnutls.h>

/* Some OIDs usually found in Distinguished names
 */
#define GNUTLS_OID_X520_COUNTRY_NAME		"2.5.4.6"
#define GNUTLS_OID_X520_ORGANIZATION_NAME	"2.5.4.10"
#define GNUTLS_OID_X520_ORGANIZATIONAL_UNIT_NAME "2.5.4.11"
#define GNUTLS_OID_X520_COMMON_NAME 		"2.5.4.3"
#define GNUTLS_OID_X520_LOCALITY_NAME 		"2.5.4.7"
#define GNUTLS_OID_X520_STATE_OR_PROVINCE_NAME 	"2.5.4.8"
#define GNUTLS_OID_LDAP_DC			"0.9.2342.19200300.100.1.25"
#define GNUTLS_OID_LDAP_UID			"0.9.2342.19200300.100.1.1"
#define GNUTLS_OID_PKCS9_EMAIL 			"1.2.840.113549.1.9.1"

/* Certificate handling functions */
                      

int gnutls_x509_crt_init(gnutls_x509_crt * cert);
void gnutls_x509_crt_deinit(gnutls_x509_crt cert);
int gnutls_x509_crt_import(gnutls_x509_crt cert, const gnutls_datum * data,
	gnutls_x509_crt_fmt format);
int gnutls_x509_crt_export( gnutls_x509_crt cert,
	gnutls_x509_crt_fmt format, unsigned char* output_data, size_t* output_data_size);
int gnutls_x509_crt_get_issuer_dn(gnutls_x509_crt cert, char *buf,
	 size_t *sizeof_buf);
int gnutls_x509_crt_get_issuer_dn_by_oid(gnutls_x509_crt cert, 
	const char* oid, int indx, char *buf, size_t *sizeof_buf);
int gnutls_x509_crt_get_dn(gnutls_x509_crt cert, char *buf,
	 size_t *sizeof_buf);
int gnutls_x509_crt_get_dn_by_oid(gnutls_x509_crt cert, 
	const char* oid, int indx, char *buf, size_t *sizeof_buf);
int gnutls_x509_crt_check_hostname(gnutls_x509_crt cert,
                                const char *hostname);

int gnutls_x509_crt_get_signature_algorithm(gnutls_x509_crt cert);
int gnutls_x509_crt_get_version(gnutls_x509_crt cert);
int gnutls_x509_crt_get_key_id( gnutls_x509_crt crt, unsigned int flags,
	unsigned char* output_data, size_t* output_data_size);


time_t gnutls_x509_crt_get_activation_time(gnutls_x509_crt cert);
time_t gnutls_x509_crt_get_expiration_time(gnutls_x509_crt cert);
int gnutls_x509_crt_get_serial(gnutls_x509_crt cert, char* result, size_t* result_size);

int gnutls_x509_crt_get_pk_algorithm( gnutls_x509_crt cert, unsigned int* bits);
int gnutls_x509_crt_get_subject_alt_name(gnutls_x509_crt cert, 
	int seq, char *ret, size_t *ret_size, unsigned int* critical);
int gnutls_x509_crt_get_ca_status(gnutls_x509_crt cert, unsigned int* critical);

int gnutls_x509_crt_get_key_usage( gnutls_x509_crt cert, unsigned int* key_usage,
	unsigned int* critical);

int gnutls_x509_oid_known(const char* oid);

/* key_usage will be an OR of the following values:
 */
#define GNUTLS_KEY_DIGITAL_SIGNATURE 		256
#define GNUTLS_KEY_NON_REPUDIATION		128
#define GNUTLS_KEY_KEY_ENCIPHERMENT		64
#define GNUTLS_KEY_DATA_ENCIPHERMENT		32
#define GNUTLS_KEY_KEY_AGREEMENT		16
#define GNUTLS_KEY_KEY_CERT_SIGN		8
#define GNUTLS_KEY_CRL_SIGN			4
#define GNUTLS_KEY_ENCIPHER_ONLY		2
#define GNUTLS_KEY_DECIPHER_ONLY		1

int gnutls_x509_crt_get_extension_by_oid(gnutls_x509_crt cert, 
	const char* oid, int indx,
	unsigned char* buf, size_t * sizeof_buf, unsigned int * critical);

int gnutls_x509_crt_to_xml(gnutls_x509_crt cert, gnutls_datum* res, int detail);

/* possible values for detail.
 */
#define GNUTLS_XML_SHOW_ALL 1
#define GNUTLS_XML_NORMAL 0

/* X.509 Certificate writing.
 */
int gnutls_x509_crt_set_dn_by_oid(gnutls_x509_crt crt, const char* oid, 
	const char *name, unsigned int sizeof_name);
int gnutls_x509_crt_set_issuer_dn_by_oid(gnutls_x509_crt crt, const char* oid, 
	const char *name, unsigned int sizeof_name);
int gnutls_x509_crt_set_version(gnutls_x509_crt crt, unsigned int version);
int gnutls_x509_crt_set_key(gnutls_x509_crt crt, gnutls_x509_privkey key);
int gnutls_x509_crt_set_ca_status(gnutls_x509_crt crt, unsigned int ca);
int gnutls_x509_crt_set_subject_alternative_name(gnutls_x509_crt crt, gnutls_x509_subject_alt_name type,
	const char* data_string);
int gnutls_x509_crt_sign(gnutls_x509_crt crt, gnutls_x509_crt issuer, 
	gnutls_x509_privkey issuer_key);
int gnutls_x509_crt_set_activation_time(gnutls_x509_crt cert, time_t act_time);
int gnutls_x509_crt_set_expiration_time(gnutls_x509_crt cert, time_t exp_time);
int gnutls_x509_crt_set_serial(gnutls_x509_crt cert, const unsigned char* serial, 
	size_t serial_size);


/* RDN handling 
 */
int gnutls_x509_rdn_get(const gnutls_datum * idn,
				  char *buf, size_t *sizeof_buf);

int gnutls_x509_rdn_get_by_oid(const gnutls_datum * idn, const char* oid,
	int indx, char *buf, size_t *sizeof_buf);


/* CRL handling functions */


int gnutls_x509_crl_init(gnutls_x509_crl * crl);
void gnutls_x509_crl_deinit(gnutls_x509_crl crl);

int gnutls_x509_crl_import(gnutls_x509_crl crl, const gnutls_datum * data, 
	gnutls_x509_crt_fmt format);
int gnutls_x509_crl_export( gnutls_x509_crl crl,
	gnutls_x509_crt_fmt format, unsigned char* output_data, size_t* output_data_size);

int gnutls_x509_crl_get_issuer_dn(const gnutls_x509_crl crl, 
	char *buf, size_t *sizeof_buf);
int gnutls_x509_crl_get_issuer_dn_by_oid(gnutls_x509_crl crl, 
	const char* oid, int indx, char *buf, size_t *sizeof_buf);

int gnutls_x509_crl_get_signature_algorithm(gnutls_x509_crl crl);
int gnutls_x509_crl_get_version(gnutls_x509_crl crl);

time_t gnutls_x509_crl_get_this_update(gnutls_x509_crl crl);
time_t gnutls_x509_crl_get_next_update(gnutls_x509_crl crl);

int gnutls_x509_crl_get_crt_count(gnutls_x509_crl crl);
int gnutls_x509_crl_get_crt_serial(gnutls_x509_crl crl, int index, unsigned char* serial,
        size_t* serial_size, time_t* time);
#define gnutls_x509_crl_get_certificate_count gnutls_x509_crl_get_crt_count
#define gnutls_x509_crl_get_certificate gnutls_x509_crl_get_crt_serial

int gnutls_x509_crl_check_issuer( gnutls_x509_crl crl,
	gnutls_x509_crt issuer);

/* PKCS7 structures handling 
 */

struct gnutls_pkcs7_int;
typedef struct gnutls_pkcs7_int* gnutls_pkcs7;


int gnutls_pkcs7_init(gnutls_pkcs7 * pkcs7);
void gnutls_pkcs7_deinit(gnutls_pkcs7 pkcs7);
int gnutls_pkcs7_import(gnutls_pkcs7 pkcs7, const gnutls_datum * data,
	gnutls_x509_crt_fmt format);
int gnutls_pkcs7_export( gnutls_pkcs7 pkcs7,
	gnutls_x509_crt_fmt format, unsigned char* output_data, size_t* output_data_size);

int gnutls_pkcs7_get_crt_count( gnutls_pkcs7 pkcs7);
int gnutls_pkcs7_get_crt_raw(gnutls_pkcs7 pkcs7, int indx, 
	unsigned char* certificate, size_t* certificate_size);

int gnutls_pkcs7_set_crt_raw(gnutls_pkcs7 pkcs7, const gnutls_datum* crt);
int gnutls_pkcs7_set_crt(gnutls_pkcs7 pkcs7, gnutls_x509_crt crt);
int gnutls_pkcs7_delete_crt(gnutls_pkcs7 pkcs7, int indx);

int gnutls_pkcs7_get_crl_raw(gnutls_pkcs7 pkcs7, 
	int indx, unsigned char* crl, size_t* crl_size);
int gnutls_pkcs7_get_crl_count(gnutls_pkcs7 pkcs7);

int gnutls_pkcs7_set_crl_raw(gnutls_pkcs7 pkcs7, const gnutls_datum* crt);
int gnutls_pkcs7_set_crl(gnutls_pkcs7 pkcs7, gnutls_x509_crl crl);
int gnutls_pkcs7_delete_crl(gnutls_pkcs7 pkcs7, int indx);

/* X.509 Certificate verification functions.
 */

typedef enum gnutls_certificate_verify_flags {
	GNUTLS_VERIFY_DISABLE_CA_SIGN=1, /* if set a signer does not have to be
					 * a certificate authority.
					 */
	GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT=2 /* Allow CA certificates that have version 1.
					      * This might be dangerous since those haven't
					      * the basicConstraints extension.
					      */
} gnutls_certificate_verify_flags;

int gnutls_x509_crt_check_issuer( gnutls_x509_crt cert,
	gnutls_x509_crt issuer);

int gnutls_x509_crt_list_verify( gnutls_x509_crt* cert_list, int cert_list_length, 
	gnutls_x509_crt * CA_list, int CA_list_length, 
	gnutls_x509_crl* CRL_list, int CRL_list_length, 
	unsigned int flags, unsigned int *verify);

int gnutls_x509_crt_verify( gnutls_x509_crt cert,
	gnutls_x509_crt *CA_list, int CA_list_length,
	unsigned int flags, unsigned int *verify);
int gnutls_x509_crl_verify( gnutls_x509_crl crl,
	gnutls_x509_crt *CA_list, int CA_list_length,
	unsigned int flags, unsigned int *verify);

int gnutls_x509_crt_check_revocation(gnutls_x509_crt cert,
					     gnutls_x509_crl * crl_list,
					     int crl_list_length);

int gnutls_x509_crt_get_fingerprint(gnutls_x509_crt cert, 
	gnutls_digest_algorithm algo, char *buf,
	size_t *sizeof_buf);

/* Private key handling
 */

/* Flags for the gnutls_x509_privkey_export_pkcs8() function.
 */
typedef enum gnutls_pkcs_encrypt_flags {
	GNUTLS_PKCS_PLAIN=1,  /* if set the private key will not
			        * be encrypted.
				*/
	GNUTLS_PKCS_USE_PKCS12_3DES=2,
	GNUTLS_PKCS_USE_PKCS12_ARCFOUR=4,
	GNUTLS_PKCS_USE_PKCS12_RC2_40=8,
	GNUTLS_PKCS_USE_PBES2_3DES=16
} gnutls_pkcs_encrypt_flags;

#define GNUTLS_PKCS8_PLAIN GNUTLS_PKCS_PLAIN
#define GNUTLS_PKCS8_USE_PKCS12_3DES GNUTLS_PKCS_USE_PKCS12_3DES
#define GNUTLS_PKCS8_USE_PKCS12_ARCFOUR GNUTLS_PKCS_USE_PKCS12_ARCFOUR
#define GNUTLS_PKCS8_USE_PKCS12_RC2_40 GNUTLS_PKCS_USE_PKCS12_RC2_40

int gnutls_x509_privkey_init(gnutls_x509_privkey * key);
void gnutls_x509_privkey_deinit(gnutls_x509_privkey key);
int gnutls_x509_privkey_import(gnutls_x509_privkey key, const gnutls_datum * data,
	gnutls_x509_crt_fmt format);
int gnutls_x509_privkey_import_pkcs8(gnutls_x509_privkey key, const gnutls_datum * data,
	gnutls_x509_crt_fmt format, const char * pass, unsigned int flags);
int gnutls_x509_privkey_import_rsa_raw(gnutls_x509_privkey privkey, 
	const gnutls_datum *m, const gnutls_datum *e,
	const gnutls_datum *d, const gnutls_datum *p, const gnutls_datum *q, 
	const gnutls_datum *u);
int gnutls_x509_privkey_get_pk_algorithm( gnutls_x509_privkey key);
int gnutls_x509_privkey_get_key_id( gnutls_x509_privkey key, unsigned int flags,
	unsigned char* output_data, size_t* output_data_size);

int gnutls_x509_privkey_generate( gnutls_x509_privkey key, gnutls_pk_algorithm algo,
	unsigned int bits, unsigned int flags);

int gnutls_x509_privkey_export( gnutls_x509_privkey key,
	gnutls_x509_crt_fmt format, unsigned char* output_data, size_t* output_data_size);
int gnutls_x509_privkey_export_pkcs8( gnutls_x509_privkey key,
	gnutls_x509_crt_fmt format, const char* password, unsigned int flags,
	unsigned char* output_data, size_t* output_data_size);
int gnutls_x509_privkey_export_rsa_raw(gnutls_x509_privkey key,
	gnutls_datum * m, gnutls_datum *e,
	gnutls_datum *d, gnutls_datum *p, gnutls_datum* q, 
	gnutls_datum* u);

/* Certificate request stuff
 */
struct gnutls_x509_crq_int;
typedef struct gnutls_x509_crq_int* gnutls_x509_crq;

int gnutls_x509_crq_init(gnutls_x509_crq * crq);
void gnutls_x509_crq_deinit(gnutls_x509_crq crq);
int gnutls_x509_crq_import(gnutls_x509_crq crq, const gnutls_datum * data,
	gnutls_x509_crt_fmt format);
int gnutls_x509_crq_get_pk_algorithm( gnutls_x509_crq crq, unsigned int* bits);
int gnutls_x509_crq_get_dn(gnutls_x509_crq crq, char *buf,
					 size_t *sizeof_buf);
int gnutls_x509_crq_get_dn_by_oid(gnutls_x509_crq crq, const char* oid, 
	int indx, char *buf, size_t *sizeof_buf);
int gnutls_x509_crq_set_dn_by_oid(gnutls_x509_crq crq, const char* oid, 
	const char *name, unsigned int sizeof_name);
int gnutls_x509_crq_set_version(gnutls_x509_crq crq, unsigned int version);
int gnutls_x509_crq_set_key(gnutls_x509_crq crq, gnutls_x509_privkey key);
int gnutls_x509_crq_sign(gnutls_x509_crq crq, gnutls_x509_privkey key);

int gnutls_x509_crq_set_challenge_password(gnutls_x509_crq crq, const char* pass);
int gnutls_x509_crq_get_challenge_password(gnutls_x509_crq crq, 
	const char* pass, size_t* sizeof_pass);

int gnutls_x509_crq_export( gnutls_x509_crq crq,
	gnutls_x509_crt_fmt format, unsigned char* output_data, size_t* output_data_size);

int gnutls_x509_crt_set_crq(gnutls_x509_crt crt, gnutls_x509_crq crq);


#ifdef __cplusplus
}
#endif
#endif /* GNUTLS_X509_H */

