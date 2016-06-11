#include "Arduino.h"
#include "Wnet.h"
#include <ESP8266WiFi.h>

Wnet::Wnet(char* ssid, char* password, char* hostname = "", char* scriptname = "", char* unitname = "") {
  _ssid = ssid;
  _password = password;
  _hostname = hostname;
  _scriptname = scriptname;
  if(strlen(unitname) == 0) {
    _unitname = "WnetUnit";
  } else {
    _unitname = unitname;
  }

  _ledActive = true;
  _httpPort = 80;
  clearData();
}

void Wnet::setUnitname(char* unitname) {
  _unitname = unitname;
}

void Wnet::setHostname(char* hostname) {
  _hostname = hostname;
}

void Wnet::setup(int baud=74880)
{
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  Serial.begin(baud);
  Serial.print(_unitname);
  Serial.println(" started");
  Serial.println("* * * * * * *");
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(_ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void Wnet::clearData() {
  _data = "client="+ String(_unitname);
}

void Wnet::addData(char* key, char* value) {
  addData(String(key),String(value));
}

void Wnet::addData(String key, String value) {
  _data = _data + "&" + key + "="+ value;
}

void Wnet::sendData(char* cmd) {
  long rssi = WiFi.RSSI();
  addData("rssi",String(rssi));
  unsigned long uptime = millis();
  addData("uptime",String(uptime));
  addData("cmd",cmd);

  Serial.print("http://");
  Serial.print(_hostname);
  Serial.print("/");
  Serial.println(_scriptname);
  Serial.println(_data);
  while(!_client.connect(_hostname, _httpPort)) {
    Serial.println("Connection failed!");
    delay(100);
  } 

  _client.print("POST /");
  _client.print(_scriptname);
  _client.println(" HTTP/1.1");
  _client.print("Host: ");
  _client.println(_hostname);
  _client.println("User-Agent: Arduino/1.0 Wnet/1.0");
  _client.println("Connection: close");
  _client.println("Content-Type: application/x-www-form-urlencoded;");
  _client.print("Content-Length: ");
  _client.println(_data.length());
  _client.println();
  _client.println(_data);
  delay(10);
  while(_client.available()){
    String line = _client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  _client.stop();
  Serial.println("closing connection");
}


