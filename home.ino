// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define DEBUG_ESP_PORT Serial
#define NODEBUG_WEBSOCKETS
#define NDEBUG
#endif

#include <Arduino.h>
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID       "ESP32Home"    
#define WIFI_PASS       "123456789"
#define APP_KEY         "563c70f4-6eac-42e5-ab1e-f9d8298f0ea7"
#define APP_SECRET      "e0a4df3d-002b-4a19-813e-aad0bf84f7c5-b11bc36f-06e2-4131-bfea-c53784aa2ac2"

// Device IDs from SinricPro
#define device_ID_1   "67dbf350bddfc53e33bc52b9"  // Bulb
#define device_ID_2   "67dbf380bddfc53e33bc5303"  // Fan

// GPIO Assignments
#define RelayPin1 23  // D23 (Relay 1 - Bulb)
#define RelayPin2 22  // D22 (Relay 2 - Fan)

#define wifiLed    2   // D2 (WiFi Status LED)

#define BAUD_RATE  9600

void setupRelays() { 
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  
  digitalWrite(RelayPin1, HIGH);  // Default OFF
  digitalWrite(RelayPin2, HIGH);  // Default OFF
}

bool onPowerState(String deviceId, bool &state) {
  Serial.printf("%s: %s\r\n", deviceId.c_str(), state ? "ON" : "OFF");

  if (deviceId == device_ID_1) {
    digitalWrite(RelayPin1, !state);  // Control Bulb
  } 
  else if (deviceId == device_ID_2) {
    digitalWrite(RelayPin2, !state);  // Control Fan
  }
  return true;
}

void setupWiFi() {
  Serial.printf("\r\n[WiFi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  digitalWrite(wifiLed, HIGH);
  Serial.printf("\n[WiFi]: Connected! IP Address: %s\r\n", WiFi.localIP().toString().c_str());
}

void setupSinricPro() {
  SinricProSwitch &bulbSwitch = SinricPro[device_ID_1];
  SinricProSwitch &fanSwitch = SinricPro[device_ID_2];

  bulbSwitch.onPowerState(onPowerState);
  fanSwitch.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(wifiLed, OUTPUT);
  digitalWrite(wifiLed, LOW);

  setupRelays();
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
