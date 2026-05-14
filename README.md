# 🌱 BioStream Autonomous: Smart Irrigation System

![C++](https://img.shields.io/badge/C++-f34b7d?logo=c%2B%2B&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-F6822B?logo=platformio&logoColor=white)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulation-4CAF50?logo=microchip&logoColor=white)
<!-- ![OOP](https://img.shields.io/badge/Architecture-OOP_&_State_Machine-blue) -->

## 📖 About
**BioStream-Autonomous** is an intelligent, self-regulating irrigation control system built around the Arduino Nano. The system fuses data from multiple environmental sensors (soil moisture, temperature, and ambient light) to make autonomous decisions regarding when and how much to water plants.

Unlike traditional procedural Arduino scripts, this project is engineered using **Object-Oriented C++** and a non-blocking **State Machine**, ensuring high reliability, safety mechanisms (like flood prevention), and a responsive Human-Machine Interface (HMI). Development and testing were rigorously conducted using the Wokwi hardware simulator.

## 🛠 Tech Stack

### Software & Tooling
* **Language:** Modern C++ (Firmware)
* **Framework:** Arduino Core
* **Build System & IDE:** PlatformIO
* **Simulation:** Wokwi Simulator (via VS Code Plugin)

### Hardware & Electronics
* **Microcontroller:** Arduino Nano (ATmega328P)
* **Sensors:** Soil Moisture Sensor, LDR (Photoresistor), LM35 (Temperature Sensor)
* **Actuator:** 5V Relay Module (Controlling a DC Water Pump)
* **HMI:** 16x2 LCD (I2C) & 4x4 Matrix Keypad

## ✨ Technical Highlights & Features

### ⚙️ Advanced Firmware Architecture
* **Object-Oriented Design:** The codebase is heavily modularized into specific components (`SensorManager`, `IrrigationManager`, `InputManager`, `DisplayManager`, `TimeManager`).
* **Non-Blocking Logic:** Absolutely no `delay()` functions are used. The entire system relies on `millis()` based state machines, allowing concurrent sensor reading, LCD updates, and pump control without freezing the processor.

### 🛡️ Safety & Plant Health Mechanisms
* **Safety Timeout (Flood Protection):** The pump automatically shuts off after a predefined maximum execution time to prevent flooding in case of sensor failure.
* **Sunlight Restriction:** Prevents watering during direct, intense daylight to avoid water droplet magnification and leaf burn.
* **Heat Wave Adaptation:** Dynamically adjusts the moisture threshold if extreme temperatures are detected.

### 📟 Interactive Human-Machine Interface
* Real-time monitoring of system states, sensor values, and up-time via the I2C LCD.
* Matrix Keypad integration for manual overrides, system configuration, and safe manual pump activation.

## 🚀 Quick Start

### 1. Prerequisites
* [Visual Studio Code](https://code.visualstudio.com/)
* [PlatformIO IDE Extension](https://platformio.org/install/ide?install=vscode)
* [Wokwi Simulator Extension](https://wokwi.com/) (Optional, for running without physical hardware)

### 2. Clone the Repository
```bash
git clone https://github.com/OsherBerGit/BioStream-Autonomous-Irrigation-Control-Project.git
cd BioStream-Autonomous-Irrigation-Control-Project
```

### 3. Build & Run (PlatformIO)
Open the project folder in VS Code. PlatformIO will automatically download the required libraries (specified in platformio.ini).
* Click the Build button (✓) on the PlatformIO toolbar.
* Connect your Arduino Nano and click Upload (→).

### 4. Run in Simulation (Wokwi)
If you don't have the hardware, you can test the full logic in the browser or via VS Code:
#### 1. Open the diagram.json file.
#### 2. Start the Wokwi simulation. The system will boot, initialize the LCD, and start monitoring the virtual sensors.

### 📁 Project Structure
```
📦 BioStream-Autonomous
├── 📂 include/          # Global configurations (Constants.h)
 ├── 📂 lib/              # Object-Oriented Managers
 │   ├── 📂 DisplayManager/
 │   ├── 📂 InputManager/
 │   ├── 📂 IrrigationManager/
 │   ├── 📂 SensorManager/
 │   └── 📂 TimeManager/
 ├── 📂 src/              # Main application entry point (main.cpp)
 ├── 📜 diagram.json      # Wokwi circuit topology
 ├── 📜 platformio.ini    # Build configurations & Library dependencies
 └── 📜 wokwi.toml        # Wokwi project settings
```

---

Developed as a Final Engineering Project - Showcasing embedded C++ architecture, hardware-software integration, and robust system design.
