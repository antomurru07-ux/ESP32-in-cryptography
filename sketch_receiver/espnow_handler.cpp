#include "espnow_handler.h"
#include "config.h"
#include <Arduino.h>
#include <string.h>

uint8_t     masterMacAddress[] = {0x68, 0xb6, 0xb3, 0x30, 0x72, 0x24};
const char* PMK_KEY_STR        = "MyPMK1234567890";
const char* LMK_KEY_STR        = "MyLMK1234567890";
struct_message myData;

void printMAC(const uint8_t* mac_addr) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2],
           mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
}

void OnDataRecv(const uint8_t* mac_addr, const uint8_t* incomingData, int len) {

  Serial.print("Pacchetto da: ");
  printMAC(mac_addr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Byte ricevuti: "); Serial.println(len);
  Serial.print("Numero:        "); Serial.println(myData.counter);
  Serial.print("X:             "); Serial.println(myData.x);
  delay(100);

}

bool espnow_init() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("[espnow] Init fallita");
    return false;
  }

  esp_now_set_pmk((uint8_t*)PMK_KEY_STR);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, masterMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = true;
  for (uint8_t i = 0; i < 16; i++)
    peerInfo.lmk[i] = LMK_KEY_STR[i];

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("[espnow] Aggiunta peer fallita");
    return false;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
  Serial.println("[espnow] OK");
  return true;
}