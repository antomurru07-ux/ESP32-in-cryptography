ESP32 in cryptography
DESCRIPTION
This project is born from a school project consisting in cryptography. 
I have developed this project to show a few examples of protection for the microcontroller esp32.
The project consists of three esp 32 modules, two of those are custom made by my teacher “ingifranco”, a DHT11 sensor and a microSD card. 
The logic is the following: the esp32-S3 gets the temperature and humidity value from the DHT11 sensor, it stores those data in two different ways into the SD card, one is encrypted following the AES-128 CBC protocol while the other is plain text. Moreover it takes the plain text and sends it to the second esp-32-C3 through the protocol ESP32-NOW encrypted.
In addition I have decided to use a third esp-32 module to show the effectiveness of the security of the protocol, simulating a low level try of intercepting the message. 
The Python code is the decryptor for testing if the AES-128 CBC works correctly.

HOW TO INSTALL 
For this project several ways can be used to get started.
1 Arduino IDE  
-install and launch Arduino IDE
-in the File menu click on Preferences and paste this link in Additional boards manager URLs: 
“https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json”
-on the left there are 5 icons, click the 2nd, search and  install “esp32 by Espressif System“
-connect the board to the PC and on top click  where it normally says “Select Board”,                  next to the Bebug button, click the board that pops out (note: in case you aren’t sure wut COM is your device just unplug it and see which COM disappears and reappear back once you replug the device back)
-depending on what it says it’s gonna open different menus, click ok.
-goes on the Tools menu, on the top, and click Board and then esp32 and choose the one suitable for your esp32. (note: if you pick the wrong board is gonna pop an error that says something like “A fatal error occurred: This chip is ESP32-S3, not ESP32-C3. Wrong chip argument?
Failed uploading: uploading error: exit status 2
 “, so proceed to replace the chip with the correct one)
-you are ready to go now 
2 PlatformIO
-install and launch Visual Studio Code 
-ont he left menu click the 5th button called the Extensions
-search and install “PlatformIO IDE” 
-restart VS code
-after that make sure the icon have appeared on the left menu
how use the decrypter 
-write on the terminal “pip install pycryptodome“ to install pycryptodome
-then type ”python decrypt_log.py datiCriptati.txt” for indicating to the program what file decrypt, make sure that your file is called “datiCriptati.txt” so that the program can successfully translate it 

Huge thanks to “ingifranco” for giving me the needed material and guiding me throughout the entire process.

TUTORIAL I USED 
https://randomnerdtutorials.com/esp32-esp-now-encrypted-messages/
https://randomnerdtutorials.com/esp32-microsd-card-arduino/
https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/
https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
If you have problem with installations
https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/#2
https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/


