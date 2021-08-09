#define PIN_DIODE_OUT 8
#define PIN_PIR_IN 9
#define PIN_PHOTO_IN A0


void setup() {
  Serial.begin(9600);
  pinMode(PIN_DIODE_OUT, OUTPUT);
  pinMode(PIN_PIR_IN, INPUT);
  digitalWrite(PIN_DIODE_OUT, HIGH);
}

bool is_dark(int voltage_read) {
  return voltage_read > 470;
}

void turn_light(bool on) {
  if(on) {
    digitalWrite(PIN_DIODE_OUT, HIGH);
  } else {
    digitalWrite(PIN_DIODE_OUT, LOW);
  }
}

void loop() {
  int analog_read = analogRead(PIN_PHOTO_IN);
  int voltage = map(analog_read, 0, 1023, 0, 500);
  turn_light(is_dark(voltage));
  Serial.print("Analog read: = ");
  Serial.print(analog_read);
  Serial.print("\n");
  Serial.print("Voltage read: = ");
  Serial.print(voltage);
  Serial.print("\n");
  Serial.print("Movemented detected: = ");
  Serial.print(digitalRead(PIN_PIR_IN));
  Serial.print("\n");
  delay(500);
}
