# 🔌 Smart Home Automation using ESP32 and Sinric Pro

This project demonstrates how to build a **Smart Home Automation system** using **ESP32**, **Sinric Pro**, **2-Channel Relay Module**, and optionally an **L298 Motor Driver** and **Transformer**. It allows voice and app-based control of home appliances like a **bulb** and **fan** via **Amazon Alexa**, **Google Assistant**, or the **Sinric Pro mobile app**.

---

## 🧰 Components Used

| Component              | Quantity | Description                                  |
|------------------------|----------|----------------------------------------------|
| ESP32 Dev Board        | 1        | WiFi-enabled microcontroller                 |
| 2-Channel Relay Module | 1        | For controlling Bulb and Fan                 |
| L298N Motor Driver     | 1        | (Optional) For driving motors (DC or Fan)    |
| Transformer (5V/12V)   | 1        | Power supply for ESP32 and Relay             |
| Bulb                   | 1        | Connected to Relay 1                         |
| Fan (AC/DC)            | 1        | Connected to Relay 2                         |
| LED (GPIO 2)           | 1        | WiFi Status Indicator                        |
| Jumper Wires           | -        | For connections                              |
| Breadboard / PCB       | 1        | For circuit assembly                         |

---

## ⚡ Wiring Diagram

| Device         | ESP32 GPIO | Notes                     |
|----------------|------------|---------------------------|
| Relay 1 (Bulb) | GPIO 23    | Active LOW (HIGH = OFF)   |
| Relay 2 (Fan)  | GPIO 22    | Active LOW (HIGH = OFF)   |
| WiFi LED       | GPIO 2     | Turns ON when connected   |
| L298N Motor IN | Optional   | Use GPIOs as needed       |
| Transformer    | VIN/5V     | Power ESP32/Relays safely |

> ⚠️ **Important:** Make sure the relay module supports 3.3V logic. Use a separate power source for relays and motors via a transformer if needed.

---

## 🔐 Sinric Pro Setup

1. Go to [https://portal.sinric.pro](https://portal.sinric.pro)
2. Create a free account and log in.
3. Create two "Switch" devices:
   - Name 1: Bulb
   - Name 2: Fan
4. Note their **Device IDs**, **App Key**, and **App Secret**.

Replace the placeholders in the code with your actual credentials:
```cpp
#define WIFI_SSID    "YourWiFiName"
#define WIFI_PASS    "YourWiFiPassword"
#define APP_KEY      "YourAppKey"
#define APP_SECRET   "YourAppSecret"
#define device_ID_1  "YourBulbDeviceID"
#define device_ID_2  "YourFanDeviceID"
```

---

## 🚀 Getting Started

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Install ESP32 Board Manager via Arduino preferences
3. Install the following libraries:
   - SinricPro
   - WiFi
4. Open and upload the code to your ESP32 board.
5. Connect relay channels to GPIO 23 (Bulb) and GPIO 22 (Fan).
6. Monitor output via Serial Monitor (9600 baud).

---

## 💡 Usage

- Control bulb and fan using:
  - Sinric Pro mobile app
  - Alexa voice commands (e.g., "Alexa, turn on the bulb")
  - Google Assistant (via Sinric integration)
- WiFi LED on GPIO 2 lights up on successful connection
- Relays are active LOW (energized = LOW)

---

## 🖥️ Sample Serial Output

```
[WiFi]: Connecting.....
[WiFi]: Connected! IP Address: 192.168.1.103
67dbf350bddfc53e33bc52b9: ON
67dbf380bddfc53e33bc5303: OFF
```

---

## 🧠 Optional L298 Motor Control

- To control DC motors or exhaust fans, use the L298N motor driver.
- Connect IN1/IN2 from L298 to spare GPIOs on ESP32.
- Extend the `onPowerState()` function to control L298 pins as needed.

---

## 🛡️ Safety Notes

- Ensure AC appliances are isolated and safely switched using relays.
- Use opto-isolated relays when dealing with 230V devices.
- Use a 5V transformer with regulated output to power ESP32 safely if not using USB.

---

## 📱 Voice Commands

- “Alexa, turn ON the Bulb”
- “Google, turn OFF the Fan”

---

## 📚 License

This project is released under the MIT License - feel free to use and modify it.

---
