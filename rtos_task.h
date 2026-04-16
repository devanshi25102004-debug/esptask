#ifndef RTOS_TASK_H
#define RTOS_TASK_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

/* ------------ INIT FUNCTIONS ------------ */
void queue_demo_init(void);
void semaphore_demo_init(void);
void semaphore_button_init(void);
void mutex_print_init(void);
void mutex_led_init(void);

#endif