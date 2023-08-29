#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_MS5637_Arduino_Library.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <SPI.h>
//#include <Arduino_FreeRTOS.h>
#define BNO055_SAMPLERATE_DELAY_MS (100);

#include <ChRt.h>
MS5637 pressureSensor;


Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28,&Wire2);

void setup() {
  Wire2.begin();
  Serial.begin(9600);
  if (!pressureSensor.begin(Wire2))
  {
    Serial.println("Could not find a valid MS5637 sensor, check wiring!");
    while (1);
  }
  if(!bno.begin()){
    Serial.println("Count not find valid BNO055 sensor, check wiring!");
    while(1);
  }

  bno.setExtCrystalUse(true);
}

void loop() {

  sensors_event_t event;
  bno.getEvent(&event);


  float temperature_C = pressureSensor.getTemperature();
  float pressure_mbar = pressureSensor.getPressure();

  Serial.print("Barometer Temperature (Celsius): ");
  Serial.println(temperature_C, 2);

  Serial.print("Barometer Pressure (mbar): ");
  Serial.println(pressure_mbar, 2);

  Serial.print("IMU Orientation: ");
  Serial.print(event.orientation.x);
  Serial.print(" ");
  Serial.print(event.orientation.y);
  Serial.print(" ");
  Serial.print(event.orientation.z);
  Serial.println("");



  delay(1000); // Wait for 1 second
}