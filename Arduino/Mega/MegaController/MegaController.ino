#include <Servo.h> 
#include <AccelStepper.h> 

// ---------- Pins Stepper ---------- //

#define HALFSTEP 8
#define motorPin1 8 
#define motorPin2 9 
#define motorPin3 10
#define motorPin4 11
AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);


// ---------- Pins Motor 1 ---------- //

int a_R_PWM = 2;
int a_L_PWM = 3;
int a_R_EN  = 30; 
int a_L_EN  = 32;
int a_R_IS  = 34;
int a_L_IS  = 36;


// ---------- Pins Motor 2 ---------- //

int b_R_PWM = 4;
int b_L_PWM = 5;
int b_R_EN  = 31; 
int b_L_EN  = 33;
int b_R_IS  = 35;
int b_L_IS  = 37;


// ---------- Pins Data ---------- //

int pin1 = 40;
int pin2 = 41;
int pin3 = 42;
int pin4 = 43;

// ---------- Cañón y torreta ---------- //

int posCannon = 0;
Servo cannon;


void setup() {

// ---------- Setup Stepper ----------//

 stepper.setMaxSpeed(2000);
 
// ---------- Setup Data ---------- //

 pinMode(pin1, INPUT);
 pinMode(pin2, INPUT);
 pinMode(pin3, INPUT);
 pinMode(pin4, INPUT);

cannon.attach(13);


// ---------- Setup Motor 1 ---------- //

 pinMode(a_R_IS, OUTPUT);
 pinMode(a_R_EN, OUTPUT);
 pinMode(a_R_PWM, OUTPUT);
 pinMode(a_L_IS, OUTPUT);
 pinMode(a_L_EN, OUTPUT);
 pinMode(a_L_PWM, OUTPUT);
 
 digitalWrite(a_R_IS, LOW);
 digitalWrite(a_L_IS, LOW);
 digitalWrite(a_R_EN, HIGH);
 digitalWrite(a_L_EN, HIGH);


// ---------- Setup Motor 2 ---------- //

 pinMode(b_R_IS, OUTPUT);
 pinMode(b_R_EN, OUTPUT);
 pinMode(b_R_PWM, OUTPUT);
 pinMode(b_L_IS, OUTPUT);
 pinMode(b_L_EN, OUTPUT);
 pinMode(b_L_PWM, OUTPUT);

 digitalWrite(b_R_IS, LOW);
 digitalWrite(b_L_IS, LOW);
 digitalWrite(b_R_EN, HIGH);
 digitalWrite(b_L_EN, HIGH);

 
 
 Serial.begin(9600);
 Serial.println("Iniciando");

  for(int i = 0; i <= 50; i++){
    Serial.print(".");
    delay(200);
  }
 
}

void loop() {

  // ---------- Read Data ---------- //

  int p1 = digitalRead(pin1);
  int p2 = digitalRead(pin2);
  int p3 = digitalRead(pin3);
  int p4 = digitalRead(pin4);

  Serial.println(String(p1) + "  " + String(p2) + "  " + String(p3) + "  " + String(p4));

  delay(50);


 if(p1 != 1){

    if((p2 == 0) && (p3 == 0) && (p4 == 0)){
  
      stopMotors();
    }
    if(p2 == 1){

      moveTorret(p3, p4);
      
    }else{

      moveCannon(p3, p4);
    }
 }else{

    tracksControl(p2, p3, p4);
 }
}

void stopMotors(){

        Serial.println("Stop");

        analogWrite(3, 0);
        analogWrite(2, 0);
        analogWrite(4, 0);
        analogWrite(5, 0);

  //-------------------------------------------------  Stop
  
}

void moveTorret(int p3, int p4){

  if(p3 == 0){
    if(p4 == 0){

      digitalWrite(8, LOW);     
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);

      //----------------------------------------------  Parar Torreta
      
    }else{
      stepper.setSpeed(-200);  
      stepper.runSpeed();
    }
  }else{

    Serial.print("osjkdlfnsdf");
    
     stepper.setSpeed(200);  
     stepper.runSpeed();
  }
}

void moveCannon(int p3, int p4){

  if(p3 == 1){
    if(p4 == 0){


      if(posCannon < 170){
        posCannon = posCannon + 10;
        cannon.write(posCannon);
      }

      Serial.println(posCannon);
    }else{
      
    }
  }else{

    if(p4 == 1){

      Serial.println(posCannon);
  
      if(posCannon > 10){
        posCannon = posCannon - 10;
        cannon.write(posCannon);
        Serial.println(posCannon);
      }
    }
  }
}

void tracksControl(int p2, int p3, int p4){

  //   5 ------ Derecho hacia detrás
  //   4 ------ Derecho hacia delante
  //   3 ------ Izquierdo hacia delante
  //   2 ------ Izquierdo hacia detrás

  if(p2 == 0){

    if(p3 == 0){

      if(p4 == 0){
        
        analogWrite(5, 0);
        analogWrite(4, 25);
        
        analogWrite(3, 25);
        analogWrite(2, 0);
        
        Serial.println("1");
        //----------------------  1
        
      }else{
        Serial.println("2");
        
        analogWrite(4, 10);
        analogWrite(3, 25);
        
        analogWrite(5, 0);
        analogWrite(2, 0);

       
        //----------------------  2
        
      }
    }else{

      if(p4 == 0){
        Serial.println("3");
        
        analogWrite(5, 20);
        analogWrite(3, 40);

        analogWrite(4, 0);
        analogWrite(2, 0);


        //----------------------  3
        
      }else{
        Serial.println("4");
        analogWrite(2, 25);
        analogWrite(3, 0);

        analogWrite(5, 10);
        analogWrite(4, 0);
        
        //----------------------  4
        
      }
    }
  }else{
    
    if(p3 == 0){

      if(p4 == 0){
        Serial.println("5");
        analogWrite(5, 25);
        analogWrite(2, 25);

        analogWrite(3, 0);
        analogWrite(4, 0);


        //----------------------  5
        
      }else{
        Serial.println("6");
        analogWrite(5, 25);
        analogWrite(2, 10);

        analogWrite(3, 0);
        analogWrite(4, 0);

        //----------------------  6
        
      }
    }else{

      if(p4 == 0){
        Serial.println("7");
        analogWrite(2, 20);
        analogWrite(4, 40);

        analogWrite(5, 0);
        analogWrite(3, 0);

        //----------------------  7
        
      }else{
        Serial.println("8");
        analogWrite(4, 25);
        analogWrite(3, 10);

        analogWrite(5, 0);
        analogWrite(2, 0);
        //----------------------  8        
      }
    }
  }
}
