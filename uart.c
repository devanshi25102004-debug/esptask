#include "uart.h"
#include "driver/gpio.h"


/* -------- PASSWORD -------- */
#define PASSWORD "1234"

void app_main(void)
{
    uint8_t data[256];
    int login = 0;   // 0 = locked , 1 = unlocked

    /* LED setup */
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    /* UART setup */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_driver_install(UART_PORT, 1024, 0, 0, NULL, 0);
    uart_param_config(UART_PORT, &uart_config);
    uart_set_pin(UART_PORT, 43, 44,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);

    uart_write_bytes(UART_PORT,
                     "Enter Password:\r\n",
                     strlen("Enter Password:\r\n"));

    /* -------- LOOP -------- */
    while (1)
    {
        int len = uart_read_bytes(UART_PORT,
                                  data,
                                  255,
                                  pdMS_TO_TICKS(1000));

        if (len > 0)
        {
            data[len] = '\0';
            data[strcspn((char*)data, "\r\n")] = 0;

            /* -------- PASSWORD CHECK -------- */
            if (login == 0)
            {
                if (strcmp((char*)data, PASSWORD) == 0)
                {
                    login = 1;

                    uart_write_bytes(UART_PORT,
                        "Login Success\r\n welcome devanshi panchal\r\n",
                        strlen("Login Success\r\n welcome devanshi panchal\r\n"));
                }
                else
                {
                    uart_write_bytes(UART_PORT,
                        "Wrong Password\r\n",
                        strlen("Wrong Password\r\n"));
                }
            }

            /* -------- COMMAND MODE -------- */
            else
            {
                if (strcmp((char*)data, "hello") == 0)
                {
                    uart_write_bytes(UART_PORT,
                        "Hello UART Working\r\n",
                        strlen("Hello UART Working\r\n"));
                }
                else if (strcmp((char*)data, "ON") == 0)
                {
                    gpio_set_level(LED_PIN, 1);

                    uart_write_bytes(UART_PORT,
                        "LED ON\r\n",
                        strlen("LED ON\r\n"));
                }
                else if (strcmp((char*)data, "OFF") == 0)
                {
                    gpio_set_level(LED_PIN, 0);

                    uart_write_bytes(UART_PORT,
                        "LED OFF\r\n",
                        strlen("LED OFF\r\n"));
                }
                else
                {
                    uart_write_bytes(UART_PORT,
                        "Invalid Command\r\n",
                        strlen("Invalid Command\r\n"));
                }
            }
        }
    }
}