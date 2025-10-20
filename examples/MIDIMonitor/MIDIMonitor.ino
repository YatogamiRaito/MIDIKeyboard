/*
 * MIDI Monitor
 *
 * This sketch sends MIDI messages AND prints them to Serial Monitor.
 * Use this to verify that the correct MIDI notes are being sent for each key.
 *
 * Instructions:
 * 1. Upload this sketch
 * 2. Open Serial Monitor at 9600 baud
 * 3. Also open your MIDI software to receive MIDI
 * 4. Press keys - you'll see MIDI messages in both Serial Monitor and MIDI software
 *
 * This helps verify:
 * - Correct MIDI note numbers for each key
 * - MIDI channel is correct
 * - Velocity values are as expected
 * - Note on/off messages are paired correctly
 */

#include "MIDIUSB.h"

const int NUM_ROWS = 4;
const int NUM_COLS = 8;
const int FIRST_COL_PIN = 2;
const int LAST_COL_PIN = 9;
const int ROW_PINS[NUM_ROWS] = {A0, A1, A2, A3};

const int STARTING_MIDI_NOTE = 52;
const byte MIDI_CHANNEL = 0;
const byte MIDI_VELOCITY = 127;
const int NO_PRESS_THRESHOLD = 1000;
const int PRESS_THRESHOLD = 87;

boolean keyPressed[NUM_ROWS][NUM_COLS];
boolean messageSent[NUM_ROWS][NUM_COLS];

// MIDI note names for display
const char* noteNames[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);

  // Print to serial
  Serial.print("NOTE ON:  Ch ");
  Serial.print(channel + 1);
  Serial.print(" | Note ");
  Serial.print(pitch);
  Serial.print(" (");
  Serial.print(noteNames[pitch % 12]);
  Serial.print(pitch / 12 - 1);
  Serial.print(") | Vel ");
  Serial.println(velocity);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);

  // Print to serial
  Serial.print("NOTE OFF: Ch ");
  Serial.print(channel + 1);
  Serial.print(" | Note ");
  Serial.print(pitch);
  Serial.print(" (");
  Serial.print(noteNames[pitch % 12]);
  Serial.print(pitch / 12 - 1);
  Serial.print(") | Vel ");
  Serial.println(velocity);
}

int getMidiNote(int row, int col) {
  return STARTING_MIDI_NOTE + (row * NUM_COLS) + col + 1;
}

void setup() {
  Serial.begin(9600);

  // Wait for serial connection (optional, but helpful)
  delay(1000);

  Serial.println("==========================================");
  Serial.println("Arduino MIDI Keyboard - MIDI Monitor");
  Serial.println("==========================================");
  Serial.println();
  Serial.print("MIDI Channel: ");
  Serial.println(MIDI_CHANNEL + 1);
  Serial.print("Starting Note: ");
  Serial.print(STARTING_MIDI_NOTE);
  Serial.print(" (");
  Serial.print(noteNames[STARTING_MIDI_NOTE % 12]);
  Serial.print(STARTING_MIDI_NOTE / 12 - 1);
  Serial.println(")");
  Serial.print("Velocity: ");
  Serial.println(MIDI_VELOCITY);
  Serial.println();
  Serial.println("Press keys to send MIDI...");
  Serial.println("------------------------------------------");
  Serial.println();

  // Initialize pins
  for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  for (int i = 0; i < NUM_ROWS; i++) {
    pinMode(ROW_PINS[i], INPUT);
  }

  // Initialize state
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      keyPressed[row][col] = false;
      messageSent[row][col] = true;
    }
  }
}

void loop() {
  int keyValues[NUM_ROWS][NUM_COLS];

  // Scan matrix
  for (int col = 0; col < NUM_COLS; col++) {
    for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
      digitalWrite(pin, LOW);
    }

    digitalWrite(FIRST_COL_PIN + col, HIGH);

    for (int row = 0; row < NUM_ROWS; row++) {
      keyValues[row][col] = analogRead(ROW_PINS[row]);
    }
  }

  // Process keys
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      if (keyValues[row][col] > PRESS_THRESHOLD) {
        keyPressed[row][col] = true;

        if (messageSent[row][col]) {
          noteOn(MIDI_CHANNEL, getMidiNote(row, col), MIDI_VELOCITY);
          messageSent[row][col] = false;
        }
      } else {
        if (keyPressed[row][col]) {
          keyPressed[row][col] = false;

          if (!messageSent[row][col]) {
            noteOff(MIDI_CHANNEL, getMidiNote(row, col), MIDI_VELOCITY);
            messageSent[row][col] = true;
          }
        }
      }
    }

    MidiUSB.flush();
    delayMicroseconds(100);
  }
}
