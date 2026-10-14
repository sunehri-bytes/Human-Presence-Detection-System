# Human Presence Detection CanSat

An ESP32-based human presence detection prototype designed to help identify the presence of a person in a monitored area and communicate the detection status wirelessly to a remote display.

## 📌 About the Project

The **Human Presence Detection CanSat** project explores how sensors, microcontrollers, and wireless communication can work together to detect human presence and display the result at a separate receiver unit.

The system is built around two main units: a **transmitter** and a **receiver**. The transmitter reads data from a human-presence sensing module connected to an ESP32 and sends detection-status messages using an nRF24L01 wireless communication module. The receiver uses another ESP32 to receive these messages and display the current status on an OLED screen.

The project is a stationary prototype intended to demonstrate remote human-presence monitoring. Despite the CanSat-inspired project name, this version is designed for room-based testing rather than flight.

## 🎯 Objectives

* Detect possible human presence using a sensing module.
* Process sensor data using an ESP32 microcontroller.
* Transmit detection status wirelessly between two units.
* Display the received status on an OLED screen.
* Explore the integration of embedded systems, sensors, and wireless communication.

## ⚙️ Hardware Components

* **ESP32 development boards:** Control the transmitter and receiver units.
* **Human-presence sensor (C1001):** Supplies sensor data to the transmitter.
* **nRF24L01 wireless modules:** Provide communication between the two units.
* **0.96-inch OLED display (SSD1306, 128 × 64):** Displays the received detection status.
* **Buzzer:** Intended to provide an audible alert when human presence is detected.
* **Connecting wires and supporting components:** Used to connect and power the circuit.

*Note: The buzzer pin configuration and operation should be verified against the final working circuit and code.*

## 🧠 How It Works

1. **Sensing:** The human-presence sensor supplies data to the transmitter ESP32.
2. **Processing:** The transmitter code updates the human-detection status based on the incoming sensor data.
3. **Wireless transmission:** The nRF24L01 module sends a status message to the receiver. The current code uses `H` for human detected and `N` for no human detected.
4. **Message reception:** The receiver ESP32 listens for incoming wireless messages.
5. **Display:** The OLED displays either `HUMAN DETECTED` or `NO HUMAN`, depending on the received message.
6. **Alert:** A buzzer alert is intended to accompany human detection, subject to the correct pin configuration.

## 🏗️ System Architecture

**Sensor → Transmitter ESP32 → nRF24L01 Wireless Link → Receiver ESP32 → OLED Display**

The system separates sensing from displaying the result, allowing the detection status to be viewed at a different location within the tested communication range.

## 💻 Software and Technologies

* **Arduino IDE / Arduino-compatible environment**
* **C++ (Arduino programming)**
* **ESP32**
* **RF24 library** for nRF24L01 communication
* **Adafruit GFX Library** for graphics support
* **Adafruit SSD1306 Library** for OLED display control
* **SPI and I²C communication interfaces**

## 📁 Repository Structure

```text
human-presence-detection-cansat/
├── transmitter/
│   └── transmitter.ino
├── receiver/
│   └── receiver.ino
├── README.md
└── .gitignore
```

* `transmitter/transmitter.ino` contains the transmitter-side code.
* `receiver/receiver.ino` contains the receiver-side code.
* `README.md` describes the project and its working.
* `.gitignore` lists files that Git should ignore.

## 🚀 Setup and Usage

1. Install the Arduino IDE or another compatible Arduino development environment.
2. Install the required ESP32 board support package.
3. Install the RF24, Adafruit GFX, and Adafruit SSD1306 libraries.
4. Connect the transmitter circuit according to the project's wiring configuration.
5. Open `transmitter/transmitter.ino`, select the correct ESP32 board and port, and upload the code.
6. Connect the receiver circuit, including the OLED display.
7. Open `receiver/receiver.ino`, select the correct board and port, and upload the code.
8. Power both units and monitor the Serial Monitor and OLED display while testing.

**Important:** Verify the wiring, sensor data format, buzzer pin configuration, and library compatibility before running the system. The code in this repository is a starting point and should be tested with the actual hardware.

## 🔬 Testing and Future Improvements

Possible future improvements include:

* Improving sensor-data parsing and detection reliability.
* Adding a communication timeout so the receiver can identify when messages stop arriving.
* Improving wireless communication reliability and testing the usable range.
* Adding timestamps and a clearer status interface.
* Synchronising the OLED display with a local web dashboard.
* Testing the system under different room conditions.

## ⚠️ Limitations

This project is an educational prototype. Its detection accuracy, wireless range, and reliability depend on the sensor, circuit, environment, and software implementation. It has not been established as a certified search-and-rescue device and should not be relied upon for emergency or life-safety decisions.

## 👥 Contributors

Developed as a student group project.

Add the names and GitHub profiles of the contributing team members here, with their permission.

## 📄 License

A license has not yet been selected. Until a license is added, do not assume that others have permission to reuse, modify, or redistribute the code.
