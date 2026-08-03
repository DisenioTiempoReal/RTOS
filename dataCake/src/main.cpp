#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define HTTP_POST_INTERVAL_MS (100000UL)


const char* ssid = "HUAWEI-1DA5";
const char* password = "20150628";

const char* serverName = "https://api.datacake.co/integrations/api/a7d0e072-2bdf-4dc2-bc3d-5992fc109da4/"; //TODO:update according Datacake Server URL

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<256> jsonDoc;
    jsonDoc["device"] = "ea1826f1-0cbb-46fb-a4a6-e20fd8889431";
   // Simulated sensor data using random()
    jsonDoc["temperature"] = random(200, 350) / 10.0;  // 20.0 to 35.0 °C
    jsonDoc["battery"]     = random(300, 420) / 100.0; // 3.00 to 4.20 V
    jsonDoc["humidity"]    = random(300, 900) / 10.0;  // 30.0% to 90.0%
    jsonDoc["co2"]         = random(400, 2000);        // 400 to 2000 ppm

    String requestBody;
    serializeJson(jsonDoc, requestBody);
    Serial.println("\n-----------------------------");
    Serial.println("Sending JSON to Datacake:");
    Serial.println(requestBody);
    Serial.println("-----------------------------");
    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(HTTP_POST_INTERVAL_MS); // Send data every 60 seconds
}