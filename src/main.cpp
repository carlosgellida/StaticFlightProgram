#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include <ESPmDNS.h> // Call the server with name istead of IP
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <string>


const char* ssid = "FIME-POSGRADO";
const char* password =  "pereira2018";

const char* input_parameter1 = "input_string";
const char* input_parameter2 = "input_integer";
const char* input_parameter3 = "input_float";
  
Servo servoPin2 ; //M8

AsyncWebServer server(80);

/*char strin2int(String str){
  char output; 
  if(sizeof(str) == 3){
    output = 100 * *((char *) str[0]) ; 
    output += 10 * *((char *) str[1]) ;
    output += *((char *) str[2]) ;
  }  else if(str.len() == 2){
    output = 10 * *((char *) str[1]) ;
    output += *((char *) str[2]) ;
  } else if(str.len() == 0){
    output = *((char *) str[2]) ; 
  }
  return output ; 
}*/

void setup() {
  Serial.begin(115200);

  servoPin2.attach(2) ;

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

  server.on("/senData", HTTP_GET, [](AsyncWebServerRequest *request){
    int paramsNr = request->params();
    Serial.println(paramsNr);
 
    for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value()); 
        Serial.println("------");
        /*char * servo1Input ; 
        i<p->value()
        for(int i=0; i<p->value().length(); i++){

        }
        strcpy(servo1Input, p->value())  ; 
        servoPin2.write(atoi(servo1Input));*/
        //servoPin2.write(atol(servo1Input));
    }
    request->send(200, "text/plain", "message received");
  });

  server.begin();
}

void loop() {
  
}
