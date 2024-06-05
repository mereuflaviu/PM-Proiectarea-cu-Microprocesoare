#include <string.h>
#include <stdio.h>

#include <util/delay.h>
#include <avr/io.h>

#include "usart.h"
#include "mpl3115a2.h"
#include "twi.h"

#define PM_BAUD 9600

int main()
{
	// Initialize USART for writing to serial console.
	USART0_init(CALC_USART_UBRR(PM_BAUD));
	USART0_use_stdio();

	// TODO 2: Initialize I2C (including GPIO)
	twi_init();

	// TODO 2: Search all slaves with adresses within range 0x00-0x7F
	twi_discover();

	// TODO 3.1: Initialize TWI and MPL3115A2 sensor.
	mpl3115a2_init();

	while (1)
	{
		uint8_t temperature = 0;
		uint32_t pressure = 0;
		mpl3115a2_read_pressure(&temperature);
		mpl3115a2_read_temperature(&pressure);

		// TODO 3.2: Read temperature and pressure using the MPL3115A2 driver
		printf("Temp %d\n", temperature);
		printf("Pressure %ld\n", pressure);
		_delay_ms(1000);
	}

	return 0;
}