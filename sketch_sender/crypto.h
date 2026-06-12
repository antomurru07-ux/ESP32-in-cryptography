#pragma once
#include <Arduino.h>

/**
 * Initialize the generator of random numbers (DRBG) necessary for IV.
 * Call once in Setup()
 * @return true if OK, false in case of error
 */
bool crypto_init();

/**
 * encrypt plain_text with AES-128 CBC + padding PKCS#7.
 * The buffer out_buf contains: [IV 16 byte][ciphertext].
 * @return number of byte written in out_buf, 0 if error
 */
size_t encrypt_data(const char* plain_text, uint8_t* out_buf, size_t out_size);

/**
 * Convert an array of byte in a uppercase HEX string
 * hex_out must be of at least len*2+1 byte.
 */
void bytes_to_hex(const uint8_t* data, size_t len, char* hex_out);
