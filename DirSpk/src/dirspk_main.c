/*
 * Dirspk1 Main
 */ 

#include <asf.h>
#include "init.h"
#include "util.h"

int main(void) {
	// Initialze peripherals etc
	init();
	
	// Blink out a 5/5 patterns
	fatalBlink(1, 3);
}