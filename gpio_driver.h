#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

/* Pins */
#define LED_PIN     GPIO_NUM_4
#define LED2_PIN    GPIO_NUM_5
#define BUTTON_PIN  GPIO_NUM_37

void led_blink(void);
void button_polling_init(void);
void button_isr_init(void);
void pulse_generation_init(void);
void gpio_task1(void *pvparameters);
void gpio_task2(void *pvparameters);

#endif
