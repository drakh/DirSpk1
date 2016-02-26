// state.h

#ifndef STATE_H_
#define STATE_H_

#include <stdbool.h>
#include "encoder.h"

// The type of the GlobalState structure.
// Contains all state that is shared between components, particularly if 
// displayable in UI or in CLI.
typedef struct {
	
	// Whether PWM is enabled. Set by calling xxxx
	// bool pwmEnable;
	// Whether DAC is enabled. Set by calling xxxx
	// bool dacEnable;
	// How Audio signals are generated. Set by calling xxx
	// AudioInMode audioInMode;
	
	// State of the encoders
	EncoderState encoders[NUM_ENCODERS];
	
} GlobalState;

// Global state may be read directly from this variable
extern GlobalState GLOBAL_STATE;

#endif /* STATE_H_ */