#include <Servo.h>

Servo myservo;

int val;
int botaoCerveja = 3;

void setup() {
  myservo.attach(9);
  pinMode(botaoCerveja, INPUT);
  digitalWrite(botaoCerveja, HIGH);

}

void loop() {
 val = digitalRead(botaoCerveja);
   if (val != 1) {
       myservo.write(15);
       delay(15);
    }

}