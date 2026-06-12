#pragma once
#include <Arduino.h>

/**
 * Strucutre of the packet sent by ESP-NOW
 * Must be identical on the receiver
 */
typedef struct struct_message {
  int  counter;
  char x[80];
} struct_message;

/**
 * Initialize WIFI in STA mode, ESP-NOW, PMK/LMK and add the peer
 * @return true if OK
 */
bool espnow_init();

/**
 * Send a paket at the receiver
 * @param counter  progressive number
 * @param payload  String to insert in the x field
 * @return true if esp_now_send has ESP_OK as result
  */
bool espnow_send_data(int counter, const char* payload);
