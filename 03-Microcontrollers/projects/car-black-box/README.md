# Car Black Box

Embedded firmware for a PIC18F4580 that records vehicle events (gear changes, collision) with a timestamp and speed, similar to a car's black box.

> Developed as part of the Emertxe training program.

## Features
- Logs events with time and speed: ON, GN (neutral), GR (reverse), G1 to G5, and C (collision)
- Event records stored in external EEPROM (14 bytes per event)
- Real-time clock (DS1307) over I2C for timestamps
- Vehicle speed read through the ADC
- 16x2 CLCD display with a matrix keypad
- Password-protected menu with limited attempts; the password is stored in EEPROM
- Menu options: view log, clear log, download log over UART, set time, change password

## Hardware and Tools
- PIC18F4580 microcontroller
- 16x2 CLCD, matrix keypad, DS1307 RTC, external EEPROM, potentiometer (speed)
- MPLAB XC8 compiler (v1.36 used in the Makefile)

## Project Structure

    car-black-box/
    - main.c / main.h
    - clcd.c / .h            character LCD driver
    - matrix_keypad.c / .h   keypad driver
    - ds_1307.c / .h         RTC driver
    - i2c.c / .h             I2C driver
    - adc.c / .h             ADC for speed
    - timer0.c / .h
    - exter.c / .h           external interrupt
    - isr.c / .h             interrupt service routine
    - uart.c / .h
    - Makefile

## Build
The Makefile targets the XC8 compiler and the tinybldlin bootloader. This needs the Microchip toolchain and the board, so it can't be built on a normal PC.

    make          builds pic18F4580.hex
    make burn     flashes using tinybldlin

Adjust INCLUDE_PATH, PROG and PORT in the Makefile for your setup.

## What I Learned
- Writing peripheral drivers: I2C, ADC, UART, timers, interrupts
- Interfacing an RTC, LCD, keypad and external memory
- Structuring embedded C into separate driver modules

## Author
Rohith T A
