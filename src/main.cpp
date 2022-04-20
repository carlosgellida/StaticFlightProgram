#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

/*const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789"; */

const char* ssid = "IZZI-2124";
const char* password =  "Antigatos7";
  

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  //WiFi.softAP(ssid, password);
  if(!SPIFFS.begin()){
        while(true) ; 
  }

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/app.js", "text/javascript");
  });

  server.begin();
}

void loop() {
  
}