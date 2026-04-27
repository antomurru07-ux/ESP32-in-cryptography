#include <WiFi.h>
#include <Wire.h>
#include "config.h"
#include "espnow_handler.h"


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  espnow_init();
}

void loop() {
  delay(1000);
  Serial.println("Nessun pacchetto ricevuto");
}