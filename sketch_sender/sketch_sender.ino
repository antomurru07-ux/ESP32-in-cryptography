// ─── External libraries ───────────────────────────────────────────────────────
#include "DHT.h"

// ─── Progejct modules ────────────────────────────────────────────────────
#include "config.h"
#include "crypto.h"
#include "sd_manager.h"
#include "espnow_manager.h"

// ─── Globals objects ────────────────────────────────────────────────────────
DHT dht(DHTPIN, DHTTYPE);
int pktCounter = 0;

// ─── Setup ──────────────────────────────────────────────────────────────────
void setup() {
  delay(3000);  // <-- giving enough time to the serial port to open
  Serial.begin(9600);
  Serial.println("=== START ===");  // if this doesn't appear, there is a problem in the baudrate

  if (!crypto_init())  { Serial.println(">> Crypto FAIL");   while (1) delay(1000); }
  Serial.println(">> Crypto OK");

  if (!sd_init())      { Serial.println(">> SD FAIL");       return; }
  Serial.println(">> SD OK");

  if (!espnow_init())  { Serial.println(">> ESP-NOW FAIL");  return; }
  Serial.println(">> ESP-NOW OK");


  dht.begin();
  Serial.println(">> DHT OK");

  Serial.println(">> Setup completed");
}
// ─── Loop ───────────────────────────────────────────────────────────────────
void loop() {
  delay(2000);

  // 1. Read sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(">> Error reading DHT");
    return;
  }

  // 2. Build string in plain text
  char plain_text[64];
  snprintf(plain_text, sizeof(plain_text),
           "humidity=%.1f temperature=%.1f", h, t);
  Serial.printf(">> Plaintext: %s\n", plain_text);

  // 3. Cipher with AES-128 CBC
  uint8_t cipher_buf[256];
  size_t  cipher_len = encrypt_data(plain_text, cipher_buf, sizeof(cipher_buf));
  if (cipher_len == 0) {
    Serial.println(">> Encryption failed");
    return;
  }

  // 4. Convert in HEX and save on SD
  char hex_str[514];
  bytes_to_hex(cipher_buf, cipher_len, hex_str);
  strcat(hex_str, "\n");

  char plain_line[80];
  snprintf(plain_line, sizeof(plain_line), "%s\n", plain_text);

  sd_append("/datiCriptati.txt", hex_str);
  sd_append("/datiChiaro.txt",   plain_line);

  // 5. Send throught ESP-NOW every 5 seconds
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 5000) {
    lastSend = millis();

    if (espnow_send_data(pktCounter++, plain_line)) {
      
    }
  }
}
