#ifndef PIANO_FREQUENCIES_H
#define PIANO_FREQUENCIES_H

#include <stdint.h>

// System Configuration
#define DAC_SAMPLE_RATE     32000.0f

// -----------------------------------------------------------------------------
// MACRO: Frequency to Phase Increment
// Converts a frequency to a 32-bit tuning word for the phase accumulator.
// -----------------------------------------------------------------------------
#define PHASE_INC(freq) ((uint32_t)(((freq) * 4294967296.0f) / DAC_SAMPLE_RATE))

// -----------------------------------------------------------------------------
// BASE FREQUENCIES (Octave 4) 
// A4 is exactly 440.0 Hz. The rest are based on the 12th root of 2.
// -----------------------------------------------------------------------------
#define FREQ_C4  261.6256f
#define FREQ_CS4 277.1826f // C#4 / Db4
#define FREQ_D4  293.6648f
#define FREQ_DS4 311.1270f // D#4 / Eb4
#define FREQ_E4  329.6276f
#define FREQ_F4  349.2282f
#define FREQ_FS4 369.9944f // F#4 / Gb4
#define FREQ_G4  391.9954f
#define FREQ_GS4 415.3047f // G#4 / Ab4
#define FREQ_A4  440.0000f
#define FREQ_AS4 466.1638f // A#4 / Bb4
#define FREQ_B4  493.8833f

// -----------------------------------------------------------------------------
// ALL 88 PIANO KEY FREQUENCIES (Derived from Octave 4)
// -----------------------------------------------------------------------------

// Octave 0 (Only A, A#, B exist on a standard 88-key piano)
#define FREQ_A0  (FREQ_A4 / 16.0f)
#define FREQ_AS0 (FREQ_AS4 / 16.0f)
#define FREQ_B0  (FREQ_B4 / 16.0f)

#define FREQ_C1  (FREQ_C4 / 8.0f)
#define FREQ_CS1 (FREQ_CS4 / 8.0f)
#define FREQ_D1  (FREQ_D4 / 8.0f)
#define FREQ_DS1 (FREQ_DS4 / 8.0f)
#define FREQ_E1  (FREQ_E4 / 8.0f)
#define FREQ_F1  (FREQ_F4 / 8.0f)
#define FREQ_FS1 (FREQ_FS4 / 8.0f)
#define FREQ_G1  (FREQ_G4 / 8.0f)
#define FREQ_GS1 (FREQ_GS4 / 8.0f)
#define FREQ_A1  (FREQ_A4 / 8.0f)
#define FREQ_AS1 (FREQ_AS4 / 8.0f)
#define FREQ_B1  (FREQ_B4 / 8.0f)

#define FREQ_C2  (FREQ_C4 / 4.0f)
#define FREQ_CS2 (FREQ_CS4 / 4.0f)
#define FREQ_D2  (FREQ_D4 / 4.0f)
#define FREQ_DS2 (FREQ_DS4 / 4.0f)
#define FREQ_E2  (FREQ_E4 / 4.0f)
#define FREQ_F2  (FREQ_F4 / 4.0f)
#define FREQ_FS2 (FREQ_FS4 / 4.0f)
#define FREQ_G2  (FREQ_G4 / 4.0f)
#define FREQ_GS2 (FREQ_GS4 / 4.0f)
#define FREQ_A2  (FREQ_A4 / 4.0f)
#define FREQ_AS2 (FREQ_AS4 / 4.0f)
#define FREQ_B2  (FREQ_B4 / 4.0f)

#define FREQ_C3  (FREQ_C4 / 2.0f)
#define FREQ_CS3 (FREQ_CS4 / 2.0f)
#define FREQ_D3  (FREQ_D4 / 2.0f)
#define FREQ_DS3 (FREQ_DS4 / 2.0f)
#define FREQ_E3  (FREQ_E4 / 2.0f)
#define FREQ_F3  (FREQ_F4 / 2.0f)
#define FREQ_FS3 (FREQ_FS4 / 2.0f)
#define FREQ_G3  (FREQ_G4 / 2.0f)
#define FREQ_GS3 (FREQ_GS4 / 2.0f)
#define FREQ_A3  (FREQ_A4 / 2.0f)
#define FREQ_AS3 (FREQ_AS4 / 2.0f)
#define FREQ_B3  (FREQ_B4 / 2.0f)

#define FREQ_C5  (FREQ_C4 * 2.0f)
#define FREQ_CS5 (FREQ_CS4 * 2.0f)
#define FREQ_D5  (FREQ_D4 * 2.0f)
#define FREQ_DS5 (FREQ_DS4 * 2.0f)
#define FREQ_E5  (FREQ_E4 * 2.0f)
#define FREQ_F5  (FREQ_F4 * 2.0f)
#define FREQ_FS5 (FREQ_FS4 * 2.0f)
#define FREQ_G5  (FREQ_G4 * 2.0f)
#define FREQ_GS5 (FREQ_GS4 * 2.0f)
#define FREQ_A5  (FREQ_A4 * 2.0f)
#define FREQ_AS5 (FREQ_AS4 * 2.0f)
#define FREQ_B5  (FREQ_B4 * 2.0f)

#define FREQ_C6  (FREQ_C4 * 4.0f)
#define FREQ_CS6 (FREQ_CS4 * 4.0f)
#define FREQ_D6  (FREQ_D4 * 4.0f)
#define FREQ_DS6 (FREQ_DS4 * 4.0f)
#define FREQ_E6  (FREQ_E4 * 4.0f)
#define FREQ_F6  (FREQ_F4 * 4.0f)
#define FREQ_FS6 (FREQ_FS4 * 4.0f)
#define FREQ_G6  (FREQ_G4 * 4.0f)
#define FREQ_GS6 (FREQ_GS4 * 4.0f)
#define FREQ_A6  (FREQ_A4 * 4.0f)
#define FREQ_AS6 (FREQ_AS4 * 4.0f)
#define FREQ_B6  (FREQ_B4 * 4.0f)

#define FREQ_C7  (FREQ_C4 * 8.0f)
#define FREQ_CS7 (FREQ_CS4 * 8.0f)
#define FREQ_D7  (FREQ_D4 * 8.0f)
#define FREQ_DS7 (FREQ_DS4 * 8.0f)
#define FREQ_E7  (FREQ_E4 * 8.0f)
#define FREQ_F7  (FREQ_F4 * 8.0f)
#define FREQ_FS7 (FREQ_FS4 * 8.0f)
#define FREQ_G7  (FREQ_G4 * 8.0f)
#define FREQ_GS7 (FREQ_GS4 * 8.0f)
#define FREQ_A7  (FREQ_A4 * 8.0f)
#define FREQ_AS7 (FREQ_AS4 * 8.0f)
#define FREQ_B7  (FREQ_B4 * 8.0f)

#define FREQ_C8  (FREQ_C4 * 16.0f)

// -----------------------------------------------------------------------------
// USAGE EXAMPLE MACROS (The "Period" Phase Increments)
// Use PHASE_INC() on any of the above to get the 32-bit tuning word.
// -----------------------------------------------------------------------------
#define PHASE_INC_A0  PHASE_INC(FREQ_A0)
#define PHASE_INC_C4  PHASE_INC(FREQ_C4)
#define PHASE_INC_A4  PHASE_INC(FREQ_A4)
#define PHASE_INC_C8  PHASE_INC(FREQ_C8)

#endif // PIANO_FREQUENCIES_H