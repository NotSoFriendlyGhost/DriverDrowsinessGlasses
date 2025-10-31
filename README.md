# 🕶 Driver Drowsiness Glasses

This repository contains the **source code and hardware design** for a wearable system — Driver Drowsiness Glasses — that helps drivers stay alert. Using IR‑sensors to detect eye closure and an LCD/buzzer alert system, the glasses prototype provides real‑time feedback to reduce fatigue‑related accidents.

---

## ℹ️ About

Driver fatigue is a major risk factor for road accidents. This project addresses that by combining biology (eye‑closure behavior) with embedded electronics to create a lightweight, wearable alert system. The Driver Drowsiness Glasses aim to improve safety by detecting early signs of fatigue and providing immediate feedback.

---

## ⚙️ Key Features

### 👁 Eye‑Closure Detection  
- Infrared (IR) sensors mounted on the glasses frame monitor the driver’s eyes and detect prolonged closure.  
- Alerts are triggered when the system senses fatigue‑related patterns.

### 🔊 Multi‑Modal Alerting  
- Buzzer and LCD display notify the driver when eye‑closure is detected.  
- The system logs events and remains passively monitoring while the vehicle is in motion.

### 🧠 Biologically‑Informed Design  
- Uses physiological traits: blinking frequency, eye‑closure duration, reaction time reductions under fatigue.  
- Wearable form factor: unobtrusive for real‑world use.

---

## 🛠 Tech Stack

| Component        | Details                                  |
|------------------|------------------------------------------|
| **Platform**     | Arduino (Uno/Nano)                       |
| **Sensors**      | Infrared obstacle avoidance sensors      |
| **Output Devices** | Buzzer, 16×2 LCD (or OLED)             |
| **Development**  | PlatformIO + Visual Studio Code          |
| **Hardware**     | Glasses frame, breadboard / prototype    |

---

## 🧠 How It Works

1. The IR sensors detect when the eyes are closed for a predefined threshold.  
2. On detection of prolonged closure, the buzzer sounds and the LCD displays a warning.  
3. The system continues monitoring and logs any such events for future analysis.  
4. Calibration is required to adjust sensitivity for different users (eye shape, set, blink behavior).

---

## 📁 Repository Structure

```text
DriverDrowsinessGlasses/
├── hardware/                    # Schematics, wiring diagrams, PCB layouts
├── firmware/                    # Arduino code and libraries
├── documentation/               # Project proposal, budget, logs
├── tests/                       # Sensor calibration and reliability tests
└── README.md                    # Project overview
