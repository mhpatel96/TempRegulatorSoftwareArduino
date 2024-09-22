
#include <Arduino.h>

#include <FreeRTOS.h>
#include <task.h>

#include <DHT.h>

DHT dht(0, DHT11);

void Blinky_Task(void *pvParameters)
{
    bool flip = false;
    pinMode(LED_BUILTIN, OUTPUT);

    while (1)
    {
        digitalWrite(LED_BUILTIN, flip);
        flip = !flip;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Test_Task(void *pvParameters)
{
    while (1)
    {
        dht.read();
        Serial.print("Temp ");
        Serial.println(dht.readTemperature());
        Serial.print("Humidity ");
        Serial.println(dht.readHumidity());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void setup(void) 
{
    Serial.begin(9600);

    dht.begin();

    xTaskCreate(Blinky_Task, "Blinky", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(Test_Task, "Test", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();

    Serial.println("Error starting scheduler");
}

void loop(void) 
{

}
