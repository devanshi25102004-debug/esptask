
#include "wifi_manager.h"

void app_main()
{
    wifi_init();
}





//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "gpio_driver.h"

//void app_main(void)
//{
   // int led_state = 0;
    //xTaskCreate(gpio_task1, "led_task1", 2048, NULL, 3, NULL);
    //xTaskCreate(gpio_task2, "led_task2", 2048, NULL, 2, NULL);
    //vTaskDelay(pdMS_TO_TICKS(1000));
//}

//static const char *TAG = "APP_MAIN";

//*void app_main(void)//
//{
    //uart_init();
    
    //xTaskCreate(uart_task, "uart_task", 4096, NULL, 5, NULL);

   // while (1)
   // {
        //ESP_LOGI(TAG, "APP MAIN RUNNING");
       // vTaskDelay(pdMS_TO_TICKS(1000));
    //}
//}
    
