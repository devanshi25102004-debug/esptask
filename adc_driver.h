#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

/* ---------- ADC Configuration ---------- */
#define ADC_CHANNEL    ADC1_CHANNEL_0
#define ADC_ATTEN      ADC_ATTEN_DB_11
#define ADC_WIDTH      ADC_WIDTH_BIT_12

/* ---------- PT100 Configuration ---------- */
#define VREF           3300.0    // Reference voltage in mV (3.3V)
#define R_FIXED        1000.0    // Fixed resistor value (1kΩ)
#define PT100_R0       100.0     // PT100 resistance at 0°C
#define ALPHA          0.00385   // Temperature coefficient

/* ---------- Function Prototypes ---------- */
void adc_init(void);
int  adc_read_raw(void);
float adc_read_voltage(void);
float pt100_read_temperature(void);

#endif
