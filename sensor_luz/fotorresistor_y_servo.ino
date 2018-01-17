
#include <Servo.h>
const int LDRPin = A0;
const int threshold = 700;
Servo servoMotor;
  
void setup()
{

pinMode(LDRPin, INPUT);
servoMotor.attach(9);
 // PREPARAR LA COMUNICACION SERIAL
  Serial.begin(9600);
  Serial.println("Prueba del fotorresistor y servo");
 
    delay(1000);
  // Desplazamos a la posición 0º
  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
  
} 
 
void loop()
{
    
  int value = analogRead(LDRPin);
  Serial.print("Valor fotorresistor: ");
  Serial.print(value);
  Serial.println(" ");
  //observaciones: mucha luz cuando "value" >700
   if (value < threshold) {
       Serial.println("muevo a 90 ");
       servoMotor.write(90);
   }
   else {
       servoMotor.write(180);
        Serial.println("muevo a 180 ");
   }
  delay(2000);
 
}
