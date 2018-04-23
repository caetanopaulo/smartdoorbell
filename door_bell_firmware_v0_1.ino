/*
 * SmartDoorbell project
 * Authors: Rick Slinkman, Paulo Caetano
 *
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const short PIN_LED_OUTPUT = 1;           // GPIO1 aka TX
const short PIN_DOORBELL_SWITCH = 3;  // GPIO3 aka RX

const char* ssid = "someSSID";
const char* password =  "somepassword";
const char* mqttServer = "192.168.2.4";
const int mqttPort = 1883;
const char* mqttUser = "mqttuser";
const char* mqttPassword = "someotherpassword";
 
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(PIN_LED_OUTPUT, OUTPUT);
  pinMode(PIN_DOORBELL_SWITCH, INPUT);

  //Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }
  //Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  
 
  while (!client.connected()) {
    //Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
       ledBlink(2,200);
       delay(400);
       attachInterrupt(PIN_DOORBELL_SWITCH, highInterrupt, HIGH);
      //Serial.println("connected");  
 
    } else {
 
      //Serial.print("failed with state ");
      //Serial.print(client.state());
      ledBlink(6,800);
      delay(2000);
 
    }
  }
}

volatile boolean turnOn = false;
// delay in milliseconds between blinks of the LED
unsigned int interval = 5000;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 3000;

// the loop function runs over and over again forever
void loop() {   
    client.loop(); 
    //delay(10);
    if(turnOn){
      turnOn = LOW;
      if ((millis() - lastDebounceTime) > debounceDelay) {
        lastDebounceTime = millis();
        ledBlink(1,250);
        client.publish("doorbell/activated", "Someone is at your door"); 
      }
      attachInterrupt(PIN_DOORBELL_SWITCH, highInterrupt, RISING);
    }
}

void ledBlink(int numberOfBlinks, int blinkingInterval){
   while(numberOfBlinks > 0){
       digitalWrite(PIN_LED_OUTPUT, LOW);
       delay(blinkingInterval);
       digitalWrite(PIN_LED_OUTPUT, HIGH);
       delay(blinkingInterval);
       numberOfBlinks = numberOfBlinks -1;
   }
}

void highInterrupt(){
    detachInterrupt(PIN_DOORBELL_SWITCH);
    turnOn = HIGH;
}

