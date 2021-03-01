//Motor 1
#define RPWM 2 // define pin 3 for RPWM pin (output)
#define LPWM 3 // define pin 6 for LPWM pin (output)
#define R_EN 4 // define pin 2 for R_EN pin (input)
#define L_EN 5 // define pin 7 for L_EN pin (input)
#define R_IS 50 // define pin 5 for R_IS pin (output)
#define L_IS 51 // define pin 8 for L_IS pin (output)

//Motor 2
#define RPWM2 6 // define pin 3 for RPWM pin (output)
#define LPWM2 7 // define pin 6 for LPWM pin (output)
#define R_EN2 8 // define pin 2 for R_EN pin (input)
#define L_EN2 9 // define pin 7 for L_EN pin (input)
#define R_IS2 52 // define pin 5 for R_IS pin (output)
#define L_IS2 53 // define pin 8 for L_IS pin (output)

#define CW 1 //do not change
#define CCW 0 //do not change

#define debug 1 //change to 0 to hide serial monitor debugging information or set to 1 to view
bool correcto = false;
char rec;

#include <RobojaxBTS7960.h>
#include <SoftwareSerial.h>

SoftwareSerial BT1(10, 11); // RX, TX se cruzan
RobojaxBTS7960 motor(R_EN,RPWM,R_IS, L_EN,LPWM,L_IS,debug);
RobojaxBTS7960 motor2(R_EN2,RPWM2,R_IS2, L_EN2,LPWM2,L_IS2,debug);

void setup() {
  BT1.begin(9600);
  Serial.begin(9600);
  motor.begin();
  motor2.begin();
}

void loop() {
  
  leer();

  if(correcto == true){
    
    while (rec == '0') {  //Gatillos x sin presión
      leer();
      motor.stop();
    }
    while (rec == '1') {  //Gatillo y sin presión
      leer();
      motor.stop();
    }

////////////////////////////////////////////////////

    while (rec == 'a') {
      leer(); 
      motor2.rotate(0, CCW); 
      motor.rotate(0, CCW);  
    }
    while (rec == 'b') {
      leer(); 
      motor2.rotate(0, CCW); 
      motor.rotate(5, CCW);  
    }
    while (rec == 'c') {
      leer(); 
      motor2.rotate(0, CCW); 
      motor.rotate(10, CCW);  
    }
    while (rec == 'd') {
      leer(); 
      motor2.rotate(0, CCW); 
      motor.rotate(15, CCW);  
    }
    while (rec == 'e') {
      leer(); 
      motor2.rotate(0, CCW); 
      motor.rotate(20, CCW);  
    }

////////////////////////////////////////////////////
    
    while (rec == 'f') {
      leer(); 
      motor2.rotate(5, CCW); 
      motor.rotate(0, CCW);  
    }
    while (rec == 'g') {
      leer(); 
      motor2.rotate(5, CCW); 
      motor.rotate(5, CCW);  
    }
    while (rec == 'h') {
      leer(); 
      motor2.rotate(5, CCW); 
      motor.rotate(10, CCW);  
    }
    while (rec == 'i') {
      leer(); 
      motor2.rotate(5, CCW); 
      motor.rotate(15, CCW);  
    }
    while (rec == 'j') {
      leer(); 
      motor2.rotate(5, CCW); 
      motor.rotate(20, CCW);  
    }

////////////////////////////////////////////////////
    
    while (rec == 'k') {
      leer(); 
      motor2.rotate(10, CCW); 
      motor.rotate(0, CCW);  
    }
    while (rec == 'l') {
      leer(); 
      motor2.rotate(10, CCW); 
      motor.rotate(5, CCW);  
    }
    while (rec == 'm') {
      leer(); 
      motor2.rotate(10, CCW); 
      motor.rotate(10, CCW);  
    }
    while (rec == 'n') {
      leer(); 
      motor2.rotate(10, CCW); 
      motor.rotate(15, CCW);  
    }while (rec == 'o') {
      leer(); 
      motor2.rotate(10, CCW); 
      motor.rotate(20, CCW);  
    }

////////////////////////////////////////////////////

    while (rec == 'p') {
      leer(); 
      motor2.rotate(15, CCW); 
      motor.rotate(0, CCW);  
    }
    while (rec == 'q') {
      leer(); 
      motor2.rotate(15, CCW); 
      motor.rotate(5, CCW);  
    }
    while (rec == 'r') {
      leer(); 
      motor2.rotate(15, CCW); 
      motor.rotate(10, CCW);  
    }
    while (rec == 's') {
      leer(); 
      motor2.rotate(15, CCW); 
      motor.rotate(15, CCW);  
    }while (rec == 't') {
      leer(); 
      motor2.rotate(15, CCW); 
      motor.rotate(20, CCW);  
    }

////////////////////////////////////////////////////
    
    while (rec == 'u') {
      leer(); 
      motor2.rotate(20, CCW); 
      motor.rotate(0, CCW);  
    }
    while (rec == 'v') {
      leer(); 
      motor2.rotate(20, CCW); 
      motor.rotate(5, CCW);  
    }
    while (rec == 'w') {
      leer(); 
      motor2.rotate(20, CCW); 
      motor.rotate(10, CCW);  
    }
    while (rec == 'x') {
      leer(); 
      motor2.rotate(20, CCW); 
      motor.rotate(15, CCW);  
    }
    while (rec == 'y') {
      leer(); 
      motor2.rotate(20,CCW); 
      motor.rotate(20,CCW);  
    }
  }
}

bool leer(){
  if (BT1.available()) {

    rec = BT1.read();
    Serial.println(rec);

    correcto = true;
    return correcto;
  }
}
