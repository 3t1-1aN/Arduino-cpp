const int sensorPin = A0;       // ACS712 connected to analog pin A0
const float VREF = 5.0;         // Arduino reference voltage
const int ADC_RES = 1023;       // 10-bit ADC resolution (0–1023)
const float SENSITIVITY = 0.185; // V/A (for ACS712-5A; change for 20A/30A)

float voltageOffset; // baseline voltage at 0 A

void setup() {
  Serial.begin(9600);

  // --- Calibration (find zero-current offset) ---
  long sum = 0;
  for (int i = 0; i < 2000; i++) {
    sum += analogRead(sensorPin);
  }
  float average = sum / 2000.0;
  voltageOffset = (average * VREF) / ADC_RES;
}

void loop() {
  // Read raw ADC and convert to voltage
  int raw = analogRead(sensorPin);
  float voltage = (raw * VREF) / ADC_RES;

  // Calculate difference from baseline
  float voltageDiff = voltage - voltageOffset;

  // Convert to current (A)
  float current = voltageDiff / SENSITIVITY;

  Serial.print("Current: ");
  Serial.print(current, 3); // show 3 decimal places
  Serial.println(" A");

  delay(500);
}
