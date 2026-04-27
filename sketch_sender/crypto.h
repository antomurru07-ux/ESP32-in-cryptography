#pragma once
#include <Arduino.h>

/**
 * Inizializza il generatore di numeri casuali (DRBG) necessario per l'IV.
 * Chiamare una volta in setup().
 * @return true se OK, false in caso di errore
 */
bool crypto_init();

/**
 * Cifra plain_text con AES-128 CBC + padding PKCS#7.
 * Il buffer out_buf conterrà: [IV 16 byte][ciphertext].
 * @return numero di byte scritti in out_buf, 0 se errore
 */
size_t encrypt_data(const char* plain_text, uint8_t* out_buf, size_t out_size);

/**
 * Converte un array di byte in stringa esadecimale uppercase.
 * hex_out deve essere almeno len*2+1 byte.
 */
void bytes_to_hex(const uint8_t* data, size_t len, char* hex_out);
