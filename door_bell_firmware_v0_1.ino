/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain

 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)

 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/


void setup() {
  pinMode(1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(3, INPUT);
  
   digitalWrite(1, LOW);                
   delay(200);                     
   digitalWrite(1, HIGH); 
   delay(200); 
   digitalWrite(1, LOW);  
   delay(200);                     
   digitalWrite(1, HIGH); 
   delay(400);
}

// the loop function runs over and over again forever
void loop() {
  
   if(digitalRead(3)) {
        digitalWrite(1, LOW);                
        delay(300);                     
        digitalWrite(1, HIGH);  
        delay(300);  
   }
                   
}
