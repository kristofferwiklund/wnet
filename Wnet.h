#ifndef Wnet_h
#define Wnet_h

#include "Arduino.h"
#include <ESP8266WiFi.h>

class Wnet
{
  public:
    Wnet(char* ssid, char* password, char* hostname, char* scriptname, char* unitname);
    void setup();
    void setUnitname(char* unitname);
    void setHostname(char* hostname);
    void clearData();
    void addData(char* key, char* value);
    void addData(String key, String value);
    void sendData(char* cmd);
  private:
    char* _ssid;
	  char* _password;
	  char* _hostname;
    char* _scriptname;
    char* _unitname;
    bool _ledActive;
    WiFiClient _client;
    int _httpPort;
    String _data;
};

#endif

