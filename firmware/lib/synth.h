//synth.h
#pragma once

#include <stdbool.h>
#include <stdint.h>

#define NUM_KEYS 60

void Synth_Write_Buf();

// For ISRs to call
void Attack_Key(uint8_t key_idx, int16_t velocity);
void Release_Key(uint8_t key_idx);