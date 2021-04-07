
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



void setup() {

// ---------- Setup Data ---------- //

 pinMode(pin1, INPUT);
 pinMode(pin2, INPUT);
 pinMode(pin3, INPUT);
 pinMode(pin4, INPUT);


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
}

void loop() {

  // ---------- Read Data ---------- //

  int p1 = digitalRead(pin1);
  int p2 = digitalRead(pin2);
  int p3 = digitalRead(pin3);
  int p4 = digitalRead(pin4);

  //Serial.println(String(p1) + "  " + String(p2) + "  " + String(p3) + "  " + String(p4));

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

  //-------------------------------------------------  Stop
  
}

void moveTorret(int p3, int p4){

  if(p3 == 0){
    if(p4 == 0){

      //----------------------------------------------  Parar Torreta
      
    }else{

      //----------------------------------------------  Torreta Izq
     
    }
  }else{

      //----------------------------------------------  Torreta Der
  }
}

void moveCannon(int p3, int p4){

  if(p3 == 1){
    if(p4 == 0){

      //----------------------------------------------  Cañon Up
      
    }else{

      //----------------------------------------------  Cañon Stop
     
    }
  }else{

      //----------------------------------------------  Cañon Down
  }
}

void tracksControl(int p2, int p3, int p4){

  if(p2 == 0){

    if(p3 == 0){

      if(p4 == 0){

        Serial.println("1");
        //----------------------  1
        
      }else{
        Serial.println("2");

        //----------------------  2
        
      }
    }else{

      if(p4 == 0){
        Serial.println("3");

        //----------------------  3
        
      }else{
        Serial.println("4");

        //----------------------  4
        
      }
    }
  }else{
    
    if(p3 == 0){

      if(p4 == 0){
          Serial.println("5");

        //----------------------  5
        
      }else{
        Serial.println("6");

        //----------------------  6
        
      }
    }else{

      if(p4 == 0){
        Serial.println("7");

        //----------------------  7
        
      }else{
        Serial.println("8");

        //----------------------  8
        
      }
    }
  }
}
