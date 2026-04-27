# ESP32-in-cryptography
the esp32-S3 gets the temperature and humidity value from the DHT11 sensor, it stores those data in two different ways into the SD card, one is encrypted following the AES-128 CBC protocol while the other is plain text. Moreover it takes the plain text and sends it to the second esp-32-C3 through the protocol ESP32-NOW encrypted.
