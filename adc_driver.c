#include "adc_driver.h"


/* ---------- ADC Configuration ---------- */
#define ADC_CHANNEL    ADC1_CHANNEL_0
#define ADC_ATTEN      ADC_ATTEN_DB_11
#define ADC_WIDTH      ADC_WIDTH_BIT_12

/* ---------- PT100 Configuration ---------- */
#define VREF           3300.0    // Reference voltage in mV (3.3V)
#define R_FIXED        1000.0    // Fixed resistor value (1kΩ)
#define PT100_R0       100.0     // PT100 resistance at 0°C
#define ALPHA          0.00385   // Temperature coefficient

int adc_raw = 0;
float voltage = 0;
float r_pt100 = 0 ;
float temperature = 0;
void app_main(void)
{
    /* ADC Initialization */
    adc1_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

    while (1)
    {
        /* Step 1: Read ADC raw value */
        adc_raw = adc1_get_raw(ADC_CHANNEL);

        /* Step 2: Convert ADC value to voltage (mV) */
        voltage = (adc_raw * VREF) / 4095.0;

        /* Step 3: Calculate PT100 resistance using voltage divider */
        r_pt100 = (voltage * R_FIXED) / (VREF - voltage);

        /* Step 4: Calculate temperature */
        temperature = (r_pt100 - PT100_R0) / (PT100_R0 * ALPHA);

        /* Step 5: Print values */
        printf("ADC Raw Value      : %d\n", adc_raw);
        printf("Voltage            : %.2f mV\n", voltage);
        printf("PT100 Resistance   : %.2f Ohm\n", r_pt100);
        printf("Temperature        : %.2f °C\r\n", temperature);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

