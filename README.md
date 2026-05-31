# pic18-uart-communication
Embedded C implementation of UART serial communication using a PIC18F microcontroller. Configured baud rates, transmit/receive registers, and interrupt routines via MPLAB X. Verified using Proteus simulations to demonstrate robust asynchronous data transfer protocols.
# PIC18 Microcontroller UART Serial Communication

A low-level embedded firmware application implementing asynchronous serial data transmission (UART/RS-232) using a PIC18 microcontroller. Designed and compiled in **MPLAB X IDE** with the **XC8 compiler**, and structurally verified via **Proteus Design Suite**.

---

## 🚀 Project Overview

This project establishes full-duplex asynchronous serial communication between the PIC18 microcontroller and a peripheral terminal. The firmware configures internal hardware registers to manage data frame generation, transmission polling, and error checking without relying on abstract Arduino-style libraries.

### Key Technical Features
* **Register-Level Programming:** Direct manipulation of PIC18 hardware registers for peripheral control.
* **Baud Rate Optimization:** Precise calculation of timing registers to minimize transmission bit-error rates.
* **Full-Duplex I/O:** Independent, simultaneous data transmission (`TX`) and reception (`RX`) pipelines.

---

## 🛠️ Hardware & Software Stack

* **Microcontroller:** PIC18F series (e.g., PIC18F65K90 / PIC18F4520)
* **Development IDE:** MPLAB X IDE
* **Compiler:** Microchip XC8
* **Simulation Tool:** Proteus Design Suite (Virtual Terminal component)
* **Protocol:** UART (8-bit data, no parity, 1 stop bit)

---

## ⚙️ Hardware Register Configuration

Achieving stable asynchronous transmission requires precise initialization of the microcontroller's internal SFRs (Special Function Registers). The core architecture is managed through:

1. **`TXSTA` (Transmit Status and Control Register):**
   * Configures high/low baud rate speed mode (`BRGH`).
   * Enables 8-bit asynchronous transmission (`TX9 = 0`, `SYNC = 0`, `TXEN = 1`).
2. **`RCSTA` (Receive Status and Control Register):**
   * Enables the serial port and continuous data reception (`SPEN = 1`, `CREN = 1`).
3. **`SPBRG` / `SPBRGH` (Baud Rate Generator):**
   * Loaded with calculated integer values based on the target Fosc (Oscillator Frequency) to lock in the standard baud rate (e.g., 9600 bps).

---

## 📁 Repository Structure

```text
├── src/                    # Firmware codebase
│   ├── main.c              # Application loop and core routine
│   ├── uart.c              # Driver functions (UART_Init, UART_Write, UART_Read)
│   └── uart.h              # Register macros and function prototypes
├── simulation/             # Schematic layouts
│   └── pic18_uart_sim.pdsprj # Proteus workspace project file
└── README.md               # Documentation
