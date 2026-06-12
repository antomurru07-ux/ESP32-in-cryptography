#pragma once
#include <Arduino.h>

/**
 * Initialize SPI and mount SD card
 * @return true if OK
 */
bool sd_init();

/**
 * Add message at the bottom of the path file
 */
void sd_append(const char* path, const char* message);

/**
 * Read and print on Serial the data of the path file 
 */
void sd_read(const char* path);
