# Arduino MIDI Keyboard

A fully-featured MIDI keyboard controller built with Arduino, using a resistor matrix to detect key presses and send MIDI notes via USB.

## Features

- **32-key keyboard** (4x8 matrix)
- **USB MIDI output** - works with any DAW or MIDI software
- **Low latency** - optimized scanning algorithm
- **Configurable** - easy to customize note range, velocity, and pin assignments
- **Debounced input** - prevents duplicate MIDI messages
- **Open source** - MIT licensed

## Hardware Requirements

### Components

- **Arduino Leonardo** or **Arduino Micro** (or any Arduino with native USB support)
- **32 momentary push buttons** (for keys)
- **Resistors** for creating the resistor matrix
- **Breadboard and jumper wires** for prototyping

### Supported Arduino Boards

This project requires an Arduino board with **native USB support** for MIDI communication:

- Arduino Leonardo
- Arduino Micro
- Arduino Pro Micro
- Arduino Due
- Any board based on ATmega32U4 or SAMD21

**Note:** Arduino Uno and Nano do **not** have native USB and will **not** work without additional hardware.

## Wiring

### Pin Configuration

| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| Column 0 | Digital Pin 2 | First column (output) |
| Column 1 | Digital Pin 3 | Second column (output) |
| Column 2 | Digital Pin 4 | Third column (output) |
| Column 3 | Digital Pin 5 | Fourth column (output) |
| Column 4 | Digital Pin 6 | Fifth column (output) |
| Column 5 | Digital Pin 7 | Sixth column (output) |
| Column 6 | Digital Pin 8 | Seventh column (output) |
| Column 7 | Digital Pin 9 | Eighth column (output) |
| Row 0 | Analog Pin A0 | First row (input) |
| Row 1 | Analog Pin A1 | Second row (input) |
| Row 2 | Analog Pin A2 | Third row (input) |
| Row 3 | Analog Pin A3 | Fourth row (input) |

### Matrix Layout

The keyboard uses a **4x8 resistor matrix** configuration:

```
         COL0   COL1   COL2   COL3   COL4   COL5   COL6   COL7
         (D2)   (D3)   (D4)   (D5)   (D6)   (D7)   (D8)   (D9)
ROW0(A0)  [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]
ROW1(A1)  [9]   [10]   [11]   [12]   [13]   [14]   [15]   [16]
ROW2(A2) [17]   [18]   [19]   [20]   [21]   [22]   [23]   [24]
ROW3(A3) [25]   [26]   [27]   [28]   [29]   [30]   [31]   [32]
```

### Wiring Diagram

Each key in the matrix is connected as follows:

1. **Column pins (D2-D9)** are set to OUTPUT mode and scanned one at a time
2. **Row pins (A0-A3)** are set to INPUT mode and read as analog values
3. Each button connects a column to a row through a resistor
4. The resistor values create unique analog readings for each key position

**Simplified Circuit:**
```
Arduino D2 ----[Button 1]----[Resistor]---- A0
Arduino D2 ----[Button 9]----[Resistor]---- A1
Arduino D3 ----[Button 2]----[Resistor]---- A0
... (and so on for all 32 keys)
```

For detailed resistor values and circuit diagrams, see `docs/WIRING.md`.

## Software Requirements

### Arduino IDE

1. **Arduino IDE** version 1.8.13 or newer
2. **MIDIUSB Library** - Install from Library Manager

### Installing MIDIUSB Library

1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for "MIDIUSB"
4. Install **MIDIUSB by Arduino**

## Installation

### Quick Start

1. **Clone this repository:**
   ```bash
   git clone https://github.com/YatogamiRaito/MIDIKeyboard.git
   cd MIDIKeyboard
   ```

2. **Open the sketch:**
   ```bash
   # Open ArduinoMIDIKeyboard.ino in Arduino IDE
   ```

3. **Install dependencies:**
   - Install MIDIUSB library (see above)

4. **Select your board:**
   - Tools → Board → Arduino Leonardo (or your board)

5. **Upload:**
   - Click Upload button
   - Wait for compilation and upload to complete

6. **Connect and test:**
   - Connect Arduino via USB
   - Your computer should recognize it as a MIDI device
   - Open any DAW or MIDI monitoring software to test

## Configuration

All configuration options are at the top of the sketch for easy customization:

### Matrix Dimensions

```cpp
const int NUM_ROWS = 4;  // Number of rows in matrix
const int NUM_COLS = 8;  // Number of columns in matrix
```

### Pin Configuration

```cpp
const int FIRST_COL_PIN = 2;  // First column pin
const int LAST_COL_PIN = 9;   // Last column pin
const int ROW_PINS[NUM_ROWS] = {A0, A1, A2, A3};  // Row pins
```

### MIDI Configuration

```cpp
const int STARTING_MIDI_NOTE = 52;  // Starting MIDI note (E3)
const byte MIDI_CHANNEL = 0;        // MIDI channel (0 = channel 1)
const byte MIDI_VELOCITY = 127;     // Note velocity (0-127)
```

### Key Detection Thresholds

```cpp
const int NO_PRESS_THRESHOLD = 1000;  // Analog value for no key press
const int PRESS_THRESHOLD = 87;        // Minimum value for key press
```

**Note:** You may need to adjust these thresholds based on your resistor values.

### Timing Configuration

```cpp
const int SCAN_DELAY_MICROSECONDS = 100;  // Delay between scans
```

## MIDI Note Mapping

The keyboard maps matrix positions to MIDI notes starting from note 52 (E3):

| Key Position | MIDI Note | Note Name |
|--------------|-----------|-----------|
| Row 0, Col 0 | 53 | F3 |
| Row 0, Col 1 | 54 | F#3 |
| Row 0, Col 2 | 55 | G3 |
| ... | ... | ... |
| Row 3, Col 7 | 84 | C6 |

**Formula:** `MIDI Note = STARTING_MIDI_NOTE + (row * 8) + col + 1`

### Changing Note Range

To change the starting note, modify the `STARTING_MIDI_NOTE` constant:

```cpp
const int STARTING_MIDI_NOTE = 60;  // Start from Middle C (C4)
```

## Usage

### With a DAW (Digital Audio Workstation)

1. Connect Arduino via USB
2. Open your DAW (Ableton Live, FL Studio, Logic Pro, etc.)
3. Select **Arduino Leonardo** (or your board name) as MIDI input device
4. Press keys on your keyboard to trigger MIDI notes

### With MIDI Monitoring Software

**On Windows:**
- [MIDI-OX](http://www.midiox.com/)
- [MIDI Monitor](https://www.snoize.com/MIDIMonitor/) (Mac)

**On macOS:**
- Audio MIDI Setup (built-in)
- MIDI Monitor

**On Linux:**
```bash
aseqdump -p "Arduino"
```

## Troubleshooting

### Arduino not recognized as MIDI device

- Make sure you're using Arduino Leonardo/Micro (boards with native USB)
- Try a different USB cable
- Reinstall the Arduino USB drivers

### Keys not responding

1. **Check wiring** - verify all connections are secure
2. **Open Serial Monitor** - add debug prints to see analog readings
3. **Adjust thresholds** - modify `PRESS_THRESHOLD` and `NO_PRESS_THRESHOLD`
4. **Test individual keys** - isolate the problem to specific keys

### Multiple notes triggering at once

- This is called "ghosting" in matrix keyboards
- Add diodes to each key to prevent ghosting
- Adjust resistor values for better separation

### Delayed or missed notes

- Reduce `SCAN_DELAY_MICROSECONDS` for faster scanning
- Simplify your circuit to reduce capacitance

## Advanced Customization

### Adding Velocity Sensitivity

The current version uses fixed velocity. To add velocity sensitivity:

1. Measure how quickly the analog value changes when a key is pressed
2. Map this to velocity (0-127)
3. Modify the `noteOn()` calls to use calculated velocity

### Adding More Keys

To expand beyond 32 keys:

1. Modify `NUM_ROWS` and/or `NUM_COLS`
2. Add more digital/analog pins
3. Update `ROW_PINS` array and `FIRST_COL_PIN`/`LAST_COL_PIN`

### Using Different Pins

Simply change the constants at the top of the sketch:

```cpp
const int FIRST_COL_PIN = 10;  // Start from pin 10 instead
const int ROW_PINS[NUM_ROWS] = {A4, A5, A6, A7};  // Different analog pins
```

## Code Improvements (Optimized Version)

This optimized version includes:

- **English variable names and comments** - better international collaboration
- **Configuration constants** - no hard-coded values
- **Helper functions** - cleaner, more maintainable code
- **Efficient scanning** - uses loops instead of repetitive code
- **Better documentation** - comprehensive inline comments
- **Row idle detection** - skips processing for inactive rows (performance boost)
- **Proper debouncing** - prevents duplicate MIDI messages

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

### Development

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Credits

- **Original Author:** ebubekir karaca
- **Optimized Version:** 2025
- **MIDIUSB Library:** Arduino

## Links

- [Arduino MIDIUSB Documentation](https://www.arduino.cc/reference/en/libraries/midiusb/)
- [MIDI Note Numbers](https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies)
- [Arduino Leonardo](https://www.arduino.cc/en/Main/Arduino_BoardLeonardo)

## Support

For questions or issues:
- Open an [Issue](https://github.com/YatogamiRaito/MIDIKeyboard/issues)
- Check existing issues for solutions

---

**Happy MIDI making! 🎹🎵**
