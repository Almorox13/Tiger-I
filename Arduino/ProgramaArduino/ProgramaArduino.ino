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
int power = 5;

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
  power = 5;
  if (correcto == true) {

      while (rec == '0') {  //Detenido
          leer();
          //motor.stop();
          //motor2.stop();
      }
      ////////////////////////////////////////////////////

      while (rec == '1') {  // izq 1 der 0
          leer();

          if (power <= 20) {

              power++;
          }
          Serial.println("Hacia la derecha");
          motor2.rotate(power, CCW);
          motor.rotate(0, CCW);
      }
      while (rec == '2') {  // izq 0 der 1
          leer();

          if (power <= 20) {

              power++;
          }
          Serial.println("Hacia la izquierda");
          motor2.rotate(0, CCW);
          motor.rotate(power, CCW);
      }
      while (rec == '3') {  // izq -1 der -1
          leer();

          if (power <= 20) {

              power++;
          }
          Serial.println("Hacia delante");
          motor2.rotate(power, CW);
          motor.rotate(power, CW);
      }
      while (rec == '4') {  // izq 1 der 1
          leer();

          if (power <= 20) {

              power++;
          }
          Serial.println("Hacia atrás");
          motor2.rotate(power, CCW);
          motor.rotate(power, CCW);
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
