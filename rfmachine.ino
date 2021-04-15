#include <RCSwitch.h>

int transmitPin = 0; // Change this to use your board's pin to the transmitter

RCSwitch rfmachine = RCSwitch();

/*
 * Commands for the Gigolo "A" remote
 */
void gigolo_a_up() {
  rfmachine.sendTriState("FFFFF1111000");
  Serial.println("Gigolo (A) Speed UP");
}

void gigolo_a_ok() {
  rfmachine.sendTriState("FFFFF1110010");
  Serial.println("Gigolo (A) ON/OFF");
}

void gigolo_a_down() {
  rfmachine.sendTriState("FFFFF1110100");
  Serial.println("Gigolo (A) Speed Down");
}

/*
 * Commands for the Tremblr "A" remote
 */
void tremblr_a_up() {
  rfmachine.sendTriState("11FFFF001000");
  Serial.println("Tremblr (A) Speed Up");
}

void tremblr_a_ok() {
  rfmachine.sendTriState("11FFFF000010");
  Serial.println("Tremblr (A) ON/OFF");
}

void tremblr_a_down() {
  rfmachine.sendTriState("11FFFF000100");
  Serial.println("Tremblr (A) Speed Down");
}
void tremblr_a_suck_up() {
  rfmachine.sendTriState("11FFFF000001");
  Serial.println("Tremblr (A) Suck Up");
}

void tremblr_a_suck_down() {
  rfmachine.sendTriState("11FFFF010000");
  Serial.println("Tremblr (A) Suck Down");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rfmachine.enableTransmit(transmitPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  tremblr_a_ok(); // Starts the machne
  delay(20000);   // Waits 20 seconds
  tremblr_a_ok(); // Stops the machine
}
