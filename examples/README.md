# Examples

This directory contains example sketches to help you test, calibrate, and understand your Arduino MIDI Keyboard.

## Available Examples

### 1. AnalogReadingTest

**Purpose:** Test and calibrate your resistor matrix

**What it does:**
- Displays real-time analog readings from all row pins
- Shows values for each key position in the matrix
- Helps you identify the correct threshold values

**When to use:**
- First time setup
- Verifying wiring is correct
- Calibrating PRESS_THRESHOLD and NO_PRESS_THRESHOLD
- Troubleshooting key detection issues

**Instructions:**
1. Upload `AnalogReadingTest.ino`
2. Open Serial Monitor (9600 baud)
3. Observe readings with no keys pressed (should be ~1023)
4. Press each key individually and note the value
5. Use these values to set thresholds in `config.h`

**Example output:**
```
[Row 0]  1023 1023  450 1023 1023 1023 1023 1023
[Row 1]  1023 1023 1023 1023 1023 1023 1023 1023
[Row 2]  1023 1023 1023 1023 1023 1023 1023 1023
[Row 3]  1023 1023 1023 1023 1023 1023 1023 1023
```
(In this example, key at Row 0, Col 2 is pressed with value 450)

---

### 2. SimpleButtonTest

**Purpose:** Test button functionality without MIDI

**What it does:**
- Detects when keys are pressed and released
- Displays key positions and analog values
- No MIDI functionality (simpler for debugging)

**When to use:**
- Testing if buttons are working mechanically
- Verifying the matrix scanning logic
- Debugging without MIDI complications
- Learning how the code detects key presses

**Instructions:**
1. Upload `SimpleButtonTest.ino`
2. Open Serial Monitor (9600 baud)
3. Press and release keys
4. Verify all keys are detected correctly

**Example output:**
```
Key [0,5] PRESSED (value: 780)
Key [2,3] PRESSED (value: 500)
Key [0,5] RELEASED
Key [2,3] RELEASED
```

---

### 3. MIDIMonitor

**Purpose:** Monitor MIDI messages while testing

**What it does:**
- Sends MIDI messages via USB (like the main sketch)
- Also prints MIDI messages to Serial Monitor
- Shows note names, numbers, and velocity

**When to use:**
- Verifying correct MIDI notes are sent
- Checking MIDI channel and velocity settings
- Ensuring note on/off messages are paired correctly
- Learning the MIDI note mapping

**Instructions:**
1. Upload `MIDIMonitor.ino`
2. Open Serial Monitor (9600 baud)
3. Also open your DAW or MIDI software
4. Press keys and verify MIDI output

**Example output:**
```
NOTE ON:  Ch 1 | Note 65 (F4) | Vel 127
NOTE OFF: Ch 1 | Note 65 (F4) | Vel 127
NOTE ON:  Ch 1 | Note 72 (C5) | Vel 127
```

---

## Testing Workflow

Follow this recommended order when setting up your keyboard:

### Step 1: Verify Wiring
Use **AnalogReadingTest** to:
- Check all connections are correct
- Verify each key produces a unique analog value
- Ensure no keys are shorted or disconnected

### Step 2: Test Buttons
Use **SimpleButtonTest** to:
- Confirm all buttons work mechanically
- Verify the scanning algorithm detects all keys
- Check for any ghosting or false triggers

### Step 3: Calibrate Thresholds
Based on readings from Step 1:
- Set `PRESS_THRESHOLD` to lowest reading - 20
- Set `NO_PRESS_THRESHOLD` to ~1000
- Update these values in `config.h`

### Step 4: Test MIDI
Use **MIDIMonitor** to:
- Verify MIDI messages are sent correctly
- Check note numbers match your expectations
- Ensure all keys produce MIDI output
- Confirm no stuck notes or missing note-offs

### Step 5: Upload Main Sketch
Once everything is working:
- Upload the main `ArduinoMIDIKeyboard.ino`
- Connect to your DAW
- Start making music!

---

## Common Issues and Solutions

### Issue: All readings show 1023

**Cause:** Buttons not pressed, or wiring issue

**Solution:**
- Verify column pins are connected correctly
- Check buttons are working mechanically
- Try pressing buttons firmly

### Issue: Erratic or unstable readings

**Cause:** Electrical noise or bad connections

**Solution:**
- Check all solder joints (if using PCB)
- Add 0.1µF capacitors between analog pins and GND
- Use shielded wires for analog connections
- Move away from noise sources

### Issue: Multiple keys trigger at once

**Cause:** Ghosting in matrix, or threshold too low

**Solution:**
- Increase `PRESS_THRESHOLD` value
- Add diodes to each key (see docs/WIRING.md)
- Verify resistor values are correct

### Issue: Some keys don't trigger

**Cause:** Threshold too high, or wiring issue

**Solution:**
- Decrease `PRESS_THRESHOLD` value
- Check wiring for those specific keys
- Verify resistors are correct values
- Test buttons mechanically

### Issue: Keys work in test but not in main sketch

**Cause:** Configuration mismatch

**Solution:**
- Ensure pin assignments match in all sketches
- Verify threshold values are the same
- Check MIDI library is installed correctly

---

## Customizing Examples

Feel free to modify these examples for your needs:

### Adding Debug Output

Add more detailed output to any example:

```cpp
Serial.print("Row: ");
Serial.print(row);
Serial.print(" Col: ");
Serial.print(col);
Serial.print(" Value: ");
Serial.println(value);
```

### Changing Update Rate

Adjust the delay at the end of `loop()`:

```cpp
delay(100);  // Update every 100ms instead of 500ms
```

### Testing Specific Keys

Focus on a subset of keys:

```cpp
// Only test row 0
for (int col = 0; col < NUM_COLS; col++) {
  int value = analogRead(A0);
  // ... process value
}
```

---

## Creating Your Own Examples

To create a new example:

1. Create a new folder: `examples/YourExampleName/`
2. Create sketch file: `examples/YourExampleName/YourExampleName.ino`
3. Add comments explaining what it does
4. Test thoroughly
5. (Optional) Submit a pull request to share with others!

---

## Need Help?

- Check the main [README.md](../README.md) for hardware setup
- See [docs/WIRING.md](../docs/WIRING.md) for wiring details
- Open an issue on GitHub if you're stuck

**Happy testing! 🎹**
