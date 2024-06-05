#include "mpl3115a2.h"
#include <util/delay.h>

void mpl3115a2_init(void)
{
    // Initialize MPL3115A2 with altimetry and wait for data to be ready
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_PT_DATA_CFG);
    twi_write(0x07);

    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_CTRL_REG1);
    twi_write(0x39);

    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_STATUS);

    twi_start();
    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    // Wait for data ready.
    uint8_t sta = 0x00;
    while (!(sta & 0x08))
    {
        twi_read_ack(&sta);
    }
    twi_read_nack(&sta);

	// TODO 3.1: stop I2C transaction
    twi_stop();
}

void mpl3115a2_read_temperature(uint8_t *temperature)
{
    // TODO 3.2: Read the temperature from the sensor
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_T_MSB);
    twi_start();
    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    uint8_t temp_msb = 0x00;
    uint8_t temp_lsb = 0x00;
    twi_read_ack(&temp_msb);
    twi_read_nack(&temp_lsb);

    *temperature = temp_msb;

    twi_stop();
}
void mpl3115a2_read_pressure(uint32_t *pressure)
{
    // TODO 3.2: Read the pressure from the sensor
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_P_MSB);
    twi_start();
    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    uint8_t pres_msb = 0x00;
    uint8_t pres_csb = 0x00;
    uint8_t pres_lsb = 0x00;

    twi_read_ack(&pres_msb);
    twi_read_ack(&pres_csb);
    twi_read_nack(&pres_lsb);

    *pressure = ((pres_msb << 16) | (pres_csb << 8) | pres_lsb) >> 4;

    twi_stop();
}