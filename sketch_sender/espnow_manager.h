#pragma once
#include <Arduino.h>

/**
 * Struttura del pacchetto inviato via ESP-NOW.
 * Deve essere identica sul ricevitore.
 */
typedef struct struct_message {
  int  counter;
  char x[80];
} struct_message;

/**
 * Inizializza WiFi in STA mode, ESP-NOW, PMK/LMK e aggiunge il peer.
 * @return true se OK
 */
bool espnow_init();

/**
 * Invia un pacchetto al ricevitore.
 * @param counter  numero progressivo
 * @param payload  stringa da inserire nel campo x
 * @return true se esp_now_send ha restituito ESP_OK
 */
bool espnow_send_data(int counter, const char* payload);
