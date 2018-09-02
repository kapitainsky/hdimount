/*
 *  Created by jief on 28/08/2018.
 *  Copyright © 2018 jf-luce.
 *  This program is free software; you can redistribute it
 *    and/or modify it under the terms of the GNU General Public License version 3.0 as published by the Free Software Foundation.
 */

#include "../../darling-dmg/src/DarlingDMGCrypto.h"
#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>

#include "../../darling-dmg/src/exceptions.h" // TODO



//
//static void printBuf(const uint8_t* buf, size_t count, const char* name, int line_length = 8)
//{
//	if ( name ) printf("static const uint8_t %s[] = {\n", name);
//	for (size_t i = 0; i < count;) {
//		printf("\t");
//		for (int j = 0; j < line_length; j++) {
//			if ( i + j < count-1 ) {
//				if ( j < line_length-1 ) {
//					printf("0x%02x, ", (uint8_t) (buf[i + j]));
//				}else{
//					printf("0x%02x,", (uint8_t) (buf[i + j]));
//				}
//			}
//			else if ( i + j < count ) {
//				printf("0x%02x", (uint8_t) (buf[i + j]));
//			}
//		}
//		i += line_length;
//		printf("\n");
//	}
//	if ( name ) printf("};\n");
//}
//
//





int DarlingDMGCrypto_PKCS5_PBKDF2_HMAC_SHA1(const char *pass, int passlen,
                           const unsigned char *salt, int saltlen, int iter,
                           int keylen, unsigned char *out)
{
	int rv = PKCS5_PBKDF2_HMAC_SHA1(pass, passlen, salt, saltlen, iter, keylen, out);
	return rv;
}


void DarlingDMGCrypto_DES_CBC(const unsigned char *key, const unsigned char *iv, unsigned char *out, int *outl, const unsigned char *in, int inl)
{
//printBuf(key, 24, "key");
//printBuf(iv, 32, "iv");
//printBuf(in, inl, "in");
	EVP_CIPHER_CTX ctx;
	int outl2;

	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit_ex(&ctx, EVP_des_ede3_cbc(), NULL, key, iv);
	if(!EVP_DecryptUpdate(&ctx, out, outl, in, inl)) {
		throw io_error("internal error (1) during key unwrap operation!");
	}
	if(!EVP_DecryptFinal_ex(&ctx, out + *outl, &outl2)) {
		throw io_error("internal error (2) during key unwrap operation! Wrong password ?");
	}
	*outl += outl2;
	EVP_CIPHER_CTX_cleanup(&ctx);
//printBuf(out, *outl, "expected_result");
}

unsigned char * DarlingDMGCrypto_HMAC(const uint8_t *key, int key_len,
                        const unsigned char *d, size_t n,
                        unsigned char *md, unsigned int *md_len)
{
//printBuf(key, key_len, "key");
//printBuf(d, n, "data");
	unsigned char* rv = HMAC(EVP_sha1(), key, key_len, d, n, md, md_len);
//printBuf(md, *md_len, "expected_result");
	return rv;
}

int DarlingDMGCrypto_aes_key_size()
{
	return sizeof(AES_KEY);
}

int DarlingDMGCrypto_set_aes_decrypt_key(const unsigned char *userKey, const int bits, void **key)
{
//printBuf(userKey, bits/8, "userKey");
	*key = malloc(sizeof(AES_KEY));
//memset(*key, 0, sizeof(AES_KEY));
	int rv = AES_set_decrypt_key(userKey, bits, (AES_KEY*)*key); // 0 on success
//printBuf((uint8_t*)*key, sizeof(AES_KEY), "aes_key");
	return rv;
}

/*
 * iv is 16 bytes
 */
void DarlingDMGCrypto_aes_cbc_decrypt(const unsigned char *in, unsigned char *out,
                     size_t length, const void *key,
                     unsigned char *ivec)
{
//printBuf(in, length, "in");
//printBuf(ivec, 16, "iv");
	AES_cbc_encrypt((uint8_t*)in, (uint8_t*)out, length, (AES_KEY*)key, ivec, AES_DECRYPT);
//printBuf(out, length, "expected_result");
}


bool base64Decode(const std::string& input, std::vector<uint8_t>& output)
{
	BIO *b64, *bmem;
	char buffer[input.length()];
	int rd;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf((void*) input.c_str(), input.length());
	bmem = BIO_push(b64, bmem);
	//BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);
	
	rd = BIO_read(bmem, buffer, input.length());
	
	if (rd > 0)
		output.assign(buffer, buffer+rd);

	BIO_free_all(bmem);
	return rd >= 0;
}

