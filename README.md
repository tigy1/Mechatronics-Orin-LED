# Orin Robosub LED Mode Indicator

This repository contains the firmware and host-side interface for controlling a WS2812 LED strip via an STM32 microcontroller over UART. The LEDs are used to indicate the **current operational mode** of the Orin Robosub, a student-built autonomous underwater vehicle.

Modes are communicated via UART from a Python script running on the host system and translated into LED color patterns by the STM32 firmware.

---

## Purpose

LEDs provide **immediate visual feedback** on Orin’s state. This is crucial during pool testing, debugging, or when operating the sub remotely. Modes are mapped to colors, enabling surface crew to distinguish between autonomous navigation, manual override, kill switch activation, and other states.

---

## Architecture Overview

### Hardware Components

- **Microcontroller**: STM32 (e.g., STM32F103 or similar)
- **LED Strip**: WS2812B addressable RGB strip
- **Communication**: UART @ 115200 baud between host and STM32
- **Power Supply**: Regulated 5V for LED strip

### Firmware Features (`main.c`)

- Configures **TIM2 PWM with DMA** for LED signal generation
- Parses RGB input strings over UART
- Allows **real-time LED updates** from Python terminal input
- Implements **chasing animation** based on current mode color
- Brightness control via `tan()` mapping for perceived brightness tuning

### Python Host Interface (`led_script.py`)

- Validates and sends RGB values to STM32 over UART
- Command-line interface prompts for interactive control
- Cross-platform support with adjustable serial port

---

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/tigy1/Mechatronics-Orin-LED.git
cd Mechatronics-Orin-LED
```

### Build and Flash Firmware

- Use **STM32CubeIDE** or compatible toolchain
- Connect your board via ST-Link or UART bootloader
- Ensure `NUMBER_OF_LEDS` is configured correctly in `main.c`
- Flash `main.c` and its dependencies (`led.c`, `led.h`) to your board

### Install Python Dependencies

No external libraries beyond `pyserial` are required:

```bash
pip install pyserial
```

---

##  Using the Control Script

Run the Python control interface:

```bash
python3 led_script.py
```

You will be prompted to enter RGB values in the format:

```
### ### ### where each chain of hashtags represents a number 001 - 255 (0s are important) as a decimal representation of RGB values.

To disable LED output via DMA, send: `001 000 000`
```

The script will validate input and send it via UART to the STM32 board.

*Adjust `port` and `baudrate` if needed inside `led_script.py`.*

---

## 🧩 Code Highlights

### UART Packet Format

The STM32 expects newline-terminated ASCII RGB strings over UART:

```
"255 000 000\n"
```

Parsed using `sscanf` in `HAL_UART_RxCpltCallback()`.

### LED Color and Brightness Encoding

Color bits are stored as bitwise-shifted PWM values in structs:

```c
typedef struct {
  uint16_t r[8], g[8], b[8];
} led;
```

Brightness mapping uses `tan(angle)` to provide nonlinear control.

### DMA Timing

Each LED gets 24 bits; additional 2 LEDs are padded to ensure reset timing:

```c
NUMBER_OF_LEDS * 24 + 2 * 24
```

---
