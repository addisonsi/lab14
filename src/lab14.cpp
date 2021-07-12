/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/addisonsimon/lab14/src/lab14.ino"
#include "oled-wing-adafruit.h"
#include <Blynk.h>
#include "MQTT.h"
/*
 * Project lab-14
 * Description:
 * Author:
 * Date:
 */
void callback(char* topic, byte* payload, unsigned int length);
void setup();
void loop();
#line 10 "/Users/addisonsimon/lab14/src/lab14.ino"
SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;
void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s",p);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(p);
  display.display();
  delay(1000);
  Serial.println();
  // if press 1 it turns led on, 0 turns it off
  if(p[0] == '1'){
    digitalWrite(D7,HIGH);
    Serial.println("ON");
  }
  if(p[0] == '0'){
    digitalWrite(D7,LOW);
    Serial.println("OFF");
  }
}
MQTT client("lab.thewcl.com", 1883, callback);
String message;


BLYNK_WRITE(V1) {
   message = param.asString();
   client.publish("testTopic/wbk", message);
   if(message == "1"){digitalWrite(D7, HIGH);}
   if(message == "0"){digitalWrite(D7, LOW);}
   display.clearDisplay();
   display.println(message);
   display.display();
}
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  display.setup();
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  Serial.begin(9600);
  pinMode(D7, OUTPUT);
  Blynk.begin("FQI3d79SCWEHkMActo_VZLsDHmLrUVPU", IPAddress(167, 172, 234, 162), 9090);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  Blynk.run();
  display.loop();
  if (client.isConnected()) {
    client.loop();
  } else {
    client.connect(System.deviceID());
    client.subscribe("something");
  }
  if(display.pressedA()){
    client.publish("testTopic/wbk", "A was pressed");
  }
  if(display.pressedB()){
    client.publish("testTopic/wbk", "B was pressed");
  }
  if(display.pressedC()){
    client.publish("testTopic/wbk", "C was pressed");
  }
}