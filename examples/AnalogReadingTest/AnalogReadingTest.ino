/*
 * Analog Reading Test
 *
 * This sketch helps you test and calibrate your resistor matrix.
 * It displays the analog readings from all row pins in the Serial Monitor.
 *
 * Use this to:
 * 1. Verify your wiring is correct
 * 2. Identify the analog values for each key
 * 3. Determine the optimal PRESS_THRESHOLD and NO_PRESS_THRESHOLD values
 *
 * Instructions:
 * 1. Upload this sketch to your Arduino
 * 2. Open Serial Monitor (Tools → Serial Monitor) at 9600 baud
 * 3. Press each key one at a time
 * 4. Note the analog value that appears
 * 5. Use these values to set thresholds in config.h
 */

// Pin configuration (must match your main sketch)
const int NUM_ROWS = 4;
const int NUM_COLS = 8;
const int FIRST_COL_PIN = 2;
const int LAST_COL_PIN = 9;
const int ROW_PINS[NUM_ROWS] = {A0, A1, A2, A3};

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("=================================");
  Serial.println("Arduino MIDI Keyboard - Analog Test");
  Serial.println("=================================");
  Serial.println();

  // Initialize column pins as OUTPUT
  for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  // Initialize row pins as INPUT
  for (int i = 0; i < NUM_ROWS; i++) {
    pinMode(ROW_PINS[i], INPUT);
  }

  Serial.println("Setup complete. Press keys to see analog readings.");
  Serial.println("Format: [Row] Col0 Col1 Col2 Col3 Col4 Col5 Col6 Col7");
  Serial.println();
}

void loop() {
  // Matrix to store readings
  int readings[NUM_ROWS][NUM_COLS];

  // Scan each column
  for (int col = 0; col < NUM_COLS; col++) {
    // Set all columns LOW
    for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
      digitalWrite(pin, LOW);
    }

    // Set current column HIGH
    digitalWrite(FIRST_COL_PIN + col, HIGH);

    // Small delay for stabilization
    delayMicroseconds(100);

    // Read all rows
    for (int row = 0; row < NUM_ROWS; row++) {
      readings[row][col] = analogRead(ROW_PINS[row]);
    }
  }

  // Print readings
  for (int row = 0; row < NUM_ROWS; row++) {
    Serial.print("[Row ");
    Serial.print(row);
    Serial.print("] ");

    for (int col = 0; col < NUM_COLS; col++) {
      int value = readings[row][col];

      // Format: pad with spaces for alignment
      if (value < 10) Serial.print("   ");
      else if (value < 100) Serial.print("  ");
      else if (value < 1000) Serial.print(" ");

      Serial.print(value);
      Serial.print(" ");
    }

    Serial.println();
  }

  Serial.println("-----------------------------------");

  // Update every 500ms
  delay(500);
}
