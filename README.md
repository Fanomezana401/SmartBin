# Hospital Information System (HIS) - Odoo ERP

**Authors:** Fanomezana Sarobidy Michelle RAZAFINDRAKOTO  & Elie Kokou Mokpokpo ETOVENA
**Supervised by:** Prof. Brahim BAKKAS 
**Academic Year:** 2025–2026  
**GitHub Repository:** [https://github.com/Fanomezana401/SmartBin](https://github.com/Fanomezana401/SmartBin)

# 🏙️ Smart City: IoT Intelligent Waste Management System

This project is part of a **Smart City** vision. It aims to optimize urban waste management through automation and remote monitoring using IoT technology.

## 📝 Project Overview
The system consists of two independent units working together:

1.  **Opening Unit (Arduino Uno):** Enables touchless interaction. The bin opens automatically when a presence is detected, improving hygiene and user experience.
2.  **Monitoring Unit (ESP32):** Connects the bin to the Cloud via **Blynk**. It measures the fill level in real-time to optimize collection routes and prevent overflows.

---

## 📂 File Structure

| File | Board | Primary Role |
| :--- | :--- | :--- |
| `sketch_dec24a_servo.ino` | **Arduino Uno** | Controls the servo motor and presence detection (Opening). |
| `sketch_dec24a.ino` | **ESP32** | WiFi connection, data transmission to Blynk (Fill level %). |

---

## 🛠️ Software Configuration (Arduino IDE)

### 1. For Arduino Uno (`sketch_dec24a_servo.ino`)
* **Board Type:** Tools > Board > Arduino AVR Boards > **Arduino Uno**.
* **Library:** No installation required (uses the built-in `Servo` library).
* **Port:** Select the COM port corresponding to your Arduino Uno.

### 2. For ESP32 (`sketch_dec24a.ino`)
* **Board Type:** Tools > Board > ESP32 Arduino > **ESP32 Dev Module**.
* **Required Libraries:** * `Blynk` (by Volodymyr Shymanskyy).
    * `WiFi` (built-in for ESP32).
* **Port:** Select the COM port corresponding to your ESP32.

---

## 🔐 Secrets Management (Security)

Replace YOUR_WIFI_NAME and YOUR_AUTH_TOKEN with the name of your wifi
Same with YOUR_AUTH_TOKEN

**`config.h` template:**
```cpp
// Blynk Settings
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_PROJECT_NAME"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

// WiFi Settings
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
Note: In the sketch_dec24a.ino file, ensure you include this file using #include "config.h" to keep your credentials private.

🔌 Hardware Pinout
Opening Unit (Arduino Uno)
Ultrasonic Sensor (HC-SR04): Trig -> Pin 9 | Echo -> Pin 10

Servo Motor: Signal -> Pin 6

Monitoring Unit (ESP32)
Ultrasonic Sensor (HC-SR04): Trig -> Pin 21 | Echo -> Pin 22

📱 Blynk App Configuration (Dashboard)
To visualize the data on your smartphone, configure the following widgets:

V0 (Gauge): Title "Fill Level", Range: 0-100.

V7 (Value Display): Title "Status", displays alerts such as "Bin Full!".
