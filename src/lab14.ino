#include "oled-wing-adafruit.h"
#include <Blynk.h>
#include "MQTT.h"
/*
 * Project lab-14
 * Description:
 * Author:
 * Date:
 */
SYSTEM_THREAD(ENABLED);
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Received message on testTopic/wbk: \n");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    if (!strcmp(p, "1")) {
      digitalWrite(D7, HIGH);
    }
    if (!strcmp(p, "0")) {
      digitalWrite(D7, LOW);
    }
    Serial.println();
}
MQTT client("lab.thewcl.com", 1883, callback);
String message;

OledWingAdafruit display;

BLYNK_WRITE(V1) {
   message = param.asString();
   client.publish("testTopic/wbk", message);
}
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  client.subscribe("testTopic/wbk");
  display.setup();
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  pinMode(D4, OUTPUT);
  Blynk.begin("MViijk-riOK2QXDW7o1k0yJkajixIVMq", IPAddress(167, 172, 234, 162), 9090);
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