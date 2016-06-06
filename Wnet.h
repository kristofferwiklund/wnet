#ifndef Wnet_h
#define Wnet_h

#include "Arduino.h"

class Wnet
{
  public:
    Wnet(char* ssid,char* password,char* host);
  private:
    char* _ssid;
	char* _password;
	char* _host;
};

#endif

