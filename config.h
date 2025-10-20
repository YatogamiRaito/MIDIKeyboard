/*
 * Configuration File for Arduino MIDI Keyboard
 *
 * This file contains all user-configurable settings.
 * Modify these values to customize your MIDI keyboard without editing the main code.
 *
 * IMPORTANT: After changing any values, re-upload the sketch to your Arduino.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// MATRIX CONFIGURATION
// ============================================================================

// Define the size of your button matrix
// Default: 4 rows x 8 columns = 32 keys
#define NUM_ROWS 4
#define NUM_COLS 8

// ============================================================================
// PIN CONFIGURATION
// ============================================================================

// Column pins (OUTPUT mode)
// These pins scan through the columns of the matrix
// Default: Pins 2-9 for an 8-column matrix
#define FIRST_COL_PIN 2
#define LAST_COL_PIN 9

// Row pins (INPUT mode)
// These analog pins read the resistor matrix values
// Default: A0, A1, A2, A3 for a 4-row matrix
const int ROW_PINS[NUM_ROWS] = {A0, A1, A2, A3};

// ============================================================================
// MIDI CONFIGURATION
// ============================================================================

// Starting MIDI note number
// This is the note number for the first key (row 0, col 0 + 1)
// Common values:
//   36 = C2 (bass)
//   48 = C3 (low)
//   52 = E3 (default)
//   60 = C4 (middle C)
//   72 = C5 (high)
#define STARTING_MIDI_NOTE 52

// MIDI channel (0-15, where 0 = MIDI channel 1)
// Most MIDI software uses channel 1 (0 in code)
#define MIDI_CHANNEL 0

// MIDI velocity for note on/off messages (0-127)
// Higher values = louder notes
// Common values:
//   64 = medium
//   100 = loud
//   127 = maximum (default)
#define MIDI_VELOCITY 127

// ============================================================================
// KEY DETECTION THRESHOLDS
// ============================================================================

// Threshold for "no key pressed" detection
// Analog values ABOVE this indicate no key is pressed in that row
// Default: 1000 (out of 1023 max for 10-bit ADC)
//
// Adjust if:
// - Keys trigger when not pressed: INCREASE this value
// - Keys don't release properly: DECREASE this value
#define NO_PRESS_THRESHOLD 1000

// Threshold for "key pressed" detection
// Analog values ABOVE this (but below NO_PRESS_THRESHOLD) indicate a key press
// Default: 87
//
// Adjust based on your resistor values:
// - Lower value = more sensitive (may cause false triggers)
// - Higher value = less sensitive (may miss light presses)
#define PRESS_THRESHOLD 87

// ============================================================================
// TIMING CONFIGURATION
// ============================================================================

// Delay in microseconds between column scans
// Lower values = faster scanning = lower latency
// Higher values = slower scanning = less CPU usage
//
// Default: 100 microseconds
// Range: 10-1000 microseconds
//
// Adjust if:
// - Keys miss presses: INCREASE this value
// - Response feels sluggish: DECREASE this value
#define SCAN_DELAY_MICROSECONDS 100

// ============================================================================
// ADVANCED: DEBOUNCE CONFIGURATION (Future Enhancement)
// ============================================================================

// These settings are for future implementation of hardware debouncing
// Currently, the code uses the messageSent array for debouncing

// Number of consecutive readings required to confirm a key state change
// Higher values = more debouncing but slower response
// #define DEBOUNCE_COUNT 2

// Debounce delay in milliseconds
// #define DEBOUNCE_DELAY_MS 5

// ============================================================================
// ADVANCED: VELOCITY SENSITIVITY (Future Enhancement)
// ============================================================================

// Enable velocity sensitivity based on key press speed
// Requires additional code implementation
// #define ENABLE_VELOCITY_SENSING false

// Minimum and maximum velocity values
// #define MIN_VELOCITY 20
// #define MAX_VELOCITY 127

// ============================================================================
// DEBUG CONFIGURATION
// ============================================================================

// Enable debug output to Serial Monitor (9600 baud)
// Useful for calibrating thresholds and troubleshooting
// WARNING: Enabling this will slow down MIDI performance
// #define DEBUG_MODE false

// Print analog readings to Serial Monitor
// #define DEBUG_ANALOG_READINGS false

// Print MIDI messages to Serial Monitor
// #define DEBUG_MIDI_MESSAGES false

// ============================================================================
// PRESET CONFIGURATIONS
// ============================================================================

/*
 * Uncomment one of the following preset configurations to quickly set up
 * your keyboard for common use cases. Comment out to use custom settings above.
 */

// PRESET 1: Standard Piano (2 octaves starting from middle C)
// #define PRESET_PIANO
#ifdef PRESET_PIANO
  #undef STARTING_MIDI_NOTE
  #define STARTING_MIDI_NOTE 60  // Middle C (C4)
  #undef MIDI_VELOCITY
  #define MIDI_VELOCITY 100
#endif

// PRESET 2: Bass Keyboard (low notes, loud velocity)
// #define PRESET_BASS
#ifdef PRESET_BASS
  #undef STARTING_MIDI_NOTE
  #define STARTING_MIDI_NOTE 36  // C2
  #undef MIDI_VELOCITY
  #define MIDI_VELOCITY 127
#endif

// PRESET 3: Drum Pads (starting from MIDI note 36 = Bass Drum)
// #define PRESET_DRUMS
#ifdef PRESET_DRUMS
  #undef STARTING_MIDI_NOTE
  #define STARTING_MIDI_NOTE 35  // Acoustic Bass Drum
  #undef MIDI_CHANNEL
  #define MIDI_CHANNEL 9  // MIDI channel 10 (percussion)
  #undef MIDI_VELOCITY
  #define MIDI_VELOCITY 127
#endif

// PRESET 4: Chromatic Scale (1 octave starting from C3)
// #define PRESET_CHROMATIC
#ifdef PRESET_CHROMATIC
  #undef STARTING_MIDI_NOTE
  #define STARTING_MIDI_NOTE 48  // C3
  #undef MIDI_VELOCITY
  #define MIDI_VELOCITY 90
#endif

// ============================================================================
// VALIDATION (DO NOT MODIFY)
// ============================================================================

// Compile-time validation of configuration
#if NUM_ROWS < 1 || NUM_ROWS > 16
  #error "NUM_ROWS must be between 1 and 16"
#endif

#if NUM_COLS < 1 || NUM_COLS > 16
  #error "NUM_COLS must be between 1 and 16"
#endif

#if MIDI_CHANNEL < 0 || MIDI_CHANNEL > 15
  #error "MIDI_CHANNEL must be between 0 and 15"
#endif

#if MIDI_VELOCITY < 0 || MIDI_VELOCITY > 127
  #error "MIDI_VELOCITY must be between 0 and 127"
#endif

#if STARTING_MIDI_NOTE < 0 || STARTING_MIDI_NOTE > 127
  #error "STARTING_MIDI_NOTE must be between 0 and 127"
#endif

#if PRESS_THRESHOLD >= NO_PRESS_THRESHOLD
  #error "PRESS_THRESHOLD must be less than NO_PRESS_THRESHOLD"
#endif

#endif // CONFIG_H
