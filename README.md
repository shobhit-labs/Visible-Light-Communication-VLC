# Visible Light Communication (VLC) Receiver & Morse Decoder

This repository contains the firmware for an **Arduino-based Visible Light Communication (VLC)** receiver system. The system samples analog light signals via a photo-sensor circuit, processes the timing dynamically, and decodes incoming Morse code data into clear text displayed in real-time on a 16x2 LCD character display.

## 🛠️ Features & Functionality
- **Dynamic Signal Sampling:** Reads analog inputs from an LDR/photodiode circuit to capture light pulses.
- **Adaptive Pulse Processing:** Uses precise timing logic (`millis()`) to differentiate between Dots (~200ms) and Dashes (~600ms) without blocking the processor.
- **Embedded Morse Dictionary:** Decodes complete alphabetical strings and includes space handling for full words.
- **Dual-Line LCD Interfacing:** Automatically manages text wraps to display long decoded strings smoothly across a 16x2 layout.

## 💻 Hardware Components Used
- **Microcontroller:** Arduino UNO
- **Receiver Sensor:** Light Dependent Resistor (LDR) / Photodiode circuit
- **Display Module:** 16x2 LCD Character Display
- **Signal Source:** Flashlight / Laser Pointer modulated via a mobile transmitter application

## 🔌 Pin Configuration
| Component | Arduino Pin | Description |
| **LDR Sensor** | `A1` | Analog Input for Light Intensity |
| **LCD RS** | `12` | Register Select |
| **LCD Enable** | `11` | Enable Pulse |
| **LCD D4 - D7** | `5, 4, 3, 2` | 4-bit Data Lines |

## ⚙️ How It Works
1. The hardware receiver is exposed to a modulated light source (e.g., a phone flashlight app transmitting Morse code).
2. When light crosses the pre-defined `threshold`, the timer begins tracking the pulse length.
3. Once the light pulse ends, the firmware calculates the duration to identify whether a `.` or `-` was received.
4. A character gap trigger (>800ms) initiates the dictionary lookup, converting the Morse string to a character and rendering it instantly onto the LCD and Serial Monitor.
