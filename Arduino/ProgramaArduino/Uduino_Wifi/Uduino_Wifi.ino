#include<Uduino_Wifi.h> // Notice that here we replace  uduino by Uduino_WiFi
Uduino_Wifi uduino("uduinoBoard");// Notice that here we replace 

void setup()
{
  uduino.connectWifi("your-ssid", "your-password"); // replace 
//... uduino.addCommand ...
}

void loop()
{
  uduino.update();
  if(uduino.isConnected()) {
    uduino.println("Connected!!");
  }
}
