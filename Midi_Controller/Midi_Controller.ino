#include <Arduino.h>
const int pot1 = A0;
const int pot2 = A1;
const int pot3 = A2;
const int buttonPin1 = 12;
const int buttonPin2 = 11;
const int buttonPin3 = 10;


void setup() {
  Serial.begin(9600);
  //Inits push buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  if(buttonState1 > 0){
    Serial.println("Button 1 Pressed.");
  }
  if(buttonState2 > 0){
    Serial.println("Button 2 Pressed.");
  }
  if(buttonState3 > 0){
    Serial.println("Button 3 Pressed.");
  }
  int potValue1 = analogRead(pot1);
  int potMIDI1 = map(potValue1,0,1023,0,127);
  
  int potValue2 = analogRead(pot2);
  int potMIDI2 = map(potValue2,0,1023,0,127);
  
  int potValue3 = analogRead(pot3);
  int potMIDI3 = map(potValue3,0,1023,0,127);

  Serial.print(potMIDI1);
  Serial.print("      ");
  Serial.print(potMIDI2);
  Serial.print("      ");
  Serial.print(potMIDI3);
  Serial.println("");
}
