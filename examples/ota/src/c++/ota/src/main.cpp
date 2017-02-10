/**
 * WifiManager: https://github.com/tzapu/WiFiManager
 */

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

// OTA
#include <ESP8266httpUpdate.h>

// Config
#define FIRMWARE_VERSION "firmware-v0.5"

#define OTA_SERVER_HOST "192.168.0.20"
#define OTA_SERVER_PORT 3000
#define OTA_SERVER_PATH "/ota.php"


// Function to upload new Firmware
void checkUpdate ()
{
  Serial.print("Checking for firmware update... ");

  t_httpUpdate_return ret = ESPhttpUpdate.update(
    OTA_SERVER_HOST, OTA_SERVER_PORT, OTA_SERVER_PATH, FIRMWARE_VERSION
  );

  switch(ret) {
    case HTTP_UPDATE_FAILED:
        Serial.printf(
          "Updated failed. Error (%d): %s\n",
          ESPhttpUpdate.getLastError(),
          ESPhttpUpdate.getLastErrorString().c_str()
        );
        break;
    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("No update found.");
        break;
    case HTTP_UPDATE_OK:
        Serial.println("Updated OK. Rebooting.");
        ESP.restart();
        break;
  }
}

void setup ()
{
  Serial.begin(115200);

  Serial.printf("Firmware version: %s\n", FIRMWARE_VERSION);

  /* Initialize wifiManager */
  WiFiManager wifiManager;

  //wifiManager.resetSettings();
  wifiManager.autoConnect("ESP8266-AP", "01234567");
}

void loop ()
{
  checkUpdate();
  delay(10000);
}
