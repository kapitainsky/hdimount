/*
 *  Created by jief on 28/08/2018.
 *  Copyright © 2018 jf-luce.
 *  This program is free software; you can redistribute it
 *    and/or modify it under the terms of the GNU General Public License version 3.0 as published by the Free Software Foundation.
 */

#include <stdio.h>
#include "../../apfs-fuse/ApfsLib/APFSLibCrypto.h"

//#include "aes-rijndael/rijndael-aes.h"
//#include "aes-rijndael/aesxts.h"
#include "gladman-aes/aes.h"
#include "gladman-sha/sha1.h"
#include "gladman-sha/sha2.h"
#include "gladman-sha/hmac.h"
#include "gladman-aes-modes/xts.h"

#include "Rfc3394.h"
#include "PBKDF2_HMAC_SHA256.h"
#include "crc32c.h"


static void printBuf(const uint8_t* buf, size_t count, const char* name, int line_length = 8)
{
	if ( name ) printf("static const uint8_t %s[] = {\n", name);
	for (size_t i = 0; i < count;) {
		printf("\t");
		for (int j = 0; j < line_length; j++) {
			if ( i + j < count-1 ) {
				if ( j < line_length-1 ) {
					printf("0x%02x, ", (uint8_t) (buf[i + j]));
				}else{
					printf("0x%02x,", (uint8_t) (buf[i + j]));
				}
			}
			else if ( i + j < count ) {
				printf("0x%02x", (uint8_t) (buf[i + j]));
			}
		}
		i += line_length;
		printf("\n");
	}
	if ( name ) printf("};\n");
}

/*
 * aes : 128 or 256 = key size in bits.
 */
bool APFSLibCrypto_Rfc3394_KeyUnwrap(uint8_t *plain, const uint8_t *crypto, size_t size, const uint8_t *key, int aes_mode, uint64_t *iv)
{
printBuf(key, aes_mode/8, "kek");
printBuf(crypto, size+8, "wrapped_key");
printBuf((const uint8_t*)iv, 16, "iv");
	bool rv = AES_unwrap_key_2(plain, crypto, size, key, aes_mode, NULL);
printBuf(plain, size, "APFSLibCrypto_Rfc3394_KeyUnwrap");
	return rv;
}

void APFSLibCrypto_PBKDF2_HMAC_SHA256(const uint8_t* pw, size_t pw_len, const uint8_t* salt, size_t salt_len, int iterations, uint8_t* derived_key, size_t dk_len)
{
	Password_Based_Key_Derivation_Function_2_SHA256(pw, pw_len, salt, salt_len, iterations, derived_key, dk_len);
//printBuf(derived_key, dk_len, "APFSLibCrypto_PBKDF2_HMAC_SHA256");
}

void APFSLibCrypto_SHA256(const uint8_t* vek, int vek_len, const uint8_t* uuid, int uuid_len, uint8_t* sha_result)
{
	sha256_ctx sha256Ctx;
	sha256_begin(&sha256Ctx);
	sha256_hash(vek, vek_len, &sha256Ctx);
	sha256_hash(uuid, uuid_len, &sha256Ctx);
	sha_end1(sha_result, &sha256Ctx, 0x20); // 0x20 = 256 bits
//printBuf(sha_result, 0x20, "APFSLibCrypto_SHA256");
}

void APFSLibCrypto_HMAC_SHA256(const uint8_t *key, size_t key_len, const uint8_t *data, size_t data_len, uint8_t *mac)
{
	hmac_sha(HMAC_SHA256, key, key_len, data, data_len, mac, 0x20); // 0x20 = 256 bits
//printBuf(mac, 0x20, "APFSLibCrypto_HMAC_SHA256");
}

void APFSLibCrypto_aes_xtx_setkey(const uint8_t* key1, int key1_len, const uint8_t* key2, int key2_len, xts_ctx* ctx)
{
//	xts_start(0, NULL, key1, key1_len, key2, key2_len, 0, 0, ctx);
	uint8_t keys[key1_len+key2_len];
	memcpy(keys, key1, key1_len);
	memcpy(keys+key1_len, key2, key2_len);
	xts_key(keys, key1_len+key2_len, ctx);
}

void APFSLibCrypto_aes_xtx_decrypt_internal(const uint8_t* encrypted_text, int len, uint8_t* plain_text, uint64_t uno, xts_ctx* ctx)
{
	uint8_t tweak[0x10];
	for (size_t zz = 0; zz < 0x10; zz++)
	{
		tweak[zz] = uno & 0xFF;
		uno >>= 8;
	}
//	xts_decrypt(encrypted_text, len, plain_text, tweak, ctx);
	memcpy(plain_text, encrypted_text, len); // TODO can we avoid buffer copy ?
	xts_decrypt(plain_text, len*8, tweak, ctx);
//printBuf(plain_text, len, "APFSLibCrypto_aes_xtx_decrypt_internal");
}

static xts_ctx g_ctx;

void APFSLibCrypto_aes_xtx_setkey(const uint8_t* key1, int key1_len, const uint8_t* key2, int key2_len)
{
	APFSLibCrypto_aes_xtx_setkey(key1, key1_len, key2, key2_len, &g_ctx);
}

void APFSLibCrypto_aes_xtx_setkey(const uint8_t* key1, int key1_len, const uint8_t* key2, int key2_len, void **ctx)
{
	*ctx = malloc(sizeof(xts_ctx));
	APFSLibCrypto_aes_xtx_setkey(key1, key1_len, key2, key2_len, (xts_ctx*)*ctx);
}

void APFSLibCrypto_aes_xtx_decrypt(const uint8_t* encrypted_text, int len, uint8_t* plain_text, uint64_t uno)
{
	APFSLibCrypto_aes_xtx_decrypt_internal(encrypted_text, len, plain_text, uno, &g_ctx);
}

void APFSLibCrypto_aes_xtx_decrypt(const uint8_t* encrypted_text, int len, uint8_t* plain_text, uint64_t uno, void* ctx)
{
	APFSLibCrypto_aes_xtx_decrypt_internal(encrypted_text, len, plain_text, uno, (xts_ctx*)ctx);
}

uint32_t APFSLibCrypto_calculate_crc32c(uint32_t crc32c, const unsigned char *buffer, unsigned int length)
{
	return calculate_crc32c(crc32c, buffer, length);
}

