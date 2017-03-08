#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

#define WIFI_SSID "<ssid>"
#define WIFI_PASS "<password>"

#define DHT_PIN  14
#define DHT_TYPE DHT11

#define AIO_HOST "io.adafruit.com"
#define AIO_KEY  "b9f5ba0712f91deb9eefdc1faf5dee06415d380f"
#define AIO_SSL_FINGERPRINT "26 96 1C 2A 51 07 FD 15 80 96 93 AE F7 32 CE B9 0D 01 55 C4"

// Initialize DHT sensor:
// For working with a faster than ATmega328p 16 MHz Arduino chip, like an ESP8266,
// you need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// This is for the ESP8266 processor on ESP-01
DHT dht(DHT_PIN, DHT_TYPE, 11); // 11 works fine for ESP8266


/**
 * Function to send data to io.adafruit.com
 */
void io (String feedName, float value)
{
  static WiFiClientSecure client;

  if ( ! client.connect(AIO_HOST, 443))
  {
    Serial.println("Connection failed");
    return;
  }

  if ( ! client.verify(AIO_SSL_FINGERPRINT, AIO_HOST))
  {
    Serial.println("Connection insecure! Abort");
    return;
  }

  String aioKey = AIO_KEY;
  String path = "/api/feeds/" + feedName + "/data";
  String data = "value=" + String(value, 1);

  client.print("POST " + path + " HTTP/1.1\r\n");
  client.print("Host: io.adafruit.com:443\r\n");
  client.print("x-aio-key: " + aioKey + "\r\n");
  client.print("Connection: close\r\n");
  client.print("Content-Type: application/x-www-form-urlencoded\r\n");
  client.print("Content-Length: " + String(data.length()) + "\r\n\r\n");
  client.print(data);

  Serial.println(feedName + " = " + String(value, 1));
}

void setup ()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop()
{
  static float h = dht.readHumidity();
  static float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Logging to io.adafruit.com
  io("humidity", h);
  io("temperature", t);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  delay(60000); // 60s
}
