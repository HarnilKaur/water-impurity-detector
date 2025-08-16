const int photo_diode = 34;
const int buzzerPin = 25;
const int threshold = 1010;

const int filterStrength = 10;
int adc_history[filterStrength] = {0};  // Correct variable name

int lowPassFilter(int newReading) {
  for (int i = filterStrength - 1; i > 0; i--) {
    adc_history[i] = adc_history[i - 1];  // Corrected variable name
  }
  adc_history[0] = newReading;

  int sum = 0;
  for (int i = 0; i < filterStrength; i++) {
    sum += adc_history[i];
  }

  return sum / filterStrength;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  int input_val = analogRead(photo_diode);
  int adc_val = lowPassFilter(input_val);  // Declare adc_val

  Serial.print(currentTime);
  Serial.print(",");
  Serial.println(adc_val);

  delay(200);
}
