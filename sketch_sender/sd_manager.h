#pragma once
#include <Arduino.h>

/**
 * Inizializza SPI e monta la SD card.
 * @return true se OK
 */
bool sd_init();

/**
 * Aggiunge message in coda al file path.
 */
void sd_append(const char* path, const char* message);

/**
 * Legge e stampa sul Serial il contenuto del file path.
 */
void sd_read(const char* path);
