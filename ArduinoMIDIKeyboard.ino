/*
 * Arduino MIDI Keyboard Controller
 *
 * This sketch turns an Arduino into a MIDI keyboard controller using a resistor matrix.
 * It scans a 4x8 button matrix and sends MIDI note on/off messages via USB.
 *
 * Hardware Configuration:
 * - 4 rows connected to analog pins A0-A3 (input)
 * - 8 columns connected to digital pins 2-9 (output)
 * - Each key is part of a resistor matrix
 *
 * Author: ebubekir karaca
 * License: MIT
 * Optimized Version: 2025
 */

#include "MIDIUSB.h"

// ============================================================================
// CONFIGURATION CONSTANTS
// ============================================================================

// Matrix dimensions
const int NUM_ROWS = 4;
const int NUM_COLS = 8;
const int TOTAL_KEYS = NUM_ROWS * NUM_COLS;  // 32 keys

// Pin configuration
const int FIRST_COL_PIN = 2;  // Columns use pins 2-9
const int LAST_COL_PIN = 9;
const int ROW_PINS[NUM_ROWS] = {A0, A1, A2, A3};  // Rows on analog pins

// MIDI configuration
const int STARTING_MIDI_NOTE = 52;  // E3 (MIDI note 52)
const byte MIDI_CHANNEL = 0;        // MIDI channel 1 (0-indexed)
const byte MIDI_VELOCITY = 127;     // Maximum velocity (0-127)

// Key detection thresholds
const int NO_PRESS_THRESHOLD = 1000;  // Values above this = no key pressed
const int PRESS_THRESHOLD = 87;        // Values above this = key pressed

// Timing configuration
const int SCAN_DELAY_MICROSECONDS = 100;  // Delay between column scans

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// Current state of each key (true = pressed, false = released)
boolean keyPressed[NUM_ROWS][NUM_COLS];

// Tracks if MIDI message has been sent for current key state
// (prevents duplicate note-on messages while key is held)
boolean messageSent[NUM_ROWS][NUM_COLS];

// Temporary storage for analog readings during matrix scan
int analogValues[NUM_ROWS];

// ============================================================================
// MIDI FUNCTIONS
// ============================================================================

/**
 * Send a MIDI note-on message
 * @param channel MIDI channel (0-15)
 * @param pitch MIDI note number (0-127)
 * @param velocity Note velocity (0-127)
 */
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

/**
 * Send a MIDI note-off message
 * @param channel MIDI channel (0-15)
 * @param pitch MIDI note number (0-127)
 * @param velocity Release velocity (0-127)
 */
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

// ============================================================================
// MATRIX SCANNING FUNCTIONS
// ============================================================================

/**
 * Initialize all column pins to OUTPUT mode and set them LOW
 */
void initializeColumnPins() {
  for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

/**
 * Initialize all row pins to INPUT mode
 */
void initializeRowPins() {
  for (int i = 0; i < NUM_ROWS; i++) {
    pinMode(ROW_PINS[i], INPUT);
  }
}

/**
 * Set all column pins to LOW
 */
void setAllColumnsLow() {
  for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
    digitalWrite(pin, LOW);
  }
}

/**
 * Read analog values from all row pins
 */
void readRowValues() {
  for (int row = 0; row < NUM_ROWS; row++) {
    analogValues[row] = analogRead(ROW_PINS[row]);
  }
}

/**
 * Check if all keys in a row are unpressed
 * @param rowValues Array of 8 analog values for one row
 * @return true if all values indicate no key press
 */
boolean isRowIdle(int rowValues[NUM_COLS]) {
  for (int col = 0; col < NUM_COLS; col++) {
    if (rowValues[col] <= NO_PRESS_THRESHOLD) {
      return false;  // At least one key is pressed
    }
  }
  return true;  // All keys unpressed
}

/**
 * Calculate MIDI note number for a given matrix position
 * @param row Row index (0-3)
 * @param col Column index (0-7)
 * @return MIDI note number
 */
int getMidiNote(int row, int col) {
  return STARTING_MIDI_NOTE + (row * NUM_COLS) + col + 1;
}

// ============================================================================
// SETUP AND MAIN LOOP
// ============================================================================

void setup() {
  // Initialize state arrays
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      keyPressed[row][col] = false;
      messageSent[row][col] = true;  // Start as "sent" to avoid initial spurious notes
    }
  }

  // Initialize hardware pins
  initializeColumnPins();
  initializeRowPins();
}

void loop() {
  // Matrix to store analog readings from key matrix
  int keyValues[NUM_ROWS][NUM_COLS];

  // Scan the button matrix column by column
  for (int col = 0; col < NUM_COLS; col++) {
    // Set all columns LOW
    setAllColumnsLow();

    // Set current column HIGH
    digitalWrite(FIRST_COL_PIN + col, HIGH);

    // Read analog values from all rows
    readRowValues();

    // Store readings for this column
    for (int row = 0; row < NUM_ROWS; row++) {
      keyValues[row][col] = analogValues[row];
    }
  }

  // Process each row to detect key presses and releases
  for (int row = 0; row < NUM_ROWS; row++) {
    // Skip processing if entire row is idle (optimization)
    if (isRowIdle(keyValues[row])) {
      // Still need to check for any keys that were previously pressed
      for (int col = 0; col < NUM_COLS; col++) {
        if (keyPressed[row][col]) {
          keyPressed[row][col] = false;

          // Send note-off if we previously sent note-on
          if (!messageSent[row][col]) {
            noteOff(MIDI_CHANNEL, getMidiNote(row, col), MIDI_VELOCITY);
            messageSent[row][col] = true;
          }
        }
      }
      continue;  // Skip to next row
    }

    // Process each key in the row
    for (int col = 0; col < NUM_COLS; col++) {
      // Check if key is pressed (value above press threshold)
      if (keyValues[row][col] > PRESS_THRESHOLD) {
        // Key is pressed
        keyPressed[row][col] = true;

        // Send note-on if we haven't already
        if (messageSent[row][col]) {
          noteOn(MIDI_CHANNEL, getMidiNote(row, col), MIDI_VELOCITY);
          messageSent[row][col] = false;
        }
      } else {
        // Key is released
        if (keyPressed[row][col]) {
          keyPressed[row][col] = false;

          // Send note-off if we previously sent note-on
          if (!messageSent[row][col]) {
            noteOff(MIDI_CHANNEL, getMidiNote(row, col), MIDI_VELOCITY);
            messageSent[row][col] = true;
          }
        }
      }
    }

    // Flush MIDI buffer after processing each row
    MidiUSB.flush();
    delayMicroseconds(SCAN_DELAY_MICROSECONDS);
  }
}
