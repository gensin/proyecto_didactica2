//Librerias================================================================================================
#include <Wire.h>
#include "RTClib.h"  //Reloj
RTC_DS3231 rtc;

#include "DHT.h"  //Sensor temperatura ambiente
#define DHTTYPE DHT11


//Definición de parametros de configuración y variables del entorno del invernadero========================

//FRECUENCIAS DE MUESTREO
//Frecuencia de muestreo de temperatura ambiente (sg)
const float Frec_Temperatura_Ambiente=10000;
//Frecuencia de muestreo de la humedad de la tierra (sg)
const float Frec_Humedad_Tierra=10000;
//Frecuencia de muestreo de la luz ambiente (sg)
const float Frec_Luz=10000;

//UMBRALES
//Umbrales temperatura ambiente en grados ºC
const float Tmprtr_Ambiente_Min=20.0;
const float Tmprtr_Ambiente_Max=27.0;
//Umbrales Humedad de la tierrra en %
const int Humedad_Tierra_Min=40;
const int Humedad_Tierra_Max=80;
//Umbrales Luz ambiente 
const int Luz_Ambiente_Min=200;

//PERIODOS HORARIOS
//Momento de comienzo del día para el intervalo diurno
const int Inicio_Intervalo_Diurno_Horas=8;
const int Inicio_Intervalo_Diurno_Minutos=0;
//Momento de finalización del día para el intervalo diurno
const int Fin_Intervalo_Diurno_Horas=20;
const int Fin_Intervalo_Diurno_Minutos=0;

//Pines de conexión a Arduino
const int BOMBA_AGUA = 12 ; 
const int MOTOR_VENTILADOR = 10 ;

const int TEMP_HUM_AMBIENTE = 5; //DHT11
const int SENSOR_LUZ = A0; // fotoresistor 
const int HIGROMETRO = A1; // sensor humedad tierra
const int BOMBILLA_LUZ = 11;
const int BOMBILLA_CALOR = 9;
DHT dht(TEMP_HUM_AMBIENTE, DHTTYPE); 




//Gestion del sensor de Humedad, mapeo a %
//obtenemos un 1023 con el higrometro entre arroz o en el aire
//obtenemos 175 con el higrómetro sumergido en agua
//obtenemos 266 con el higrómetro estabilizado sumergido en tierra húmeda
int dryValue = 1023;
int wetValue = 0;
int friendlyDryValue = 0;
int friendlyWetValue = 100;


//Inicialización de variables de lectura de los sensores:
float Tmprtr_Ambiente=0;
int Humedad_Tierra=0;
int Luz_Ambiente=0;

//Funcion de iniciacion de variables=======================================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Activacion puertos Arduino
     //ACTUADORES
   pinMode(MOTOR_VENTILADOR,  OUTPUT) ;
   pinMode(BOMBA_AGUA,  OUTPUT) ;
   pinMode(BOMBILLA_CALOR,  OUTPUT) ;
   pinMode(BOMBILLA_LUZ,  OUTPUT) ;
     //SENSORES
   pinMode(SENSOR_LUZ, INPUT);
   pinMode(TEMP_HUM_AMBIENTE, INPUT);
   pinMode(HIGROMETRO, INPUT);

    
   dht.begin(); //sensor temperatura


   //Ajuste de reloj
   if (!rtc.begin()) {
      Serial.println(F("Couldn't find RTC"));
      while (1);
   }
 
   if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }

   
}

//FUNCIONES DE LECTURA DE SENSORES========================================================================
//Función lectura de luz
int leer_sensor_luz(){
  
  Luz_Ambiente = analogRead(SENSOR_LUZ);
  Serial.print("Valor fotorresistor: ");  //observaciones: mucha luz cuando "Luz_Ambiente" > 
  Serial.print(Luz_Ambiente);
  Serial.println(" ");
  return Luz_Ambiente;
  
}

//Función lectura de humedad
int leer_humedad(){
  int rawValue = analogRead(HIGROMETRO);
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.println(" | ");
  
  Humedad_Tierra = map(rawValue, dryValue, wetValue, friendlyDryValue, friendlyWetValue);
  
  Serial.print("Humedad tierra: ");
  Serial.print(Humedad_Tierra);
  Serial.println(" %");
  return Humedad_Tierra;
}


//Función lectura de temperatura
float leer_temperatura(){
  //meter el código para leer el sensor de temperatura ambiente

   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();
 
   if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
 
 
   Serial.print("Humidity: ");
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.print(" *C ");
   Serial.println("");
   

  return t;
}




//FUNCIONES PARA LOS ACTUADORES=============================================================================
//Función para encender el ventilador
void encender_ventilador(){
  
        digitalWrite(MOTOR_VENTILADOR, HIGH);
         Serial.println ("ventilador ON");
        //Dejamos el ventilador encendido
        
}

//Función para apagar el ventilador
void apagar_ventilador(){
  
        digitalWrite(MOTOR_VENTILADOR, LOW);
         Serial.println ("ventilador OFF");
         
}

//Función para encender la bombilla infrarrojos
void encencer_bombilla_calentadora(){
  //meter el código de activación de la bombilla infrarrojos
  digitalWrite(BOMBILLA_CALOR, LOW); //Enciendo la bombilla para calentar
}
//Función para apagar la bombilla infrarrojos
void apagar_bombilla_calentadora(){
  //meter el código de apagado de la bombilla infrarrojos
  digitalWrite(BOMBILLA_CALOR, HIGH);
}

//Función para activar el riego
void activar_riego(){
   
        digitalWrite(BOMBA_AGUA, HIGH);
        Serial.println("Riego ON");
        delay(6000); //¿hasta que suba la humedad?
               
}
void apagar_riego(){
   
        digitalWrite(BOMBA_AGUA, LOW);
        Serial.println("Riego OFF");
          
}

//Función para activar/desactivar la luz ambiente
void dar_luz(){
  //meter el código de activación de la bombilla lumínica
     digitalWrite(BOMBILLA_LUZ, LOW);
}
void apagar_luz(){
   //meter el código de apagar la bombilla lumínica 
   digitalWrite(BOMBILLA_LUZ, HIGH);
}



//FUNCIONES PARA EL TRATAMIENTO DE LOS VALORES DE LOS SENSORES============================================
//Función para tratar la temperatura
void tratar_temperatura(float Tmprtr_Ambiente) {

  if (Tmprtr_Ambiente > Tmprtr_Ambiente_Max) {
    //Activamos el ventilador 
    encender_ventilador(); 
  }
  else apagar_ventilador();
  
  if (Tmprtr_Ambiente < Tmprtr_Ambiente_Min) {
    //Activamos la bombilla infrarrojos para calentar
    encencer_bombilla_calentadora();
  }
  else apagar_bombilla_calentadora();
}

//Función para tratar la humedad
void tratar_humedad(int Humedad_Tierra) {

  if (Humedad_Tierra < Humedad_Tierra_Min) {
    //Activamos el riego 
        activar_riego(); 
  }
  //¿Vamos a hacer algo si está muy húmeda?
  else apagar_riego();
    
}

//Función para tratar la luminosidad
void tratar_luz(int Luz_Ambiente, DateTime hora) {
 
  if (Luz_Ambiente < Luz_Ambiente_Min) {
    //Encender bombilla luz sólo si hay poca luz y estoy dentro de la franja horaria de LUZ
    //Ver definicion de PERIODOS HORARIOS
    
   float hours = hora.hour()*60 + hora.minute();
   float minutosInicio = Inicio_Intervalo_Diurno_Horas*60 + Inicio_Intervalo_Diurno_Minutos;
   float minutosFinal = Fin_Intervalo_Diurno_Horas*60 + Fin_Intervalo_Diurno_Minutos;
   //Si nos encontramos dentro del periodo en el que debiera haber luz y no la hay, enciendo la bombilla luz
   if ((hours >  minutosInicio) && (hours < minutosFinal))
   {
        dar_luz(); 
   }
   else apagar_luz();
  }
  else apagar_luz();
  
}



void printDate(DateTime date)
{
   Serial.print(date.day(), DEC);
   Serial.print('/');
   Serial.print(date.month(), DEC);
   Serial.print('/');
   Serial.print(date.year(), DEC);
   Serial.print('--');
   Serial.print(date.hour(), DEC);
   Serial.print(':');
   Serial.print(date.minute(), DEC);
   Serial.print(':');
   Serial.print(date.second(), DEC);
   Serial.println();
} 

//BUCLE PRINCIPAL ==================================================================================
void loop() {
  // Mejora propuesta: leer cuando nos indique los temporizadores definidos en el apartado "FRECUENCIAS DE MUESTREO"
   
    //creo una variable llamada "now" que me da la hora actual que lee del reloj
    // me servirá para saber si estoy en periodo horario nocturno o diurno y saber si tengo que iluminar si hay poca luz (y es de día)
   DateTime now = rtc.now();  
   printDate(now);

   delay(6000);

int Luz_Ambiente=leer_sensor_luz();
  tratar_luz(Luz_Ambiente, now);

int Humedad_Tierra=leer_humedad();
  tratar_humedad(Humedad_Tierra);

float Tmprtr_Ambiente=leer_temperatura();
  tratar_temperatura(Tmprtr_Ambiente);



}
