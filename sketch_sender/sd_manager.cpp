#include "sd_manager.h"
#include "config.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

static SPIClass spi(HSPI);

// ─── Init ───────────────────────────────────────────────────────────────────
bool sd_init() {
  spi.begin(SCK, MISO, MOSI, CS);
  if (!SD.begin(CS, spi, 80000000)) {
    Serial.println("[SD] Card Mount Failed");
    return false;
  }
  if (SD.cardType() == CARD_NONE) {
    Serial.println("[SD] Nessuna SD inserita");
    return false;
  }
  Serial.println("[SD] OK");
  return true;
}

// ─── Append ─────────────────────────────────────────────────────────────────
void sd_append(const char* path, const char* message) {
  File file = SD.open(path, FILE_APPEND);
  if (!file) {
    Serial.printf("[SD] Impossibile aprire %s in append\n", path);
    return;
  }
  file.print(message);
  file.close();
}

// ─── Read ───────────────────────────────────────────────────────────────────
void sd_read(const char* path) {
  Serial.printf("[SD] Lettura file: %s\n", path);
  File file = SD.open(path);
  if (!file) {
    Serial.printf("[SD] Impossibile aprire %s\n", path);
    return;
  }
  while (file.available()) Serial.write(file.read());
  Serial.println();
  file.close();
}
