# 4-Bit Calculator Using STM32 Nucleo-64

This project implements a 4-bit calculator that can perform addition, subtraction, AND, and OR operations, built on the STM32 Nucleo-64 microcontroller. Designed for hands-on learning, this project introduces bit manipulation, basic arithmetic operations, and port interfacing in C.

## Overview

The 4-bit calculator operates based on user-selected operations and inputs:
- **Operation Selector**: Two bits select the operation type (AND, OR, ADD, or SUBTRACT).
- **Inputs**: 4-bit inputs (A and B).
- **Outputs**: Displays the result on a 7-segment display and 4 LEDs, with flags for carry, sign, zero, and overflow.

## Features

- **Operations**: 
  - **AND**: Performs bitwise AND between A and B.
  - **OR**: Performs bitwise OR between A and B.
  - **ADD**: Adds A and B.
  - **SUBTRACT**: Subtracts B from A, using complement logic if A < B.
- **Visual Output**:
  - **7-Segment Display**: Shows the result of the operation.
  - **LED Indicators**:
    - **4-Bit Output**: Binary result of the calculation.
    - **Flags**: Carry, sign, zero, and overflow indicators for each operation.

## Circuit Setup

### Hardware Connections

- **Output LEDs**:
  - **PA4-PA7**: Represents the 4-bit result, with PA7 as the most significant bit.
  - **Flag LEDs**: 
    - **PA8**: Carry flag.
    - **PA9**: Sign flag.
    - **PC10**: Zero flag.
    - **PC11**: Overflow flag.
- **7-Segment Display**: Connected to **PB0-PB7**.
- **Inputs**:
  - **PC0 and PC1**: Operation selectors.
  - **PC2-PC5**: 4-bit input A.
  - **PC6-PC9**: 4-bit input B.

#### Block Diagram

![Block Diagram]()

### Breadboard Wiring

- **7-Segment Display Wiring**:
  ![Breadboard 7-Segment Display]()
- **LED Output Wiring**:
  ![Breadboard LED Image]()
- **Nucleo Development Board Setup**:
  ![Dev Board]()

## Software Workflow

The main program reads user inputs (operation type, numbers A and B), performs the selected operation, and updates the display and flags accordingly. Here’s a breakdown of the software logic:

1. **Initialize Ports**: Configure GPIO ports for inputs and outputs.
2. **Read Inputs**: Continuously reads inputs for A, B, and the operation selector.
3. **Perform Operation**: Based on the selector value:
   - **AND (Selector = 0)**
   - **OR (Selector = 1)**
   - **ADD (Selector = 2)**:
     - Uses binary addition, with carry and overflow flags updated based on the result.
   - **SUBTRACT (Selector = 3)**:
     - If **A < B**, the program uses complement logic to handle negative results.
4. **Set Flags**:
   - **Carry**, **Sign**, **Zero**, and **Overflow** flags are updated based on the operation outcome.
5. **Output Result**:
   - **LEDs**: Display the 4-bit result.
   - **7-Segment Display**: Shows the calculated value.

#### Software Flowchart
![Flowchart]()

## Demonstration

This project provides a simple, visual calculator that demonstrates bitwise operations and basic arithmetic on a 4-bit scale. Each result is displayed in binary and on a 7-segment display, with flag indicators for error checking and sign representation.

## Example Usage

- **Operation Selector**:
  - Set using PC0 and PC1 pins.
- **Inputs A and B**:
  - Entered via PC2-PC5 for A and PC6-PC9 for B.
- **Result**:
  - Displayed in binary on LEDs and numerically on a 7-segment display.
- **Flag Indicators**:
  - Help diagnose carry, zero, overflow, and sign status.


## Video Demonstration

To see the 4-bit calculator in action, check out this video demonstration: [Project Video](https://youtu.be/6W3DWBqB28I)
