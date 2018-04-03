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
 
       digitalWrite(PIN_LED_OUTPUT, LOW);
       delay(200);
       digitalWrite(PIN_LED_OUTPUT, HIGH);
       delay(200);
       digitalWrite(PIN_LED_OUTPUT, LOW);
       delay(200);
       digitalWrite(PIN_LED_OUTPUT, HIGH);
       delay(400);
      //Serial.println("connected");  
 
    } else {
 
      //Serial.print("failed with state ");
      //Serial.print(client.state());
      delay(2000);
 
    }
  }
}

// the loop function runs over and over again forever
void loop() {
   if(digitalRead(PIN_DOORBELL_SWITCH)) {
        digitalWrite(PIN_LED_OUTPUT, LOW);
        delay(300);
        digitalWrite(PIN_LED_OUTPUT, HIGH);
        client.publish("esp/test", "Hello from ESP8266");
        delay(300); 
   }
    client.loop();
}
