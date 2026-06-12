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
// MAC Address of the receiver
extern uint8_t receiverAddress[6];

#define PMK_KEY_STR "MyPMK1234567890" // Primary Master Key: must be the same on ALL devices in the network
#define LMK_KEY_STR "MyLMK1234567890" // Local Master Key: per-peer key, must match between this device and the specific peer

// ─── AES-128 ────────────────────────────────────────────────────────────────
// AES key: defined in crypto.cpp
extern const uint8_t AES_KEY[16];
