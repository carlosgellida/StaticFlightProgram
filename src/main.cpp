#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include <ESPmDNS.h> // Call the server with name istead of IP
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>


const char* ssid = "FIME-POSGRADO";
const char* password =  "pereira2018";
  

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  //Begin FileSystem
  if(!SPIFFS.begin()){
        while(true) ; 
  }

  // Begin Wifi Conection 
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  // Begin DNS server to find device: http://esp32.local
  if(!MDNS.begin("esp32")) {
     Serial.println("Error starting mDNS");
     return;
  }


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/app.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/app.js", "text/javascript");
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/styles.css", "text/javascript");
  });

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");
  });

  server.begin();
}

void loop() {
  
}
