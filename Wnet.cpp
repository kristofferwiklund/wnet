#include "Arduino.h"
#include "Morse.h"

Wnet::Wnet(char* ssid,char* password,char* host)
{
    _ssid = ssid;
	_password = password;
	_host = host;
}
/*
void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

*/