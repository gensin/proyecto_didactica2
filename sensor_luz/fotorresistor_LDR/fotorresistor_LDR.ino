const int LEDPin = 13;
const int LDRPin = A0;
const int threshold = 700;
  
void setup()
{
pinMode(LEDPin, OUTPUT); 
pinMode(LDRPin, INPUT);
 // PREPARAR LA COMUNICACION SERIAL
  Serial.begin(9600);
  Serial.println("Prueba del fotorresistor");
} 
 
void loop()
{
  int value = analogRead(LDRPin);
  Serial.print("Valor fotorresistor: ");
  Serial.print(value);
  Serial.println(" ");
  //observaciones: mucha luz cuando "value" >700
   if (value < threshold) {
      digitalWrite(LEDPin, HIGH);
   }
   else {
      digitalWrite(LEDPin, LOW);
   }
  delay(2000);
 
}
