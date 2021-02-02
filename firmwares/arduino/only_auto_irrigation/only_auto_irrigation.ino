// Soil Humidity Settings
#define soil_sensor_output A0
#define soil_sensor_pin 2
#define dry 600
#define wet 230
#define threshold 60 // threshold for all flowers (average)

// Pump Settings
#define pump_pin 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(soil_sensor_pin, OUTPUT);
  pinMode(pump_pin, OUTPUT);
}

void loop() {
  int value = get_soil_humidity();

  Serial.print("Humidity in soil: ");
  Serial.print(value);
  Serial.print("%");
  Serial.print(" is ");
  if (value < threshold && value >= 0) {
    Serial.println("dry");
    digitalWrite(pump_pin, HIGH);
  }
  else if (value >= threshold) {
    Serial.println("wet");
    digitalWrite(pump_pin, LOW);
  }
  else {
    Serial.println("undefined");
    digitalWrite(pump_pin, LOW);
  }
  Serial.println("============================");
  
  delay(600);
}

int get_soil_humidity() {
  return map(get_value_soil(), dry, wet, 0, 100);
}

float get_value_soil() {
  int value = 0;
  
  digitalWrite(soil_sensor_pin, HIGH);
  delay(200);
  for (int i = 0; i < 10; i++) {
    value += analogRead(A0);
    delay(100);
  }
  delay(200);
  digitalWrite(soil_sensor_pin, LOW);

  return (value/10.0);
}
