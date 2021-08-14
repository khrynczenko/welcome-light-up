// This program requires manual adjustment of the time delay for the movement sensor HC-SR501.
// The diode will light up as long as the sensor outputs HIGH one and the voltage drop on the
// photoresistor indicates that it is dark in the room.

#define PIN_LED_OUT 8
#define PIN_PIR_IN 9
#define PIN_PHOTO_IN A0

const int LIGHT_UP_PERIOD_MS = 5000;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_OUT, OUTPUT);
  pinMode(PIN_PIR_IN, INPUT);
  digitalWrite(PIN_LED_OUT, LOW);
}

bool is_dark() {
  int photo_analog_read = analogRead(PIN_PHOTO_IN);
  int photo_voltage_read = map(photo_analog_read, 0, 1023, 0, 500);
  Serial.print("Analog read: = ");
  Serial.print(photo_analog_read);
  Serial.print("\n");
  Serial.print("Voltage read: = ");
  Serial.print(photo_voltage_read);
  Serial.print("\n");
  return photo_voltage_read > 450;
}

bool is_movement_detected() {
  byte pir_read = digitalRead(PIN_PIR_IN);
  Serial.print("Movemented detected: = ");
  Serial.print(pir_read);
  Serial.print("\n");
  return pir_read == 1;
}

void turn_light(bool on) {
  if (on) {
    digitalWrite(PIN_LED_OUT, HIGH);
  } else {
    digitalWrite(PIN_LED_OUT, LOW);
  }
}

void loop() {
  while (is_movement_detected() && is_dark()) {
    turn_light(true);
  }
  turn_light(false);

}
