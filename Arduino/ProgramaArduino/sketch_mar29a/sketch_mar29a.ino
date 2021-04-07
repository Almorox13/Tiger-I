int pin = A3;
int value;
void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop() {
  analogRead(pin);
  Serial.println(analogRead(pin));

  if (value >= 50) {
  }
  else {

  }
  delay(1000);
}
