// spi.c
#include <asf.h>
#include "spi.h"
#include "state.h"
#include "util.h"

// Start the SPI subsystem
void startSpi(void) {
	GLOBAL_STATE.spiMutex = xSemaphoreCreateMutex();
	ASSERT_BLINK(GLOBAL_STATE.spiMutex, 4, 1);
}

// Force SPI_RDR to be read
static __attribute__((optimize("O0"))) inline int32_t forceReadRDR(void) {
	return SPI0->SPI_RDR;
}

#define SPI_TIMEOUT_MS 1000

// Send a datum, receive a datum.
// Channel number must be encoded in bits 19-16
// Acquire semaphore before using
uint32_t spiSendReceive(uint32_t datum) {
	portTickType timeout = xTaskGetTickCount() + MS_TO_TICKS(SPI_TIMEOUT_MS);
	// Empty receive data register
	forceReadRDR();
	SPI0->SPI_TDR = datum;
	
	// Busy-ish waiting. 
	// TODO: This will still starve lower priority tasks.
	// Use an interrupt + semaphore instead.
	while ((SPI0->SPI_SR & SPI_SR_TDRE) && (xTaskGetTickCount() < timeout)) {
		portYIELD();
	}
	while ((SPI0->SPI_SR & SPI_SR_RDRF) && (xTaskGetTickCount() < timeout)) {
		portYIELD();
	}
	
	if (xTaskGetTickCount() >= timeout) {
		errorBlink(4, 2);
	}
	return SPI0->SPI_RDR;
}