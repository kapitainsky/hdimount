#include <stdio.h>
#include <stddef.h>
#include <string.h> // for memcmp
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#include "../../src/crypto/gladman-aes/aes.h"
#include "../../src/crypto/gladman-aes-modes/xts.h"



static int test_AES_XTS(const uint8_t* key1, int key1_len, const uint8_t* key2, int key2_len,
                        const uint8_t* encrypted_text, int len, uint64_t uno,
                        const unsigned char *expected_result, int expected_result_len)
{
	int ret = 0;

	uint8_t keys[key1_len+key2_len];
	memcpy(keys, key1, key1_len);
	memcpy(keys+key1_len, key2, key2_len);

	uint8_t tweak[0x10];
	for (size_t zz = 0; zz < 0x10; zz++)
	{
		tweak[zz] = uno & 0xFF;
		uno >>= 8;
	}

	unsigned char out[expected_result_len];
	memcpy(out, encrypted_text, expected_result_len);

	xts_ctx ctx;
	xts_key(keys, key1_len+key2_len, &ctx);
//	xts_key(key1, key1_len, &ctx);
	xts_decrypt(out, expected_result_len*8, tweak, &ctx);
	

//printHexBufAsCDecl((uint8_t*)&aes_key, sizeof(AES_KEY), "aes_key");
//printHexBufAsCDecl(in, length, "in");
//printHexBufAsCDecl(ivec, 16, "iv");
//printHexBufAsCDecl(out, length, "expected_result");

	if (memcmp(expected_result, out, expected_result_len))
		goto err;
	ret = 1;
  err:
	return ret;
}




static const uint8_t key1[] = {
	0xd5, 0xc5, 0x58, 0xb2, 0xb2, 0x8c, 0xfd, 0x89,
	0x1a, 0x5a, 0x9b, 0xee, 0x9f, 0x10, 0xdb, 0x40
};
static const uint8_t key2[] = {
	0xb8, 0x0e, 0x1c, 0xa5, 0x8e, 0x62, 0x29, 0x9c,
	0x94, 0x0b, 0x1f, 0x41, 0x14, 0x7c, 0x57, 0xe3
};
static const uint8_t encrypted_text[] = {
	0xd6, 0x6b, 0x70, 0x64, 0x52, 0x8b, 0xdd, 0x59,
	0x6f, 0xe8, 0x73, 0xf7, 0x3a, 0xb7, 0x8a, 0xfb,
	0x79, 0x73, 0x20, 0x11, 0xb4, 0x3f, 0xf4, 0x66,
	0x1c, 0x24, 0x2a, 0x39, 0xce, 0xdb, 0x84, 0x8d,
	0x89, 0x2b, 0x7a, 0x9c, 0xd7, 0x1c, 0x5b, 0x6f,
	0x9e, 0xca, 0x2a, 0xc0, 0x7a, 0x76, 0x39, 0xfe,
	0x89, 0xc5, 0x06, 0xdd, 0xb5, 0x5d, 0x07, 0xa7,
	0x6c, 0x32, 0xc9, 0x4b, 0xc7, 0x8a, 0x50, 0xd0,
	0x3a, 0xa6, 0xd3, 0x33, 0x22, 0x2a, 0x1c, 0x8c,
	0x6d, 0x14, 0x69, 0x4a, 0x95, 0x05, 0xbf, 0x3f,
	0xf4, 0x2e, 0x80, 0xcb, 0xae, 0x6e, 0x9b, 0x32,
	0xa7, 0x02, 0xf8, 0x46, 0xdc, 0x67, 0xf2, 0x65,
	0x15, 0x6a, 0x7f, 0x1d, 0x2a, 0x93, 0xec, 0x43,
	0xd1, 0x0c, 0x80, 0x10, 0xc2, 0x16, 0x1d, 0xee,
	0x51, 0xbd, 0x3c, 0x07, 0xec, 0xe2, 0xa0, 0xa3,
	0x7d, 0x49, 0x3f, 0x20, 0x91, 0x7a, 0x0d, 0x52,
	0x33, 0x82, 0x50, 0x54, 0x2e, 0x1c, 0x74, 0xfc,
	0xf8, 0xc9, 0x02, 0x32, 0x47, 0xb8, 0xc0, 0x9d,
	0x58, 0xbc, 0xb2, 0xb5, 0x09, 0xe2, 0x82, 0xb7,
	0xa7, 0xf6, 0x60, 0x31, 0x2d, 0x4c, 0x7b, 0x69,
	0x7c, 0x8f, 0xe8, 0xba, 0xc5, 0x97, 0xa3, 0xa9,
	0x70, 0x34, 0x07, 0xfb, 0xb2, 0x47, 0x42, 0xe7,
	0x8d, 0x1e, 0x37, 0x68, 0xa4, 0xb4, 0x5c, 0x77,
	0x1b, 0xea, 0x7f, 0x14, 0x6b, 0xb1, 0x20, 0xbf,
	0xae, 0xa1, 0xf2, 0x9b, 0x9a, 0xc7, 0xeb, 0x01,
	0xb0, 0x2b, 0x93, 0x38, 0xe5, 0x02, 0xff, 0xdd,
	0x9d, 0x09, 0x21, 0xe2, 0x09, 0x0c, 0x66, 0xed,
	0xd1, 0x42, 0x62, 0xe5, 0xe5, 0x1c, 0xf8, 0x38,
	0x7d, 0x14, 0xc2, 0x0e, 0xeb, 0xce, 0x81, 0xe7,
	0xa6, 0xbc, 0x14, 0xbd, 0x9a, 0xaa, 0xe3, 0xd4,
	0x33, 0x61, 0xd3, 0x86, 0x9c, 0x96, 0xb3, 0x89,
	0x54, 0x04, 0x52, 0x51, 0xd0, 0xb7, 0x14, 0xe5,
	0x39, 0x96, 0x0c, 0xdb, 0x73, 0xf1, 0xc8, 0x88,
	0x58, 0x29, 0x22, 0x34, 0xbe, 0xcb, 0xe9, 0xea,
	0xd5, 0xbc, 0x83, 0x23, 0xce, 0xf1, 0x08, 0xc5,
	0x74, 0x48, 0x33, 0x88, 0x02, 0x43, 0x08, 0x80,
	0x23, 0x00, 0xb2, 0x6f, 0x74, 0x94, 0x6e, 0x88,
	0xac, 0xf6, 0x60, 0xb6, 0xfa, 0xf0, 0x1c, 0xeb,
	0xa4, 0x87, 0x5b, 0x0c, 0x11, 0xb3, 0xcf, 0xed,
	0xed, 0x67, 0x98, 0xf8, 0x11, 0xad, 0x53, 0x05,
	0xf5, 0xc9, 0x76, 0x9c, 0xd5, 0xf2, 0x93, 0x2d,
	0x29, 0x8d, 0xc1, 0x31, 0xf1, 0x14, 0xc0, 0xec,
	0xe5, 0x21, 0xc1, 0x9c, 0x0a, 0x90, 0x6d, 0x14,
	0x9f, 0x32, 0x1b, 0x17, 0x2a, 0x5d, 0x68, 0x8e,
	0x5e, 0x74, 0xcb, 0x89, 0x63, 0x10, 0x02, 0x93,
	0xe1, 0x87, 0x1b, 0xe2, 0x04, 0x9a, 0xce, 0xa2,
	0xf3, 0xc1, 0x1d, 0xd1, 0xd2, 0xa1, 0x87, 0xa2,
	0x5f, 0xe5, 0x1c, 0x5e, 0x8a, 0xbb, 0x21, 0xaa,
	0xc9, 0x9a, 0xae, 0x9e, 0x1d, 0x8c, 0x8d, 0x66,
	0x50, 0x29, 0x68, 0x5b, 0x69, 0x85, 0x9b, 0x86,
	0xc1, 0x23, 0x3c, 0xcb, 0xa5, 0x08, 0xa3, 0x28,
	0xc0, 0x2d, 0x18, 0x73, 0xb6, 0x24, 0x0c, 0xa0,
	0x34, 0x5a, 0x8d, 0xfe, 0x08, 0x27, 0x29, 0xb0,
	0xbf, 0xf7, 0x54, 0xd0, 0x7d, 0xc6, 0xc3, 0xc3,
	0xb3, 0x38, 0x0e, 0x2c, 0xa6, 0xb4, 0x7c, 0xb8,
	0x06, 0x0c, 0x01, 0x3d, 0xd9, 0x43, 0x44, 0xc2,
	0x29, 0xb3, 0x18, 0x73, 0x9f, 0x80, 0xf1, 0x94,
	0x10, 0xfb, 0xa4, 0xd0, 0x1a, 0xe5, 0xda, 0x4d,
	0xfc, 0x90, 0x64, 0x2c, 0x8e, 0x3c, 0x5a, 0xa3,
	0x65, 0x59, 0x1b, 0xd6, 0xf3, 0x70, 0x1e, 0xa7,
	0xbc, 0xb9, 0xf4, 0xf6, 0xc3, 0x48, 0xf2, 0x81,
	0x07, 0x91, 0x22, 0x10, 0x0a, 0xee, 0x6b, 0x5d,
	0x10, 0x89, 0xad, 0x85, 0x3e, 0x12, 0x09, 0x0b,
	0xc7, 0xb8, 0x77, 0xd5, 0xf3, 0x4e, 0xcd, 0x7c
};
static uint64_t uno = 143479;
static const uint8_t expected_result[] = {
	0x4f, 0x15, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x6c, 0xc2, 0xa5, 0x4a,
	0x48, 0x5a, 0x4f, 0x15, 0x08, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x21,
	0x60, 0x4a, 0x48, 0x5a, 0x4f, 0x15, 0x00, 0xe1,
	0xa5, 0x4a, 0x48, 0x5a, 0x4f, 0x15, 0x00, 0xe1,
	0xa5, 0x4a, 0x48, 0x5a, 0x4f, 0x15, 0xb8, 0x21,
	0x60, 0x4a, 0x48, 0x5a, 0x4f, 0x15, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x00,
	0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0xc0, 0x41,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x04, 0x02,
	0x10, 0x00, 0x2e, 0x53, 0x70, 0x6f, 0x74, 0x6c,
	0x69, 0x67, 0x68, 0x74, 0x2d, 0x56, 0x31, 0x30,
	0x30, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x41, 0x00, 0x47, 0x11, 0x01, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x72, 0x60, 0x35, 0xd5, 0x46, 0x5a,
	0x4f, 0x15, 0x67, 0x45, 0x44, 0x8e, 0x2d, 0x9d,
	0x4f, 0x15, 0x67, 0x45, 0x44, 0x8e, 0x2d, 0x9d,
	0x4f, 0x15, 0x72, 0x60, 0x35, 0xd5, 0x46, 0x5a,
	0x4f, 0x15, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa4, 0x41, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x10, 0x00, 0x04, 0x02, 0x0c, 0x00, 0x70, 0x72,
	0x69, 0x76, 0x61, 0x74, 0x65, 0x2d, 0x64, 0x69,
	0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb1, 0x62,
	0x71, 0x86, 0x8a, 0x5c, 0x4f, 0x15, 0x04, 0x00,
	0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xbd, 0x35, 0xd5, 0xaf, 0x88, 0x5c, 0x4f, 0x15,
	0x08, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x4b, 0xe5, 0x04, 0x4b, 0x48, 0x5a,
	0x4f, 0x15, 0x04, 0x00, 0x4e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xa4, 0xdc, 0x8c, 0xfd,
	0x51, 0x5a, 0x4f, 0x15, 0x08, 0x00, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x21,
	0x60, 0x4a, 0x48, 0x5a, 0x4f, 0x15, 0x04, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xd9, 0xfd, 0x34, 0xd5, 0x46, 0x5a, 0x4f, 0x15,
	0xeb, 0x22, 0xd0, 0xe1, 0x8a, 0x5c, 0x4f, 0x15,
	0xeb, 0x22, 0xd0, 0xe1, 0x8a, 0x5c, 0x4f, 0x15,
	0xc7, 0x52, 0x5c, 0xe4, 0x8a, 0x5c, 0x4f, 0x15,
	0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xfd, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00,
	0x04, 0x02, 0x05, 0x00, 0x72, 0x6f, 0x6f, 0x74,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xd9, 0xfd, 0x34, 0xd5,
	0x46, 0x5a, 0x4f, 0x15, 0x04, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x60,
	0x35, 0xd5, 0x46, 0x5a, 0x4f, 0x15, 0x04, 0x00
};


int test_AES_XTS_crypto()
{


	bool all_tests_ok = true;
	int ret;
	ret = test_AES_XTS(key1, sizeof(key1), key2, sizeof(key2), encrypted_text, sizeof(encrypted_text), uno, expected_result, sizeof(expected_result));
	fprintf(stderr, "test_AES_XTS_crypto %d\n", ret);
	if ( ret == 0 ) all_tests_ok = false;

	return 1;
}

