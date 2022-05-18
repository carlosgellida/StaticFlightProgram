#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include <ESPmDNS.h> // Call the server with name istead of IP
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <string>

//const char* ssid = "FIME-POSGRADO";
//const char* password =  "pereira2018";
const char* ssid = "IZZI-2124";
const char* password =  "Antigatos7";

Servo actuator[5] ; 
int pines[5] = {27, 25, 2, 26, 0}; // M5, M7, M8, M6, ECO ULTRA

AsyncWebServer server(80);

class State {
  public: 
    char motor0, motor1, servo0, servo1, servo2 ; 
    State() ; 
    void setMotor0(int) ; 
    void setMotor1(int) ; 
    void setServo0(int) ; 
    void setServo1(int) ; 
    void setServo2(int) ;  
    void getCompactState(char *) ; 
} ;

State::State(){
  motor0 = 0;
  motor1 = 0; 
  servo0 = 0; 
  servo1 = 0; 
  servo2 = 0;  
}; 

void State::setMotor0(int pwm){
  pwm = pwm*180/255 ; // It is mapped to scale [0, 180]
  motor0 = (char) pwm ; 
  actuator[0].write(pwm) ;
} ; 

void State::setMotor1(int pwm){
  pwm = pwm*180/255 ; // It is mapped to scale [0, 180]
  motor1 = (char) pwm ; 
  actuator[1].write(pwm) ;
} ; 

void State::setServo0(int angle){
  angle = angle + 90 ; // If angle goes from -30 to 30 degrees
  servo0 = (char) angle ; 
  actuator[2].write(angle) ;
} ; 

void State::setServo1(int angle){
  angle = angle + 90 ; // If angle goes from -30 to 30 degrees
  servo1 = (char) angle ; 
  actuator[3].write(angle) ;
} ; 

void State::setServo2(int angle){
  angle = angle + 90 ; // If angle goes from -30 to 30 degrees
  servo2 = (char) angle ; 
  actuator[4].write(angle) ;
} ; 

void State::getCompactState(char * compactState){
  compactState[0] = this->motor0 ; 
  compactState[1] = this->motor1 ; 
  compactState[2] = this->servo0 ; 
  compactState[3] = this->servo1 ; 
  compactState[4] = this->servo2 ; 
  compactState[5] = '\0' ; 
}

State state ; 

char compactState[6]; 
String scompactState ; 


void setup() {

  for(int i=0; i < 5; i++){
    actuator[i].attach(pines[i]) ; 
  }

  
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

  server.on("/getData", HTTP_GET, [](AsyncWebServerRequest *request){
    state.getCompactState(compactState) ; 
    scompactState = compactState ; 
    request->send(200, "text/plain", scompactState);
  });

  server.on("/senData", HTTP_GET, [](AsyncWebServerRequest *request){
    //int paramsNr = request->params(); // return the number of parameters
    AsyncWebParameter* p = request->getParam(0);
    if(p->name() == "motor0"){
        state.setMotor0((p->value()).toInt()) ; 
        //Serial.print("motor0: ") ; 
        //Serial.println((int) state.motor0) ; 
    }
    if(p->name() == "motor1"){
        state.setMotor1((p->value()).toInt()) ; 
        //Serial.print("motor1: ") ; 
        //Serial.println((int) state.motor1) ; 
    }
    if(p->name() == "servo0"){
        state.setServo0((p->value()).toInt()) ; 
        //Serial.print("servo0: ") ; 
        //Serial.println((int) state.servo0) ; 
    }
    if(p->name() == "servo1"){
        state.setServo1((p->value()).toInt()) ; 
        //Serial.print("servo1: ") ; 
        //Serial.println((int) state.servo1) ; 
    }
    if(p->name() == "servo2"){
        state.setServo2((p->value()).toInt()) ; 
        //Serial.print("servo2: ") ; 
        //Serial.println((int) state.servo2) ; 
    }
    request->send(200, "text/plain", "message received");
  });

  server.begin();
}

void loop() {}
