#include "espnow_manager.h"
#include "config.h"
#include <esp_now.h>
#include <WiFi.h>

// ─── Indirizzo MAC ricevitore ────────────────────────────────────────────────
uint8_t receiverAddress[6] = {0xA0, 0x76, 0x4E, 0x7C, 0x4B, 0x58};

static esp_now_peer_info_t peerInfo;

// ─── Callback invio ─────────────────────────────────────────────────────────
static void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  Serial.print("[ESP-NOW] Stato invio: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FAIL");
}

// ─── Init ───────────────────────────────────────────────────────────────────
bool espnow_init() {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("[ESP-NOW] Errore init");
    return false;
  }

  // PMK globale
  esp_now_set_pmk((uint8_t*)PMK_KEY_STR);

  // Configura peer con LMK e cifratura
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = true;
  for (uint8_t i = 0; i < 16; i++) {
    peerInfo.lmk[i] = LMK_KEY_STR[i];
  }

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("[ESP-NOW] Errore aggiunta peer");
    return false;
  }

  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

  Serial.println("[ESP-NOW] OK");
  return true;
}

// ─── Invia dati ─────────────────────────────────────────────────────────────
bool espnow_send_data(int cnt, const char* payload) {
  struct_message msg;
  msg.counter = cnt;
  snprintf(msg.x, sizeof(msg.x), "%s", payload);

  esp_err_t result = esp_now_send(receiverAddress,
                                  (uint8_t*)&msg, sizeof(msg));
  if (result == ESP_OK) {
    Serial.println("[ESP-NOW] Pacchetto inviato");
    return true;
  }
  Serial.println("[ESP-NOW] Errore invio");
  return false;
}
