#include <stdio.h>
#include <stddef.h>
#include <string.h> // for memcmp
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>


#ifndef _WIN32
#define USE_TEST_CRYPTO_OPENSSL
#endif
#define USE_TEST_CRYPTO_C
#define USE_TEST_CRYPTO_CPLUSPLUS





#ifdef USE_TEST_CRYPTO_OPENSSL
#define DECLARE_TEST_CRYPTO_OPENSSL(name, ... ) \
    int test_##name##_crypto_openssl(__VA_ARGS__);
#else
#define DECLARE_TEST_CRYPTO_OPENSSL(name, ... )
#endif

#ifdef USE_TEST_CRYPTO_C
#define DECLARE_TEST_CRYPTO_C(name, ... ) \
    int test_##name##_crypto_c(__VA_ARGS__);
#else
#define DECLARE_TEST_CRYPTO_C(name, ... )
#endif

#ifdef USE_TEST_CRYPTO_CPLUSPLUS
#define DECLARE_TEST_CRYPTO_CPLUSPLUS(name, ... ) \
    int test_##name##_crypto_cplusplus(__VA_ARGS__);
#else
#define DECLARE_TEST_CRYPTO_CPLUSPLUS(name, ... )
#endif

#define DECLARE_TEST(name, ... ) \
    DECLARE_TEST_CRYPTO_CPLUSPLUS(name, __VA_ARGS__); \
    DECLARE_TEST_CRYPTO_OPENSSL(name, __VA_ARGS__); \
    DECLARE_TEST_CRYPTO_C(name, __VA_ARGS__); \


DECLARE_TEST(AES_wrap_unwrap, const unsigned char *kek, int keybits,
             const unsigned char *wrapped_key,
             int wrapped_key_len,
             const unsigned char *iv,
             const unsigned char *expected_result, int expected_result_len)


DECLARE_TEST(DES_CBC, const unsigned char *key, const unsigned char *iv, const unsigned char *in, int inl,
                                  const unsigned char *expected_result, int expected_result_len);


DECLARE_TEST(PBKDF2_HMAC_SHA1, const char *pass, int passlen,
                                  const unsigned char *salt, int saltlen, int iter,
                                  const unsigned char *expected_result, int expected_result_len);

DECLARE_TEST(PBKDF2_HMAC_SHA256, const uint8_t* pw, size_t pw_len, const uint8_t* salt, size_t salt_len, int iterations,
                                    const unsigned char *expected_result, int expected_result_len);


DECLARE_TEST(HMAC_SHA1, const uint8_t *key, int key_len, const unsigned char *d, size_t n,
                                  const unsigned char *expected_result, int expected_result_len);



DECLARE_TEST(AES_CBC, const unsigned char *userKey, const int bits,
                         const unsigned char *in, size_t length,
                         const unsigned char *ivec,
                         const unsigned char *expected_result, int expected_result_len);


DECLARE_TEST(AES_XTS, const uint8_t* key1, int key1_len, const uint8_t* key2, int key2_len,
                        const uint8_t* encrypted_text, int len, uint64_t uno,
                        const unsigned char *expected_result, int expected_result_len);



DECLARE_TEST(HMAC_SHA256, const uint8_t *key, int key_len, const unsigned char *d, size_t n,
                                  const unsigned char *expected_result, int expected_result_len);


#ifdef USE_TEST_CRYPTO_C
#define TEST_CRYPTO_C(name, ...) \
    ret = test_##name##_crypto_c(__VA_ARGS__); \
    fprintf(stderr, #name "_crypto_c %d\n", ret); \
    if ( ret == 0 ) all_tests_ok = false; \

#else
#define TEST_CRYPTO_C(name, ...)
#endif

#ifdef USE_TEST_CRYPTO_CPLUSPLUS
#define TEST_CRYPTO_CPLUSPLUS(name, ...) \
    ret = test_##name##_crypto_cplusplus(__VA_ARGS__); \
    fprintf(stderr, #name "_crypto_cplusplus %d\n", ret); \
    if ( ret == 0 ) all_tests_ok = false; \

#else
#define TEST_CRYPTO_CPLUSPLUS(name, ...)
#endif

#ifdef USE_TEST_CRYPTO_OPENSSL
#define TEST_CRYPTO_OPENSSL(name, ...) \
    ret = test_##name##_crypto_openssl(__VA_ARGS__); \
    fprintf(stderr, #name "_crypto_openssl %d\n", ret); \
    if ( ret == 0 ) all_tests_ok = false; \

#else
#define TEST_CRYPTO_OPENSSL(name, ...)
#endif

#define TEST_all_crypto(name, ...) \
     TEST_CRYPTO_C(name, __VA_ARGS__) \
     TEST_CRYPTO_CPLUSPLUS(name, __VA_ARGS__) \
     TEST_CRYPTO_OPENSSL(name, __VA_ARGS__) \

static const uint8_t AES_wrap_unwrap_kek[] = {
    0x52, 0x7b, 0x9a, 0xbd, 0x41, 0x0a, 0x69, 0x93,
    0x11, 0x0e, 0x6c, 0x5f, 0xdf, 0x6f, 0x25, 0xff,
    0xa5, 0xcb, 0xb1, 0xdb, 0x98, 0xbe, 0x18, 0xe3,
    0x3d, 0x45, 0xa5, 0xe3, 0x9e, 0xe7, 0x0d, 0x4c
};
static const uint8_t AES_wrap_unwrap_wrapped_key[] = {
    0xaa, 0xa8, 0x39, 0xcb, 0xe7, 0x17, 0x3b, 0x59,
    0x07, 0xe3, 0xc7, 0x96, 0xa1, 0x1b, 0xfa, 0x1a,
    0xd7, 0x51, 0xc1, 0x9e, 0x54, 0x30, 0xbd, 0x29,
    0xb1, 0x23, 0x9a, 0xf6, 0xa2, 0xff, 0xf3, 0x60,
    0x17, 0x46, 0xbe, 0x9f, 0x4d, 0x89, 0xbd, 0x9a
};
static const uint8_t AES_wrap_unwrap_unwrapped_key[] = {
    0xf0, 0x60, 0x5c, 0xc3, 0xf1, 0xed, 0x03, 0x05,
    0xb7, 0x03, 0x93, 0x75, 0x2e, 0x90, 0xd6, 0x92,
    0xcb, 0x4e, 0x04, 0xec, 0x96, 0x3c, 0x4b, 0x75,
    0xed, 0xef, 0xc2, 0xbd, 0x62, 0x0c, 0x6b, 0xf8
};
static const uint8_t AES_wrap_unwrap_unwrapped_iv[] = {
    0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6,
};


static const uint8_t DES_CBC_key[] = {
    0xb9, 0x5e, 0xb6, 0x81, 0x60, 0x59, 0x60, 0xa5,
    0x83, 0x88, 0x41, 0x9a, 0x54, 0x45, 0xc8, 0x61,
    0x18, 0x4c, 0xdd, 0x3a, 0xf5, 0x69, 0x51, 0xbd
};
static const uint8_t DES_CBC_iv[] = {
    0xa8, 0x46, 0x7a, 0x0c, 0x56, 0xfb, 0x6a, 0x4f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const uint8_t DES_CBC_in[] = {
    0x0f, 0xae, 0x28, 0x87, 0x25, 0x9b, 0xae, 0x4b,
    0xc3, 0x78, 0x9c, 0xa8, 0x90, 0xd0, 0x69, 0x99,
    0xb4, 0x2e, 0x27, 0x63, 0x6e, 0xe6, 0xf4, 0xef,
    0xa7, 0x3c, 0x60, 0x73, 0xb1, 0x67, 0xf3, 0x55,
    0xe2, 0xb5, 0x24, 0x57, 0xc6, 0xb4, 0x69, 0x9f,
    0x61, 0x17, 0x96, 0x54, 0x28, 0xe1, 0x6c, 0xce
};

static const uint8_t DES_CBC_expected_result[] = {
    0x98, 0x35, 0x11, 0x34, 0xd5, 0x78, 0x26, 0xb0,
    0x87, 0x82, 0x97, 0x4d, 0x9c, 0x9b, 0x32, 0x9a,
    0x98, 0x35, 0x11, 0x34, 0xd5, 0x78, 0x26, 0xb0,
    0x87, 0x82, 0x97, 0x4d, 0x9c, 0x9b, 0x32, 0x9a,
    0x00, 0xbc, 0xb3, 0x07, 0x43, 0x4b, 0x49, 0x45,
    0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07
};


static const char PBKDF2_HMAC_SHA1_pass[] = "foo";
static const unsigned char PBKDF2_HMAC_SHA1_salt[] = {
    0x76, 0xc7, 0xb1, 0x0d, 0xfb, 0xce, 0x6f, 0x91,
    0xb4, 0x97, 0x55, 0x82, 0xef, 0x50, 0x0a, 0xc8,
    0x7c, 0xb5, 0xba, 0x76
};

static const uint8_t PBKDF2_HMAC_SHA1_expected_result[] = {
    0xb9, 0x5e, 0xb6, 0x81, 0x60, 0x59, 0x60, 0xa5,
    0x83, 0x88, 0x41, 0x9a, 0x54, 0x45, 0xc8, 0x61,
    0x18, 0x4c, 0xdd, 0x3a, 0xf5, 0x69, 0x51, 0xbd
};


static const uint8_t HMAC_SHA1_key[] = {
    0x98, 0x35, 0x11, 0x34, 0xd5, 0x78, 0x26, 0xb0,
    0x87, 0x82, 0x97, 0x4d, 0x9c, 0x9b, 0x32, 0x9a,
    0x00, 0xbc, 0xb3, 0x07
};
static const uint8_t HMAC_SHA1_data[] = {
    0x00, 0x00, 0x4c, 0x72
};
static const uint8_t HMAC_SHA1_expected_result[] = {
    0x8d, 0x9a, 0xfc, 0x86, 0xcc, 0xc0, 0x3d, 0xdd,
    0x51, 0x05, 0xd2, 0x3a, 0x62, 0x33, 0xa8, 0x18,
    0x76, 0xa8, 0x02, 0xdc
};



static const char* PBKDF2_HMAC_SHA256_pass = "foo";
static const uint8_t PBKDF2_HMAC_SHA256_salt[] = {
    0xe1, 0x37, 0xaf, 0xac, 0xe0, 0x4b, 0x99, 0x88,
    0x2d, 0xc9, 0x60, 0xae, 0x56, 0x32, 0x45, 0xe7
};
static const int PBKDF2_HMAC_SHA256_iterations = 100748;
static const uint8_t PBKDF2_HMAC_SHA256_expected_result[] = {
    0x52, 0x7b, 0x9a, 0xbd, 0x41, 0x0a, 0x69, 0x93,
    0x11, 0x0e, 0x6c, 0x5f, 0xdf, 0x6f, 0x25, 0xff,
    0xa5, 0xcb, 0xb1, 0xdb, 0x98, 0xbe, 0x18, 0xe3,
    0x3d, 0x45, 0xa5, 0xe3, 0x9e, 0xe7, 0x0d, 0x4c
};


static const uint8_t AES_XTS_key1[] = {
    0xd5, 0xc5, 0x58, 0xb2, 0xb2, 0x8c, 0xfd, 0x89,
    0x1a, 0x5a, 0x9b, 0xee, 0x9f, 0x10, 0xdb, 0x40
};
static const uint8_t AES_XTS_key2[] = {
    0xb8, 0x0e, 0x1c, 0xa5, 0x8e, 0x62, 0x29, 0x9c,
    0x94, 0x0b, 0x1f, 0x41, 0x14, 0x7c, 0x57, 0xe3
};
static const uint8_t AES_XTS_encrypted_text[] = {
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
static const uint64_t AES_XTS_uno = 143479;
static const uint8_t AES_XTS_expected_result[] = {
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




static const uint8_t AES_CBC_userKey[] = {
    0x98, 0x35, 0x11, 0x34, 0xd5, 0x78, 0x26, 0xb0,
    0x87, 0x82, 0x97, 0x4d, 0x9c, 0x9b, 0x32, 0x9a
};
static const uint8_t AES_CBC_in[] = {
    0x3c, 0xfe, 0x13, 0x0b, 0xbf, 0x53, 0xf2, 0x59,
    0xb8, 0x4d, 0x69, 0x2c, 0x02, 0x04, 0xfb, 0x14,
    0x5b, 0x5e, 0x3d, 0x11, 0xde, 0x95, 0x1a, 0x18,
    0x1d, 0x4d, 0x6b, 0xf0, 0xad, 0x0b, 0xd2, 0x3e,
    0x09, 0x11, 0x62, 0x8e, 0x2b, 0xab, 0xf2, 0xda,
    0x68, 0x28, 0xf4, 0x1d, 0x85, 0x27, 0x1d, 0x04,
    0xa0, 0xa9, 0x51, 0x3e, 0xb5, 0xf3, 0x54, 0xcb,
    0x3f, 0xa6, 0xf8, 0x8c, 0xd2, 0xbe, 0x85, 0xcc,
    0xd8, 0x48, 0xe7, 0x20, 0xd9, 0xc6, 0x81, 0xb4,
    0x7f, 0xc1, 0x58, 0x52, 0xaa, 0x8b, 0x5b, 0xf3,
    0xdf, 0xbb, 0xf6, 0xb7, 0xb3, 0x0a, 0xca, 0x43,
    0x2b, 0x22, 0x10, 0xf8, 0xe8, 0x10, 0x65, 0x40,
    0x31, 0x85, 0xb1, 0x6a, 0xa3, 0x2b, 0xc8, 0x82,
    0x07, 0xf8, 0x5a, 0x7e, 0xb4, 0xd7, 0x51, 0x2b,
    0xef, 0xfc, 0x2e, 0x31, 0x72, 0x4e, 0xef, 0x5a,
    0x02, 0x74, 0x37, 0x1c, 0xad, 0x6a, 0x7d, 0x6f,
    0x9e, 0x04, 0xa7, 0x59, 0xad, 0xe1, 0xd5, 0x3d,
    0x8b, 0xdc, 0xfe, 0x16, 0xe8, 0x32, 0x34, 0x91,
    0x21, 0xb2, 0x8b, 0xdb, 0x51, 0x6a, 0xc4, 0x7d,
    0xcc, 0x1f, 0xc6, 0x27, 0xd9, 0xfd, 0x56, 0xad,
    0x22, 0xb4, 0x8e, 0x9e, 0x5a, 0x4f, 0xb5, 0xfe,
    0x85, 0x82, 0x01, 0x7b, 0x68, 0x3a, 0xb7, 0xd8,
    0x6f, 0x43, 0xb6, 0x60, 0xde, 0x3d, 0xe5, 0x90,
    0x06, 0x2e, 0x4c, 0x33, 0x56, 0xa2, 0x7b, 0xbf,
    0xd8, 0x2b, 0x90, 0x0b, 0xc4, 0x0e, 0xa3, 0xb5,
    0x80, 0xa6, 0xcd, 0xac, 0x2e, 0x01, 0x91, 0xc1,
    0xbc, 0x70, 0x85, 0x06, 0x7a, 0x0f, 0x4b, 0xac,
    0x5f, 0x57, 0xe9, 0x0b, 0x34, 0x70, 0x8f, 0xf6,
    0x55, 0xac, 0x34, 0xe7, 0x00, 0x64, 0xb6, 0x2b,
    0x54, 0x32, 0xbb, 0x79, 0x64, 0x99, 0x38, 0x87,
    0x11, 0x0f, 0x52, 0xc4, 0xe1, 0xbd, 0xcf, 0x9c,
    0x8f, 0x9a, 0x55, 0x64, 0x2f, 0x32, 0x88, 0xc4,
    0x94, 0xfd, 0x78, 0x71, 0x2c, 0x2e, 0xa4, 0x66,
    0x18, 0x39, 0xcf, 0x83, 0xe4, 0x3b, 0xe9, 0xe4,
    0x9d, 0x2b, 0x0c, 0x8b, 0x93, 0xcf, 0x7b, 0xf2,
    0x3c, 0x83, 0xda, 0xce, 0xeb, 0x6c, 0x66, 0xaa,
    0x2f, 0x9d, 0xc5, 0xf1, 0x1b, 0x10, 0xe9, 0xfa,
    0x4b, 0x2f, 0x47, 0x09, 0x7b, 0x92, 0x9d, 0xf4,
    0x95, 0x29, 0x92, 0x98, 0x77, 0x8f, 0x0c, 0x60,
    0x88, 0xc4, 0x49, 0x22, 0xb3, 0x0d, 0xe1, 0x2b,
    0x7c, 0x24, 0xaf, 0xcc, 0x4c, 0x24, 0x6a, 0xa8,
    0x7a, 0xcf, 0x04, 0xa6, 0x9e, 0x05, 0x88, 0xbc,
    0x1d, 0xce, 0xa5, 0x5f, 0xa8, 0xd5, 0x41, 0x25,
    0x94, 0x67, 0x7e, 0x30, 0x95, 0xeb, 0xa3, 0x1e,
    0x44, 0x88, 0x18, 0x5b, 0xa7, 0x09, 0x6c, 0x2d,
    0x1a, 0xa9, 0x0c, 0xbc, 0x7a, 0x2f, 0x4e, 0xf0,
    0xba, 0x45, 0x85, 0x35, 0xf8, 0x57, 0x72, 0xab,
    0xa6, 0x83, 0x9b, 0xaa, 0xe2, 0xb0, 0x62, 0xfe,
    0x5e, 0x99, 0xb7, 0x8f, 0x2e, 0x35, 0x27, 0xf9,
    0x1d, 0xad, 0xf7, 0x3d, 0x2b, 0x91, 0xa7, 0x90,
    0x31, 0xb1, 0xf0, 0x02, 0xa4, 0xeb, 0x02, 0x4a,
    0x3e, 0x14, 0xc9, 0x8d, 0xe5, 0x94, 0xbe, 0x4b,
    0xb9, 0x1d, 0x7f, 0xc3, 0x39, 0x60, 0x54, 0xca,
    0x94, 0x7b, 0x6d, 0x31, 0x10, 0x2b, 0x36, 0xbd,
    0xb2, 0xd0, 0xf8, 0x23, 0x4f, 0x9e, 0xf4, 0xfc,
    0x07, 0x64, 0x59, 0x96, 0x9c, 0x5a, 0x61, 0xbc,
    0xea, 0x13, 0x5d, 0xd5, 0x68, 0x2a, 0x69, 0x23,
    0xf6, 0xec, 0xb6, 0x33, 0xab, 0x39, 0x89, 0xbe,
    0x9d, 0xe3, 0x82, 0x14, 0xb1, 0xef, 0x98, 0x68,
    0x5f, 0xd4, 0xf4, 0x68, 0x2a, 0xf7, 0x42, 0x7d,
    0x89, 0x8e, 0x15, 0xf6, 0x99, 0xf5, 0xa1, 0x7f,
    0xd7, 0xdd, 0xd5, 0x2d, 0x22, 0xf8, 0xa9, 0x8e,
    0x1d, 0xb6, 0xd3, 0x9c, 0x17, 0x85, 0x4f, 0x55,
    0x27, 0xad, 0x97, 0xb7, 0x5f, 0x44, 0x62, 0x12
};
static const uint8_t AES_CBC_iv[] = {
    0x61, 0x36, 0x05, 0x30, 0x44, 0xfa, 0x9b, 0x8f,
    0xe4, 0xfc, 0xf7, 0x16, 0x50, 0x88, 0xa9, 0x5a
};
static const uint8_t AES_CBC_expected_result[] = {
    0x00, 0x08, 0x00, 0x78, 0x00, 0x61, 0x00, 0x74,
    0x00, 0x74, 0x00, 0x72, 0x00, 0x31, 0x00, 0x38,
    0x00, 0x35, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x31, 0x38, 0x35, 0xde, 0x00, 0x1c,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x78, 0x00, 0x61,
    0x00, 0x74, 0x00, 0x74, 0x00, 0x72, 0x00, 0x31,
    0x00, 0x38, 0x00, 0x36, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x31, 0x38, 0x36, 0xde,
    0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x78,
    0x00, 0x61, 0x00, 0x74, 0x00, 0x74, 0x00, 0x72,
    0x00, 0x31, 0x00, 0x38, 0x00, 0x37, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x31, 0x38,
    0x37, 0xde, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x78, 0x00, 0x61, 0x00, 0x74, 0x00, 0x74,
    0x00, 0x72, 0x00, 0x31, 0x00, 0x38, 0x00, 0x38,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x31, 0x38, 0x38, 0xde, 0x00, 0x1c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x78, 0x00, 0x61, 0x00, 0x74,
    0x00, 0x74, 0x00, 0x72, 0x00, 0x31, 0x00, 0x38,
    0x00, 0x39, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x31, 0x38, 0x39, 0xde, 0x00, 0x1a,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0x00, 0x78, 0x00, 0x61,
    0x00, 0x74, 0x00, 0x74, 0x00, 0x72, 0x00, 0x31,
    0x00, 0x39, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x02, 0x31, 0x39, 0x00, 0x1c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x78, 0x00, 0x61, 0x00, 0x74,
    0x00, 0x74, 0x00, 0x72, 0x00, 0x31, 0x00, 0x39,
    0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x31, 0x39, 0x30, 0xde, 0x00, 0x1c,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x78, 0x00, 0x61,
    0x00, 0x74, 0x00, 0x74, 0x00, 0x72, 0x00, 0x31,
    0x00, 0x39, 0x00, 0x31, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x31, 0x39, 0x31, 0xde,
    0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x78,
    0x00, 0x61, 0x00, 0x74, 0x00, 0x74, 0x00, 0x72,
    0x00, 0x31, 0x00, 0x39, 0x00, 0x32, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x31, 0x39,
    0x32, 0xde, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x78, 0x00, 0x61, 0x00, 0x74, 0x00, 0x74,
    0x00, 0x72, 0x00, 0x31, 0x00, 0x39, 0x00, 0x33,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x31, 0x39, 0x33, 0xde, 0x00, 0x1c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x78, 0x00, 0x61, 0x00, 0x74,
    0x00, 0x74, 0x00, 0x72, 0x00, 0x31, 0x00, 0x39
};



static const uint8_t HMAC_SHA256_key[] = {
    0xc2, 0x76, 0x46, 0x94, 0x0b, 0x94, 0xb7, 0xf3,
    0x54, 0x24, 0xa1, 0x19, 0x13, 0xd9, 0x4f, 0x96,
    0xc7, 0xa6, 0xd1, 0x58, 0x3b, 0xd7, 0x14, 0x23,
    0x9c, 0xb8, 0xbf, 0x26, 0x29, 0x7e, 0xf9, 0xb3
};
static const uint8_t HMAC_SHA256_data[] = {
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
static const uint8_t HMAC_SHA256_expected_result[] = {
    0x03, 0x03, 0xa1, 0xf3, 0x12, 0x9f, 0xbe, 0x7d,
    0xb9, 0x12, 0xef, 0x09, 0x7a, 0x44, 0xea, 0x4b,
    0xd0, 0x29, 0xe5, 0x45, 0x25, 0x21, 0x0f, 0x76,
    0x82, 0x17, 0x74, 0x33, 0xc6, 0x1a, 0x65, 0x13
};





int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
    bool all_tests_ok = true;
    int ret;
    
    TEST_all_crypto(AES_wrap_unwrap, AES_wrap_unwrap_kek, 256, AES_wrap_unwrap_wrapped_key, sizeof(AES_wrap_unwrap_wrapped_key), AES_wrap_unwrap_unwrapped_iv, AES_wrap_unwrap_unwrapped_key, 32);
    TEST_all_crypto(AES_CBC, AES_CBC_userKey, sizeof(AES_CBC_userKey)*8, AES_CBC_in, sizeof(AES_CBC_in), (unsigned char*)AES_CBC_iv, AES_CBC_expected_result, sizeof(AES_CBC_expected_result));
    TEST_all_crypto(AES_XTS, AES_XTS_key1, sizeof(AES_XTS_key1), AES_XTS_key2, sizeof(AES_XTS_key2), AES_XTS_encrypted_text, sizeof(AES_XTS_encrypted_text), AES_XTS_uno, AES_XTS_expected_result, sizeof(AES_XTS_expected_result));
    TEST_all_crypto(DES_CBC, DES_CBC_key, DES_CBC_iv, DES_CBC_in, sizeof(DES_CBC_in), DES_CBC_expected_result, sizeof(DES_CBC_expected_result));
    TEST_all_crypto(PBKDF2_HMAC_SHA1, PBKDF2_HMAC_SHA1_pass, strlen(PBKDF2_HMAC_SHA1_pass), PBKDF2_HMAC_SHA1_salt, sizeof(PBKDF2_HMAC_SHA1_salt), 192307, PBKDF2_HMAC_SHA1_expected_result, sizeof(PBKDF2_HMAC_SHA1_expected_result));
    TEST_all_crypto(PBKDF2_HMAC_SHA256, (const uint8_t*)PBKDF2_HMAC_SHA256_pass, strlen(PBKDF2_HMAC_SHA256_pass), PBKDF2_HMAC_SHA256_salt, sizeof(PBKDF2_HMAC_SHA256_salt), PBKDF2_HMAC_SHA256_iterations, PBKDF2_HMAC_SHA256_expected_result, sizeof(PBKDF2_HMAC_SHA256_expected_result));
    TEST_all_crypto(HMAC_SHA1, HMAC_SHA1_key, sizeof(HMAC_SHA1_key), HMAC_SHA1_data, sizeof(HMAC_SHA1_data), HMAC_SHA1_expected_result, sizeof(HMAC_SHA1_expected_result));
    TEST_all_crypto(HMAC_SHA256, HMAC_SHA256_key, sizeof(HMAC_SHA256_key), HMAC_SHA256_data, sizeof(HMAC_SHA256_data), HMAC_SHA256_expected_result, sizeof(HMAC_SHA256_expected_result));



    return all_tests_ok ? 0 : 1;
}

