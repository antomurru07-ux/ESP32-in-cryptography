#pragma once

// ─── DHT ───────────────────────────────────────────────────────────────────
#define DHTPIN  2
#define DHTTYPE DHT11

// ─── SPI / SD ──────────────────────────────────────────────────────────────
#define SCK   12
#define MISO  13
#define MOSI  11
#define CS    10

// ─── I2C / PCF8574 ─────────────────────────────────────────────────────────
#define ADDR_PCF 0x3F
#define I2C1_SCL 9
#define I2C1_SDA 8

// ─── ESP-NOW ────────────────────────────────────────────────────────────────
// Indirizzo MAC del ricevitore
extern uint8_t receiverAddress[6];

#define PMK_KEY_STR "MyPMK1234567890"
#define LMK_KEY_STR "MyLMK1234567890"

// ─── AES-128 ────────────────────────────────────────────────────────────────
// Chiave AES: definita in crypto.cpp
extern const uint8_t AES_KEY[16];
