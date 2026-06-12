#pragma once
#include <stdint.h>

// ── Pin ──────────────────────────────────────────
#define I2C_SDA  8
#define I2C_SCL  9
#define LED_PIN  2
#define ADDR_PCF 0x3F

// ── ESP-NOW ──────────────────────────────────────
extern uint8_t      masterMacAddress[6];
extern const char*  PMK_KEY_STR;
extern const char*  LMK_KEY_STR;

// ── Message structure ──────────────────────────
typedef struct {
  int  counter;
  char x[80];
} struct_message;

extern struct_message myData;
