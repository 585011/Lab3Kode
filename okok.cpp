#include <Arduino.h>
#include <DHT.h>
#include <WiFiS3.h>
#include <SPI.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.end();

  Serial.print("Setup complete");
}

void enterLowPowerMode() {
  // Sleep instruction for ARM Cortex-M4
  __disable_irq();
  __WFI();
  //SPI.end();
  __enable_irq();
}

void loop() {
  dht.begin();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.print("{\"temperature\": ");
    Serial.print(temperature);
    Serial.print(", \"humidity\": ");
    Serial.print(humidity);
    Serial.println("}"); // Add a newline at the end
  }

  // Enter low power mode for 10 minutes
  for (int i = 0; i < 600; i++) {
    //enterLowPowerMode();
    delay(1000);  // 1 second delay in sleep mode
  }
}
