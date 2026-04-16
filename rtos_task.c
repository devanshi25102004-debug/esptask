#include <stdio.h>
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtos_task.h"
#include "driver/gpio.h"
#include "esp_log.h"

//*............. QUEUE DEMO ..........*//

static QueueHandle_t data_queue;

static void producer_task(void *pv)
{
    int sensor_value = 0;

    while (1)
    {
        sensor_value++;
        xQueueSend(data_queue, &sensor_value, portMAX_DELAY);
        printf("Queue Sent: %d\n", sensor_value);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void consumer_task(void *pv)
{
    int received;

    while (1)
    {
        if (xQueueReceive(data_queue, &received, portMAX_DELAY))
        {
            printf("Queue Received: %d\n", received);
        }
    }
}

void queue_demo_init(void)
{
    data_queue = xQueueCreate(5, sizeof(int));

    xTaskCreate(producer_task, "Producer", 2048, NULL, 5, NULL);
    xTaskCreate(consumer_task, "Consumer", 2048, NULL, 5, NULL);
}

//*............. SEMAPHORE DEMO ..........*//

static SemaphoreHandle_t mySemaphore;

static void sender_task(void *pv)
{
    while (1)
    {
        printf("Sender: Give Semaphore\n");
        xSemaphoreGive(mySemaphore);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

static void receiver_task(void *pv)
{
    while (1)
    {
        if (xSemaphoreTake(mySemaphore, portMAX_DELAY))
        {
            printf("Receiver: Semaphore Taken\n");
        }
    }
}

void semaphore_demo_init(void)
{
    mySemaphore = xSemaphoreCreateBinary();

    xTaskCreate(sender_task, "Sender", 2048, NULL, 4, NULL);
    xTaskCreate(receiver_task, "Receiver", 2048, NULL, 4, NULL);
}

//*............. SEMAPHORE BUTTON DEM

#define BUTTON_GPIO 37
#define LED_GPIO    4

static SemaphoreHandle_t button_semaphore;
static const char *TAG = "BTN_SEM";

static void IRAM_ATTR button_isr_handler(void *arg)
{
    BaseType_t hp_task_woken = pdFALSE;
    xSemaphoreGiveFromISR(button_semaphore, &hp_task_woken);

    if (hp_task_woken)
        portYIELD_FROM_ISR();
}

static void button_task(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(button_semaphore, portMAX_DELAY))
        {
            ESP_LOGI(TAG, "Button Pressed");
            gpio_set_level(LED_GPIO,
                          !gpio_get_level(LED_GPIO));
        }
    }
}

void semaphore_button_init(void)
{
    button_semaphore = xSemaphoreCreateBinary();

    gpio_config_t led = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT};
    gpio_config(&led);

    gpio_config_t btn = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .intr_type = GPIO_INTR_NEGEDGE};
    gpio_config(&btn);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_GPIO,
                         button_isr_handler, NULL);

    xTaskCreate(button_task, "ButtonTask", 2048, NULL, 5, NULL);
}

//*............. MUTEX PRINT DEMO ..........*//

static SemaphoreHandle_t printMutex;

static void task1_print(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(printMutex, portMAX_DELAY))
        {
            printf("Task1: Hello World\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            printf("Task1: Devanshi\n");
            xSemaphoreGive(printMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void task2_print(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(printMutex, portMAX_DELAY))
        {
            printf("Task2: Hello World\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            printf("Task2: Devanshi\n");
            xSemaphoreGive(printMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void mutex_print_init(void)
{
    printMutex = xSemaphoreCreateMutex();

    xTaskCreate(task1_print, "Print1", 2048, NULL, 3, NULL);
    xTaskCreate(task2_print, "Print2", 2048, NULL, 3, NULL);
}

//*............. MUTEX LED DEMO ..........*//

#define LED_MUTEX_PIN 4
static SemaphoreHandle_t ledMutex;

static void led_task1(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(ledMutex, portMAX_DELAY))
        {
            gpio_set_level(LED_MUTEX_PIN, 1);
            printf("LED Task1 ON\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            gpio_set_level(LED_MUTEX_PIN, 0);
            printf("LED Task1 OFF\n");

            xSemaphoreGive(ledMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

static void led_task2(void *arg)
{
    while (1)
    {
        if (xSemaphoreTake(ledMutex, portMAX_DELAY))
        {
            gpio_set_level(LED_MUTEX_PIN, 1);
            printf("LED Task2 ON\n");
            vTaskDelay(pdMS_TO_TICKS(1000));

            gpio_set_level(LED_MUTEX_PIN, 0);
            printf("LED Task2 OFF\n");

            xSemaphoreGive(ledMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void mutex_led_init(void)
{
    gpio_reset_pin(LED_MUTEX_PIN);
    gpio_set_direction(LED_MUTEX_PIN, GPIO_MODE_OUTPUT);

    ledMutex = xSemaphoreCreateMutex();

    xTaskCreate(led_task1, "LED1", 2048, NULL, 2, NULL);
    xTaskCreate(led_task2, "LED2", 2048, NULL, 2, NULL);
}