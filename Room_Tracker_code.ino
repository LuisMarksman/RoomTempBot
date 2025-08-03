#include "arduino_secrets.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4//I have chosen GPIO 4 on esp32
#define DHTTYPE DHT11

const char* ssid = "Your wifi name";
const char* password = "Your wifi password";

// Use your actual deployed Web App URL
const char* serverName = "webapp url ending with exec";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected.");
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  if (isnan(temp) || isnan(humid)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"temperature\":" + String(temp) + ",\"humidity\":" + String(humid) + "}";
    int httpCode = http.POST(payload);

    Serial.print("HTTP Response: ");
    Serial.println(httpCode);

    if (httpCode == 302) {
      String location = http.header("Location");
      Serial.print("Redirect to: ");
      Serial.println(location);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(60000); // Wait 1 minute before sending next reading
}
