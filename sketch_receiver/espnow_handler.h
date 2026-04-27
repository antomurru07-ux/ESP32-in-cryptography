#pragma once
#include <esp_now.h>
#include <stdint.h>

bool espnow_init();
void printMAC(const uint8_t* mac_addr);
void OnDataRecv(const uint8_t* mac_addr, const uint8_t* incomingData, int len);