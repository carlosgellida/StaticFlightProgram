#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

void setup() {
  WiFi.softAP(ssid, password);
}

void loop() {
  
}