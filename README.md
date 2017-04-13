# esp_avr_programmer
ESP8266 as wireless AVR (arduino) programmer

The program allows you to upload hex files to the ESP and use to them to flash an arduino, the files are stores on the ESP using the 3MB SPIFFS, the arduino is flashed but connection to the ESP with a browser (only tested with chrome).

1. Change the SSID and PASSWORD in code to give the ESP access to the wireless network.
2. Compile and upload the program using the Arduino IDE.
3. Install the Arduino IDE SPIFFS tool and use the tools>ESP8266 Data Upload, sends the html files to the ESP.
4. Connect the ESP TX/RX pins to the RX/TX pins on the arduino, and the ESP pin 4 to the Arduino reset pin.
5. Use a browser to connect to the ESP and upload a hex files, when uploaded click the flash link to flash the arduino.
