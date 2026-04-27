#include "crypto.h"
#include "config.h"
#include "mbedtls/aes.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include <string.h>

// ─── Chiave AES-128 (16 byte) ───────────────────────────────────────────────
// In produzione: caricarla dalla NVS invece di metterla qui
const uint8_t AES_KEY[16] = {
  0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
  0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C
};

// Stato interno del generatore casuale (privato a questo file)
static mbedtls_ctr_drbg_context ctr_drbg;
static mbedtls_entropy_context   entropy;

// ─── Padding PKCS#7 ─────────────────────────────────────────────────────────
static size_t pkcs7_pad(const char* in, size_t in_len,
                         uint8_t* out, size_t out_size) {
  uint8_t pad_len = 16 - (in_len % 16);
  size_t  total   = in_len + pad_len;
  if (total > out_size) return 0;
  memcpy(out, in, in_len);
  memset(out + in_len, pad_len, pad_len);
  return total;
}

// ─── Inizializzazione DRBG ──────────────────────────────────────────────────
bool crypto_init() {
  mbedtls_entropy_init(&entropy);
  mbedtls_ctr_drbg_init(&ctr_drbg);
  const char* pers = "esp32_aes_cbc";
  int ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
                                   (const unsigned char*)pers, strlen(pers));
  if (ret != 0) {
    Serial.println("[crypto] Errore init DRBG");
    return false;
  }
  Serial.println("[crypto] DRBG OK");
  return true;
}

// ─── AES-128 CBC encrypt ────────────────────────────────────────────────────
size_t encrypt_data(const char* plain_text, uint8_t* out_buf, size_t out_size) {
  size_t pt_len = strlen(plain_text);

  // 1. Padding PKCS#7
  uint8_t padded[256];
  size_t padded_len = pkcs7_pad(plain_text, pt_len, padded, sizeof(padded));
  if (padded_len == 0 || (16 + padded_len) > out_size) return 0;

  // 2. Genera IV casuale
  uint8_t iv[16];
  if (mbedtls_ctr_drbg_random(&ctr_drbg, iv, 16) != 0) {
    Serial.println("[crypto] Errore generazione IV");
    return 0;
  }

  // 3. Copia IV in testa all'output (serve al ricevitore per decifrare)
  memcpy(out_buf, iv, 16);

  // 4. CBC encrypt (usa copia dell'IV perché la funzione lo modifica)
  uint8_t iv_copy[16];
  memcpy(iv_copy, iv, 16);

  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, AES_KEY, 128);
  int ret = mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT,
                                   padded_len, iv_copy,
                                   padded, out_buf + 16);
  mbedtls_aes_free(&aes);

  if (ret != 0) {
    Serial.println("[crypto] Errore cifratura CBC");
    return 0;
  }
  return 16 + padded_len;  // IV + ciphertext
}

// ─── Bytes → stringa HEX ────────────────────────────────────────────────────
void bytes_to_hex(const uint8_t* data, size_t len, char* hex_out) {
  for (size_t i = 0; i < len; i++) {
    sprintf(hex_out + i * 2, "%02X", data[i]);
  }
  hex_out[len * 2] = '\0';
}
