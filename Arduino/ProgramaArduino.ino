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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
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
  
      analogWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      delay(100);
}

void sur(){
  
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);  

      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW); 

      delay(100);
}

void este(){
  
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW); 

      delay(100);
}

void oeste(){

      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW); 

      digitalWrite(ENB, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);  

      delay(100);
}

void parar(){

      digitalWrite(ENA, LOW);
      digitalWrite(ENB, LOW);
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
