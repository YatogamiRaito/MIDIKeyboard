# Wiring Guide - Arduino MIDI Keyboard

This document provides detailed wiring instructions for building the Arduino MIDI Keyboard with a resistor matrix.

## Table of Contents

- [Overview](#overview)
- [Components Required](#components-required)
- [Resistor Matrix Theory](#resistor-matrix-theory)
- [Step-by-Step Wiring](#step-by-step-wiring)
- [Resistor Value Calculation](#resistor-value-calculation)
- [Testing and Calibration](#testing-and-calibration)
- [Common Issues](#common-issues)

## Overview

The MIDI keyboard uses a **resistor matrix** to detect which key is pressed. This method allows multiple keys to be read using only 4 analog inputs, rather than requiring 32 digital pins.

### How It Works

1. The Arduino scans through each column (pins 2-9) by setting it HIGH
2. When a key is pressed, it connects a column to a row through a unique resistor
3. The analog input reads a voltage determined by the resistor value
4. The Arduino determines which key was pressed based on the analog reading

## Components Required

### Essential Components

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Leonardo or Micro | 1 | Must have native USB support |
| Momentary Push Buttons | 32 | Any normally-open tactile switches |
| Resistors (various values) | 32 | See resistor values below |
| Breadboard or PCB | 1 | For prototyping |
| Jumper Wires | ~20 | Male-to-male for breadboard |
| USB Cable | 1 | Type-B or Micro-USB depending on board |

### Optional Components

| Component | Purpose |
|-----------|---------|
| Diodes (1N4148) | Prevent ghosting in matrix |
| Capacitors (0.1µF) | Reduce electrical noise |
| Enclosure | Professional-looking case |
| Key caps | Better feel and appearance |

## Resistor Matrix Theory

### Why Use Different Resistors?

Each key needs a unique analog value so the Arduino can identify it. We achieve this by using different resistor values for each position in a row.

### Example Resistor Values

For a 4x8 matrix, you need **8 different resistor values** (one value for each column):

| Column | Resistor Value | Example Values |
|--------|----------------|----------------|
| Col 0 | R1 | 100Ω |
| Col 1 | R2 | 220Ω |
| Col 2 | R3 | 470Ω |
| Col 3 | R4 | 1kΩ |
| Col 4 | R5 | 2.2kΩ |
| Col 5 | R6 | 4.7kΩ |
| Col 6 | R7 | 10kΩ |
| Col 7 | R8 | 22kΩ |

**Important:** All keys in the same column use the **same resistor value**.

### Circuit Diagram for One Key

```
Arduino Digital Pin (Column)
      |
      |
   [Button]
      |
      |
  [Resistor]
      |
      |
Arduino Analog Pin (Row)
```

### Voltage Divider Principle

When a button is pressed:
```
5V ---- [Button] ---- [Resistor] ---- Analog Pin ---- GND (through Arduino input impedance)
```

The analog pin reads a voltage determined by the resistor value. Different resistors = different voltages = unique key identification.

## Step-by-Step Wiring

### Step 1: Prepare Your Components

1. Identify your resistor values using a multimeter or color codes
2. Sort resistors by value (8 piles, one for each column)
3. Label your buttons if they're not already in an array

### Step 2: Wire the Columns (Digital Pins)

For each column (0-7):

1. Connect digital pin 2 to one terminal of buttons 1, 9, 17, 25
2. Connect digital pin 3 to one terminal of buttons 2, 10, 18, 26
3. Connect digital pin 4 to one terminal of buttons 3, 11, 19, 27
4. Connect digital pin 5 to one terminal of buttons 4, 12, 20, 28
5. Connect digital pin 6 to one terminal of buttons 5, 13, 21, 29
6. Connect digital pin 7 to one terminal of buttons 6, 14, 22, 30
7. Connect digital pin 8 to one terminal of buttons 7, 15, 23, 31
8. Connect digital pin 9 to one terminal of buttons 8, 16, 24, 32

**Visualization:**
```
D2 ---- Button[0,0] ---- Button[1,0] ---- Button[2,0] ---- Button[3,0]
D3 ---- Button[0,1] ---- Button[1,1] ---- Button[2,1] ---- Button[3,1]
... (and so on)
```

### Step 3: Add Resistors to Each Button

For each button, connect a resistor between the button's second terminal and the row wire:

**Column 0 buttons (1, 9, 17, 25):** Use R1 (100Ω)
**Column 1 buttons (2, 10, 18, 26):** Use R2 (220Ω)
**Column 2 buttons (3, 11, 19, 27):** Use R3 (470Ω)
... and so on

### Step 4: Wire the Rows (Analog Pins)

Connect all resistors from the same row to the corresponding analog pin:

1. **Row 0** (buttons 1-8): Connect all resistors to pin A0
2. **Row 1** (buttons 9-16): Connect all resistors to pin A1
3. **Row 2** (buttons 17-24): Connect all resistors to pin A2
4. **Row 3** (buttons 25-32): Connect all resistors to pin A3

**Visualization for Row 0:**
```
A0 ---- [R1] ---- Button1
    |
    +-- [R2] ---- Button2
    |
    +-- [R3] ---- Button3
    |
    ... (all 8 buttons in row 0)
```

### Step 5: Complete Connection Table

Here's the complete wiring for all 32 keys:

| Key # | Row | Col | Digital Pin | Analog Pin | Resistor |
|-------|-----|-----|-------------|------------|----------|
| 1 | 0 | 0 | D2 | A0 | R1 (100Ω) |
| 2 | 0 | 1 | D3 | A0 | R2 (220Ω) |
| 3 | 0 | 2 | D4 | A0 | R3 (470Ω) |
| 4 | 0 | 3 | D5 | A0 | R4 (1kΩ) |
| 5 | 0 | 4 | D6 | A0 | R5 (2.2kΩ) |
| 6 | 0 | 5 | D7 | A0 | R6 (4.7kΩ) |
| 7 | 0 | 6 | D8 | A0 | R7 (10kΩ) |
| 8 | 0 | 7 | D9 | A0 | R8 (22kΩ) |
| 9 | 1 | 0 | D2 | A1 | R1 (100Ω) |
| 10 | 1 | 1 | D3 | A1 | R2 (220Ω) |
| ... | ... | ... | ... | ... | ... |
| 32 | 3 | 7 | D9 | A3 | R8 (22kΩ) |

## Resistor Value Calculation

### Method 1: Use Standard Values

The easiest method is to use common resistor values with good separation:

```
100Ω, 220Ω, 470Ω, 1kΩ, 2.2kΩ, 4.7kΩ, 10kΩ, 22kΩ
```

These are **E12 series** values, widely available and provide enough separation for reliable detection.

### Method 2: Calculate Custom Values

If you want to calculate your own values:

1. Choose a minimum resistor (e.g., 100Ω)
2. Choose a maximum resistor (e.g., 47kΩ)
3. Calculate 8 logarithmically-spaced values between them

**Formula:**
```
R(n) = R_min * (R_max/R_min)^(n/7)
where n = 0, 1, 2, ... 7
```

### Analog Reading Expectations

With 5V Arduino and the suggested resistor values, expect these approximate analog readings:

| Resistor | Approx. Analog Value | Digital Reading (0-1023) |
|----------|---------------------|--------------------------|
| 100Ω | ~0.5V | ~100 |
| 220Ω | ~1.0V | ~200 |
| 470Ω | ~1.8V | ~350 |
| 1kΩ | ~2.5V | ~500 |
| 2.2kΩ | ~3.2V | ~650 |
| 4.7kΩ | ~3.8V | ~780 |
| 10kΩ | ~4.2V | ~860 |
| 22kΩ | ~4.6V | ~940 |

## Testing and Calibration

### Step 1: Test Without Buttons

Upload this test sketch to see raw analog readings:

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  Serial.print("A0: "); Serial.print(analogRead(A0));
  Serial.print(" A1: "); Serial.print(analogRead(A1));
  Serial.print(" A2: "); Serial.print(analogRead(A2));
  Serial.print(" A3: "); Serial.println(analogRead(A3));
  delay(500);
}
```

**Expected:** All values should be ~1023 (no buttons pressed)

### Step 2: Test Each Column

For each column (D2-D9):

1. Set the digital pin HIGH
2. Press each button in that column
3. Note the analog reading
4. Verify readings are consistent and distinct

### Step 3: Adjust Thresholds

Based on your readings, adjust these constants in the main sketch:

```cpp
const int NO_PRESS_THRESHOLD = 1000;  // Adjust if needed
const int PRESS_THRESHOLD = 87;        // Set to lowest reading - 20
```

### Step 4: Test MIDI Output

1. Upload the main sketch
2. Connect to MIDI monitoring software
3. Press each key and verify correct MIDI notes

## Common Issues

### Issue 1: Inconsistent Readings

**Symptoms:** Analog values jump around when button is pressed

**Solutions:**
- Add 0.1µF capacitor between analog pin and GND
- Use shielded wire for analog connections
- Move away from noise sources (motors, AC power)

### Issue 2: Multiple Keys Trigger Simultaneously (Ghosting)

**Symptoms:** Pressing one key triggers another key

**Solutions:**
- Add diode (1N4148) in series with each button
  ```
  Digital Pin ----[Diode]----[Button]----[Resistor]---- Analog Pin
  ```
- Use diode with cathode (stripe) toward the button

### Issue 3: Keys Not Detected

**Symptoms:** Some keys don't register

**Checklist:**
- Verify button is working (test with multimeter)
- Check all solder joints
- Verify correct resistor value
- Check for loose wires
- Adjust `PRESS_THRESHOLD` in code

### Issue 4: Wrong Notes Playing

**Symptoms:** Key presses produce unexpected MIDI notes

**Solutions:**
- Verify wiring matches the pin assignments in code
- Check MIDI note mapping in `getMidiNote()` function
- Ensure `STARTING_MIDI_NOTE` is set correctly

### Issue 5: Delayed Response

**Symptoms:** Noticeable lag between key press and MIDI note

**Solutions:**
- Reduce `SCAN_DELAY_MICROSECONDS` (try 50 or even 10)
- Ensure USB cable is working properly
- Close other applications that might use CPU

## Advanced: Adding Diodes

To completely prevent ghosting, add a diode to each key:

```
Digital Pin ----[1N4148 Diode]----[Button]----[Resistor]---- Analog Pin
                  (stripe →)
```

The diode ensures current can only flow in one direction, preventing false key detection.

## Breadboard Layout Tips

1. **Use color coding:**
   - Red wires for digital pins (columns)
   - Black wires for analog pins (rows)
   - Colored resistors sorted by value

2. **Organize in rows:**
   - Keep all row 0 components together
   - Label each row clearly

3. **Test incrementally:**
   - Wire one row at a time
   - Test before moving to next row

## PCB Design Considerations

If you want to make a PCB:

1. **Trace width:** Use at least 0.5mm traces for signals
2. **Ground plane:** Add a ground plane for noise reduction
3. **Mounting holes:** Include holes for securing buttons
4. **Silkscreen:** Label all components clearly
5. **Test points:** Add test points for analog pins

## Resources

- [Resistor Color Code Calculator](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code)
- [Arduino Analog Input Tutorial](https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput)
- [Matrix Keyboard Theory](https://www.baldengineer.com/arduino-keyboard-matrix-tutorial.html)

## Questions?

If you encounter issues not covered here, please open an issue on GitHub with:
- Photos of your wiring
- Serial monitor output showing analog readings
- Description of the problem

---

**Good luck with your build! 🎹**
