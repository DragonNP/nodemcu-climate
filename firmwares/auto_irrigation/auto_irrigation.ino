/*
  Sketch for the project "Smart Climate"
  The source code on GitHub: https://github.com/DragonNP/smart-climate
  Author: DragonNP, 2020
  https://github.com/DragonNP/

  Libs link:
  ------------------------------------------------------
  GyverTimer        -    https://github.com/AlexGyver/GyverLibs/tree/master/GyverTimer
  ------------------------------------------------------
*/
// ============ SETTINGS ============
// --------- Soil Humidity ----------
#define OPTIMAL_HUM 60               // threshold for all flowers (average)
#define SOIL_SENSOR_OUTPUT A0
#define SOIL_SENSOR_PIN 2
#define MIN_VALUE 240                // minimum value (in air)
#define MAX_VALUE 710                // minimum value (in water)

// -------------- PUMP --------------
#define PUMP_PIN 3

//-------------- SERIAL -------------
#define SPEED_SERIAL 9600
// ============ SETTINGS ============

// ============== LIBS ==============
#include <GyverTimer.h>
// ============== LIBS ==============

// ============== VARS ==============
// Timers
GTimer timerReader(MS);
// ============== VARS ==============

void setup() {
  // Init serial
  Serial.begin(SPEED_SERIAL);
  Serial.println();
  
  pinMode(SOIL_SENSOR_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
}

void loop() {
  int value = get_soil_humidity();

  Serial.print("Humidity in soil: ");
  Serial.print(value);
  Serial.print("%");
  Serial.print(" is ");
  
  if (value < OPTIMAL_HUM && value >= 0) {
    Serial.println("dry");
    digitalWrite(PUMP_PIN, HIGH);
  }
  else if (value >= OPTIMAL_HUM) {
    Serial.println("wet");
    digitalWrite(PUMP_PIN, LOW);
  }
  else {
    Serial.println("undefined");
    digitalWrite(PUMP_PIN, LOW);
  }
  Serial.println("============================");
  
  delay(600);
}

int get_soil_humidity() {
  int value = 0;
  
  digitalWrite(SOIL_SENSOR_PIN, HIGH);
  delay(200);
  for (int i = 0; i < 10; i++) {
    value += analogRead(SOIL_SENSOR_OUTPUT);
    delay(100);
  }
  delay(200);
  digitalWrite(SOIL_SENSOR_PIN, LOW);

  return map((value/10.0), MAX_VALUE, MIN_VALUE, 0, 100);
}
