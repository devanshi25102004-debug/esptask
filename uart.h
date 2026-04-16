#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "config.h"
#include "gpio_driver.h"
#include "esp_system.h"

#define UART_PORT      UART_NUM_1
#define UART_TX_PIN    43
#define UART_RX_PIN    44


#define LED_PIN        GPIO_NUM_4

void uart_init(void);
void uart_task(void *pvParameters);
int uart_read_data(uint8_t *data);
void uart_send(const char *msg);

#endif
