/*
  Скетч для проекта "Smart Climate"
  Исходный код на GitHub: https://github.com/DragonNP/smart-climate
  Автор: DragonNP, 2021
  https://github.com/DragonNP/
*/

// ============ НАСТРОЙКИ ===========
// -------- ДАТЧИК ВЛАЖНОСТИ --------
#define OPTIMAL_HUM 60               // Заначние при котором будет включать пома
#define SOIL_SENSOR_OUTPUT A0        // Пин на котором находится питание для датчика
#define SOIL_SENSOR_PIN 2            // Пин с которого будут считываться данные
#define MIN_VALUE 240                // Мин. значение датчика в воде
#define MAX_VALUE 710                // Макс. значение датчика на воздухе

// -------------- ПОМПА -------------
#define PUMP_PIN 3                   // Пин на котором находится питание для помпы

//-------------- SERIAL -------------
#define SPEED_SERIAL 9600
// ============ НАСТРОЙКИ ===========

void setup() {
  // Init serial
  Serial.begin(SPEED_SERIAL);
  Serial.println();
  
  pinMode(SOIL_SENSOR_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
}

void loop() {
  int value = get_soil_humidity();

  Serial.print("Влажность в почве: ");
  Serial.print(value);
  Serial.print("%");
  Serial.print(" это ");
  
  if (value < OPTIMAL_HUM && value >= 0) {
    Serial.println("сухо");
    digitalWrite(PUMP_PIN, HIGH);
  }
  else if (value >= OPTIMAL_HUM) {
    Serial.println("влажно");
    digitalWrite(PUMP_PIN, LOW);
  }
  else {
    Serial.println("не определено");
    digitalWrite(PUMP_PIN, LOW);
  }
  Serial.println("============================");
  
  delay(600 + 58000 + 1740000);
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
