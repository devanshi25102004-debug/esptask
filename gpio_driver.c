#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/* ---------- Pin Definitions ---------- */
#define LED_PIN     GPIO_NUM_4
#define LED1_PIN    GPIO_NUM_3
#define LED2_PIN    GPIO_NUM_5
#define BUTTON_PIN  GPIO_NUM_37

static bool led_state = false;
 
/* ---------- ISR for Button ---------- */
static void IRAM_ATTR button_isr_handler(void *arg)
{
    led_state = !led_state;                 // Toggle LED state
    gpio_set_level(LED_PIN, led_state);
}

void app_main(void)
{
    /* ---------- LED Configuration ---------- */
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_reset_pin(LED2_PIN);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);

    /* ---------- Button Configuration ---------- */
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    /* ---------- Interrupt Configuration ---------- */
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);

    while (1)
    {
        /* ---- LED Blink ---- */
        gpio_set_level(LED2_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED2_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        /* ---- Pulse on LED_PIN (if button not used) ---- */
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(200));
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}


/*...........GPIO task ceration .................*/

void gpio_task1(void *pvParameters)
{
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LED1_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED1_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void gpio_task2(void *pvParameters)
{
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LED2_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED2_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}