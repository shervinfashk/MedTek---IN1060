// Denne koden brukes for en prototype laget av gruppe MedTek i emne IN1060 ved UiO. Koden bruker eksempelfiler fra Arduino IDE som "ping" og ressurser fra Arduino sin nettside. F. eks: https://docs.arduino.cc/tutorials/generic/basic-servo-control/


#include <Servo.h>  // inkluderer bibliotek for å kunne bruk servo

Servo Servo1;  // oppretter et servo objekt

// oppretter en rekke konstanter og "navngir" pinnene slik at det blir lettere å bruke i loop()
const int servoPin = 9;
const int piezoPin = 10;
const int trigPinAapning = 8;
const int echoPinAapning = 7;
const int trigPinSoppel = 13;
const int echoPinSoppel = 12;
const int rodt = 4;
const int gront = 5;
const int apneManueltPin = 3;


// oppretter to variabler som skal vite hvor lenge siden servoen og piezoen ble brukt
unsigned long servoMoveTime = 0;
unsigned long piezoTime = 0;
// variabel for å sjekke om servoen er åpen
bool venter = false;

// variabler som brukes av ultralydsensorene
long lengdeForApne, cmForApning, lengdeForSoppel, cmForSoppel;

void setup() {
  Serial.begin(9600);  // brukes for å printe ut avstandene ultralydsensorene har

  // setter de ulike pinnene som skal brukes i riktig tilstand
  pinMode(trigPinAapning, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(echoPinAapning, INPUT);
  pinMode(rodt, OUTPUT);
  pinMode(gront, OUTPUT);
  pinMode(trigPinSoppel, OUTPUT);
  pinMode(echoPinSoppel, INPUT);
  pinMode(apneManueltPin, INPUT_PULLUP);
  // tildeler servo-objektet pinnen sin
  Servo1.attach(servoPin);
  // setter servoen i lukket posisjon
  lukkServo();
}

void loop() {
  
  
  
  maalAvstandFelles();  // får begge ultralydsensorene tli å måle avstand
  unsigned long currentMillis = millis(); // sjekker hva "tiden" er nå
  
  
  if (digitalRead(apneManueltPin) == LOW) { // manuel overskriding av åpning og lukking
    aapneServo(currentMillis);
  }
  
  if (!venter && cmForApning <= 30 && cmForSoppel > 13) { // hvis servoen ikke er åpen, noen er 30cm eller nærmere og kanyleboksen ikke er full
    aapneServo(currentMillis);
  }

  if (venter && cmForApning > 30) { // hvis vi har åpnet boksen og ingen er foran den
    lukkServo(currentMillis);
  }

  if (cmForSoppel <= 13 && !venter) { // hvis boksen er lukket og kanyleboksen er full
    oppdagetSoppel(currentMillis);
  } else {
    ikkeNokSoppel();
  }

  skrivUtAvstand();
}

void maalAvstandFelles() {  // får begge sensorene til å måle avstand, bruker disse verdiene i en funksjon som konverterer til cm
  lengdeForApne = maalAvstandIndividuelt(trigPinAapning, echoPinAapning);
  lengdeForSoppel = maalAvstandIndividuelt(trigPinSoppel, echoPinSoppel);
  cmForApning = microsecondsToCentimeters(lengdeForApne);
  cmForSoppel = microsecondsToCentimeters(lengdeForSoppel);
}

long maalAvstandIndividuelt(int trigPin, int echoPin) {  // selve "mål avstand" funksjonen som gjør at ultralydsensorene fungerer
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

void aapneServo(unsigned long currentMillis) { // åpner servoen til 90 grader. tar i mot hva "klokka" er som argument og oppdaterer variabler
  Servo1.write(10);
  servoMoveTime = currentMillis;
  venter = true;
}

void lukkServo(unsigned long currentMillis) { // lukker servoen hvis servoen har vært åpnet i minst 3 sekunder
  if (currentMillis - servoMoveTime >= 5000) {
    Servo1.write(90);
    servoMoveTime = currentMillis;
    venter = false;
  }
}

void oppdagetSoppel(unsigned long currentMillis) { // hvis den ene ultralydsensoren oppdager søppel endrer vi tilstandene til lyset og lager en lyd for å varsle hvert 2,5 sekund
  digitalWrite(gront, LOW);
  digitalWrite(rodt, HIGH);

  if (currentMillis - piezoTime >= 2000) {
    tone(piezoPin, 1000);
    piezoTime = currentMillis;
  } else {
    noTone(piezoPin);
  }
}

void ikkeNokSoppel() { // hvis kanyleboksen ikke er full nok så spilles det ingen lyd og lyset lyser grønt
  digitalWrite(gront, HIGH);
  digitalWrite(rodt, LOW);
  noTone(piezoPin);
}

void skrivUtAvstand() { // brukes for debugging
  Serial.print(cmForApning);
  Serial.println(" cm for åpning");

  Serial.print(cmForSoppel);
  Serial.println(" cm for søppel");
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void lukkServo() { // brukes i setup() 
  Servo1.write(90);
  venter = false;
}
