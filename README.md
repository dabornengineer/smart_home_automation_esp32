# 🏠 Smart Home Automation with ESP32

This is an ESP32-based Smart Home Automation project developed with PlatformIO. It uses a combination of sensors to automate home appliances based on environmental conditions and motion detection.

---

## 🔧 Features

- 📡 **PIR Motion Sensor**: Detects human presence and triggers lights or alarms.
- 🌞 **LDR (Light-Dependent Resistor)**: Measures ambient light to automatically control lighting.
- 🌡️ **DHT11/DHT22 Sensor**: Monitors room temperature and humidity for smart climate control.
- 🌐 **ESP32 Microcontroller**: Wi-Fi enabled, used to control devices and transmit data.
- ⚙️ **PlatformIO Development Environment**: Modular and scalable development setup.

---

## 🛠 Hardware Used

| Component              | Quantity | Purpose                                  |
|------------------------|----------|------------------------------------------|
| ESP32 Dev Board        | 1        | Main microcontroller with Wi-Fi          |
| PIR Motion Sensor      | 1        | Detects human movement                   |
| LDR + 10k Resistor     | 1        | Detects brightness/light intensity       |
| DHT11 or DHT22 Sensor  | 1        | Measures temperature and humidity        |
| Relay Module (Optional)| 1+       | Controls AC appliances (fan, bulb, etc.) |
| Breadboard + Jumpers   | -        | Prototyping                              |

---

## 📐 Circuit Diagram

📌 _Will be added soon (Fritzing or schematic diagram)_

---

## 💻 How It Works

- **Motion Detected (PIR)**: Turns on lights or alerts when human movement is detected.
- **Low Light (LDR)**: Automatically turns on a bulb or LED when it gets dark.
- **Temperature/Humidity (DHT)**: Controls fans or alerts when temperature/humidity thresholds are crossed.

---

## 🧪 Project Goals

- Automate home appliances intelligently.
- Reduce energy usage by detecting ambient conditions.
- Create a solid base for scalable IoT applications.
