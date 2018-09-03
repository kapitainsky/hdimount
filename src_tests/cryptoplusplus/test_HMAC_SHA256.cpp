#include <stddef.h>
#include <string.h> // for memcmp
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/modes.h>

#include "../../src/crypto++/Crypto.h"

int test_HMAC_SHA256(const uint8_t *key, int key_len, const unsigned char *d, size_t n,
							      const unsigned char *expected_result, int expected_result_len)
{
	int ret = 0;
	unsigned char out[expected_result_len];

	HMAC_SHA256(key, key_len, d, n, out);

	if (memcmp(expected_result, out, expected_result_len))
		goto err;
	ret = 1;
  err:
	return ret;
}

static const uint8_t key[] = {
	0xc2, 0x76, 0x46, 0x94, 0x0b, 0x94, 0xb7, 0xf3,
	0x54, 0x24, 0xa1, 0x19, 0x13, 0xd9, 0x4f, 0x96,
	0xc7, 0xa6, 0xd1, 0x58, 0x3b, 0xd7, 0x14, 0x23,
	0x9c, 0xb8, 0xbf, 0x26, 0x29, 0x7e, 0xf9, 0xb3
};
static const uint8_t data[] = {
	0xa3, 0x60, 0x80, 0x01, 0x00, 0x81, 0x10, 0x0e,
	0x91, 0xfe, 0xd4, 0x84, 0xd8, 0x4d, 0x2e, 0x8f,
	0x9d, 0x67, 0xeb, 0x31, 0xb6, 0xf2, 0xa6, 0x82,
	0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x11,
	0xcb, 0x83, 0x28, 0xaa, 0xa8, 0x39, 0xcb, 0xe7,
	0x17, 0x3b, 0x59, 0x07, 0xe3, 0xc7, 0x96, 0xa1,
	0x1b, 0xfa, 0x1a, 0xd7, 0x51, 0xc1, 0x9e, 0x54,
	0x30, 0xbd, 0x29, 0xb1, 0x23, 0x9a, 0xf6, 0xa2,
	0xff, 0xf3, 0x60, 0x17, 0x46, 0xbe, 0x9f, 0x4d,
	0x89, 0xbd, 0x9a, 0x84, 0x03, 0x01, 0x89, 0x8c,
	0x85, 0x10, 0xe1, 0x37, 0xaf, 0xac, 0xe0, 0x4b,
	0x99, 0x88, 0x2d, 0xc9, 0x60, 0xae, 0x56, 0x32,
	0x45, 0xe7
};
static const uint8_t expected_result[] = {
	0x03, 0x03, 0xa1, 0xf3, 0x12, 0x9f, 0xbe, 0x7d,
	0xb9, 0x12, 0xef, 0x09, 0x7a, 0x44, 0xea, 0x4b,
	0xd0, 0x29, 0xe5, 0x45, 0x25, 0x21, 0x0f, 0x76,
	0x82, 0x17, 0x74, 0x33, 0xc6, 0x1a, 0x65, 0x13
};

int test_HMAC_SHA256_plusplus()
{


	bool all_tests_ok = true;
	int ret;

	ret = test_HMAC_SHA256(key, sizeof(key), data, sizeof(data), expected_result, sizeof(expected_result));
	fprintf(stderr, "test_HMAC_SHA256_test_cryptoplusplus %d\n", ret);
	if ( ret == 0 ) all_tests_ok = false;

	return 1;
}

