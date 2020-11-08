# ESP32 OTA Programming

This repository acts as a framework that allows to Update the ESP32 firmware via WiFi.

## Configuration:

Copy the example h credentials file 

`cp arduino_secrets.h.example arduino_secrets.h`

Modify the copied file to include the corresponding credentials of your network by changing the defined constants SECRET_WIFI_SSID and SECRET_WIFI_PASS according to your AP SSID credentials.

Setup the desired password for the upload page changing the SECRET_WWW_USERNAME and SECRET_WWW_PASSWORD constants

## Installation:

For the first time you need to install the firmware with the Arduino IDE into the ESP32 board with a USB connected physical cable. After the firmware gets recorded into the flash memory of the board, open the serial monitor with Tools/Serial Monitor option and wait the device resets after installing. The device must connect to your wifi network if you've setup the wifi credentials and the signal is available. Take note of the IP address of the web server of the device.

## Compilation:

Open this projects main file esp32-over-the-air-programming.ino with the Arduino IDE and export the binary with the Sketch/Export compiled binary option. This will create a new .bin file with the binary compiled version of the firmware.

## OTA firmware upgrade:

Open your web browser and navigate to the IP you've seen on the Serial Monitor during the device boot up.
Input your credentials that you've configured in the first step of this README, select the file you've created in the compilation step. Then push upload and wait the progress bar reaches 100%, the device will reset and redirect you to the home page of the web server. You've successfully written a new firmware with Over The Air!