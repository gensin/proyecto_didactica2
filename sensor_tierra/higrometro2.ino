int dryValue = 1023;
//obtenemos un 1023 con el higrometro entre arroz o en el aire
//obtenemos 175 con el higrómetro sumergido en agua
//obtenemos 266 con el higrómetro estabilizado sumergido en tierra húmeda
int wetValue = 0;
int friendlyDryValue = 0;
int friendlyWetValue = 100;
void setup() {
  Serial.begin(9600);
}
void loop() {
  int rawValue = analogRead(A0);
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.println(" | ");
  
  int friendlyValue = map(rawValue, dryValue, wetValue, friendlyDryValue, friendlyWetValue);
  
  Serial.print("Friendly: ");
  Serial.print(friendlyValue);
  Serial.println("%");
  
  delay(2000);
}
