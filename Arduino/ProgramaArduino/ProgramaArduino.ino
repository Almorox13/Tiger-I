#include <SoftwareSerial.h>
SoftwareSerial BT1(10, 11); // RX, TX se cruzan

int IN1 = 2;
int IN2 = 3;
int ENA = 5;
int IN3 = 7;
int IN4 = 8;
int ENB = 9;
char rec;
bool correcto = false;

void setup()
{
  
  BT1.begin(9600);
  Serial.begin(9600);
}

void loop() {

  leer();

  if(correcto == true){
    
    while (rec == 'N') {

      norte();
      leer();
    }
    parar();

    while (rec == 'S') {

      sur();
      leer();

    }
    parar();

    while (rec == 'E') {

      este();
      leer();

    }
    parar();

    while (rec == 'O') {

      oeste();
      leer();

    }
    parar();
  
  }
}

void norte(){
  
     motor.rotate(100,CW);

      delay(100);
}

void sur(){
  
    motor.rotate(100,CCW);

      delay(100);
}

void este(){
  
      motor.rotate(100,CCW);
      delay(100);
}

void oeste(){

      motor.rotate(100,CW);
      delay(100);
}

void parar(){

     motor.stop();
      delay(50);
}

bool leer(){
  if (BT1.available()) {

    rec = BT1.read();
    Serial.println(rec);

    correcto = true;
    return correcto;
  }
}
