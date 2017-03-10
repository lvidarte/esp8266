#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

extern "C" {
  #include<user_interface.h>
}

/* Set these to your desired credentials. */
const char *ssid = "ESP-AP";
const char *password = "12345678";

ESP8266WebServer server(80);

String getHosts ()
{
  String json;
  struct station_info *stat_info;
  struct ip_addr *IPaddress;
  uint32 uintaddress;
  uint8_t firstElement = 1;

  stat_info = wifi_softap_get_station_info();

  json = "{\"hosts\":[";
  while (stat_info != NULL)
  {
    IPaddress = &stat_info->ip;
    uintaddress = IPaddress->addr;
    if (firstElement) {
      firstElement = 0;
    } else {
      json += ",";
    }
    json += "\"" +
      String(uintaddress&0xFF) + "." +
      String((uintaddress&0xFF00)>>8) + "." +
      String((uintaddress&0xFF0000)>>16) + "." +
      String((uintaddress&0xFF000000)>>24) + "\""
    ;
    stat_info = STAILQ_NEXT(stat_info, next);
  }
  json += "]}";

  return json;
}

/* Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot ()
{
	server.send(200, "application/json", getHosts());
}

void setup ()
{
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();

	server.on("/", handleRoot);
	server.begin();
}

void loop ()
{
	server.handleClient();
}
