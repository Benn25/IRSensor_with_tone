#include <Arduino.h>

/*IR environmental perfect filter with:
1)pulse tone
2)no library
3)fucking awesome
TODO:
>trouver un moyen (physique ou software) de changer la sensibilite du recepteur (pas forcement necessaire si une LED IR puissante est utilisee)
>necessite de capter plusieurs signaux positifs successif pour declencher un trigger ?
>floating frequency pour filtrer encore mieux l'environment?
*/

#define LED 2 //the LED for the user to see
#define SENS A0 // the IR sensor (phototransistor, Emitor to GND, collector to Signal pulled UP like :
     // https://electropeak.com/learn/interfacing-tcrt5000-reflective-infrared-sensor-with-arduino/)
#define IR 5 //the IR LED

int pulseLen; //length of the pulse, in microSec

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(SENS, INPUT);
  pinMode(IR, OUTPUT);
}

void loop() {
  tone(IR, 50); //emit flashes @ 50Hz

pulseLen = pulseIn(SENS, LOW, 30000); //listen for pulses (with cuttoff around 33Hz for efficiency)
Serial.print(pulseLen);

if (pulseLen > 0) { //a pulse is detected !!
//now test for the good frequency:
  pulseLen > 9000 & pulseLen < 11000 ? digitalWrite(LED, HIGH) : digitalWrite(LED, LOW); // light up the LED if the deteced signal is 50Hz
}
else{
  digitalWrite(LED, LOW);
  //circulez ya rien a voir!
}

}
