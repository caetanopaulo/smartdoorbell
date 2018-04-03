/*
 * SmartDoorbell project
 * Authors: Rick Slinkman, Paulo Caetano
 *
 */

const PIN_OUTPUT = 1;           // GPIO1 aka TX
const PIN_DOORBELL_SWITCH = 3;  // GPIO3 aka RX

void setup() {
  pinMode(PIN_OUTPUT, OUTPUT);
  pinMode(PIN_DOORBELL_SWITCH, INPUT);

   digitalWrite(PIN_OUTPUT, LOW);
   delay(200);
   digitalWrite(PIN_OUTPUT, HIGH);
   delay(200);
   digitalWrite(PIN_OUTPUT, LOW);
   delay(200);
   digitalWrite(PIN_OUTPUT, HIGH);
   delay(400);
}

// the loop function runs over and over again forever
void loop() {
   if(digitalRead(PIN_DOORBELL_SWITCH)) {
        digitalWrite(PIN_OUTPUT, LOW);
        delay(300);
        digitalWrite(PIN_OUTPUT, HIGH);
        delay(300);
   }
}
