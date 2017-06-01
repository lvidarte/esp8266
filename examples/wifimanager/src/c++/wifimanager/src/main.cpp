/* https://github.com/esp8266/Arduino */
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

/* https://github.com/tzapu/WiFiManager */
#include <WiFiManager.h>


WiFiManager wifiManager;

const char* ssid = "xleo-ap";
const char* pass = "12345678";


void setup ()
{
  Serial.begin(115200);

  WiFiManager wifiManager;

  //wifiManager.resetSettings();
  wifiManager.autoConnect(ssid, pass);

  Serial.println("connected...yeey :)");
}

void loop ()
{
}
