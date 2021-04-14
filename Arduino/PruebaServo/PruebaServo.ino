#include <Servo.h>

Servo myservo;  // crea el objeto servo

int pos = 0;    // posicion del servo

void setup() {
  myservo.attach(9);  // vincula el servo al pin digital 9
}

void loop() {
  myservo.write(180);       

  delay(500);


    myservo.write(0);              

}
