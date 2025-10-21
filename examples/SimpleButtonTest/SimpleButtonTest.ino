/*
 * Simple Button Test
 *
 * This sketch tests individual buttons without MIDI functionality.
 * Use this to verify your buttons are working before testing MIDI.
 *
 * The Serial Monitor will display which keys are currently pressed.
 *
 * Instructions:
 * 1. Upload this sketch
 * 2. Open Serial Monitor at 9600 baud
 * 3. Press keys - you should see "Key [row,col] PRESSED" messages
 * 4. Release keys - you should see "Key [row,col] RELEASED" messages
 */

const int NUM_ROWS = 4;
const int NUM_COLS = 8;
const int FIRST_COL_PIN = 2;
const int LAST_COL_PIN = 9;
const int ROW_PINS[NUM_ROWS] = {A0, A1, A2, A3};

// Thresholds
const int NO_PRESS_THRESHOLD = 1000;
const int PRESS_THRESHOLD = 87;

// State tracking
boolean keyPressed[NUM_ROWS][NUM_COLS];

void setup() {
  Serial.begin(9600);
  Serial.println("====================================");
  Serial.println("Arduino MIDI Keyboard - Button Test");
  Serial.println("====================================");
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
    }
  }

  Serial.println("Ready! Press any key...");
  Serial.println();
}

void loop() {
  int keyValues[NUM_ROWS][NUM_COLS];

  // Scan matrix
  for (int col = 0; col < NUM_COLS; col++) {
    // Set all columns LOW
    for (int pin = FIRST_COL_PIN; pin <= LAST_COL_PIN; pin++) {
      digitalWrite(pin, LOW);
    }

    // Set current column HIGH
    digitalWrite(FIRST_COL_PIN + col, HIGH);
    delayMicroseconds(100);

    // Read rows
    for (int row = 0; row < NUM_ROWS; row++) {
      keyValues[row][col] = analogRead(ROW_PINS[row]);
    }
  }

  // Check for key state changes
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      boolean currentlyPressed = (keyValues[row][col] > PRESS_THRESHOLD) &&
                                  (keyValues[row][col] < NO_PRESS_THRESHOLD);

      // Key press detected
      if (currentlyPressed && !keyPressed[row][col]) {
        keyPressed[row][col] = true;
        Serial.print("Key [");
        Serial.print(row);
        Serial.print(",");
        Serial.print(col);
        Serial.print("] PRESSED (value: ");
        Serial.print(keyValues[row][col]);
        Serial.println(")");
      }

      // Key release detected
      if (!currentlyPressed && keyPressed[row][col]) {
        keyPressed[row][col] = false;
        Serial.print("Key [");
        Serial.print(row);
        Serial.print(",");
        Serial.print(col);
        Serial.println("] RELEASED");
      }
    }
  }

  delay(10);  // Small delay to prevent Serial spam
}
