//Definición de parametros de configuración y variables del entorno del invernadero

//FRECUENCIAS DE MUESTREO
//Frecuencia de muestreo de temperatura ambiente (sg)
const float Frec_Temperatura_Ambiente=10000;
//Frecuencia de muestreo de la humedad de la tierra (sg)
const float Frec_Humedad_Tierra=10000;
//Frecuencia de muestreo de la luz ambiente (sg)
const float Frec_Luz=10000;

//UMBRALES
//Umbrales temperatura ambiente en grados ºC
const int Tmprtr_Ambiente_Min=15;
const int Tmprtr_Ambiente_Max=25;
//Umbrales Humedad de la tierrra en %
const int Humedad_Tierra_Min=40;
const int Humedad_Tierra_Max=80;
//Umbrales Luz ambiente 
const int Luz_Ambiente_Min=700;

//PERIODOS HORARIOS
//Momento de comienzo del día para el intervalo diurno
const int Inicio_Intervalo_Diurno_Horas=8;
const int Inicio_Intervalo_Diurno_Minutos=0;
//Momento de finalización del día para el intervalo diurno
const int Fin_Intervalo_Diurno_Horas=20;
const int Fin_Intervalo_Diurno_Minutos=0;

//Inicialización de variables de lectura de los sensores:
int Tmprtr_Ambiente=0;
int Humedad_Tierra=0;
int Luz_Ambiente=0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

//FUNCIONES DE LECTURA DE SENSORES
//Función lectura de luz
int leer_sensor_luz(){
  //meter el código para leer el sensor de luz
}
//Función lectura de humedad
int leer_humedad(){
  //meter el código para leer el sensor de humedad de tierra
}
//Función lectura de temperatura
int leer_temperatura(){
  //meter el código para leer el sensor de temperatura ambiente
}




//FUNCIONES PARA LOS ACTUADORES
//Función para encender el ventilador
void encender_ventilador(){
  //meter el código de activación motor/ventilador
}

//Función para encender la bombilla infrarrojos
void encencer_bombilla_calentadora(){
  //meter el código de activación de la bombilla infrarrojos
}

//Función para activar el riego
void activar_riego(){
  //meter el código de activación de la BOMBA peristáltica o electrovalvula 
  
}

//Función para activar la luz ambiente
void dar_luz(){
  //meter el código de activación de la bombilla lumínica
}

//FUNCIONES PARA EL TRATAMIENTO DE LOS VALORES DE LOS SENSORES
//Función para tratar la temperatura
void tratar_temperatura(int Tmprtr_Ambiente) {

  if (Tmprtr_Ambiente > Tmprtr_Ambiente_Max) {
    //Activamos el ventilador 
    encender_ventilador(); 
  }
  if (Tmprtr_Ambiente < Tmprtr_Ambiente_Min) {
    //Activamos la bombilla infrarrojos para calentar
    encencer_bombilla_calentadora();
  }
}

//Función para tratar la humedad
void tratar_humedad(int Humedad_Tierra) {

  if (Humedad_Tierra < Humedad_Tierra_Min) {
    //Activamos el riego 
    activar_riego(); 
  }
  //¿Vamos a hacer algo si está muy húmeda?
    
}

//Función para tratar la luminosidad
void tratar_luz(int Luz_Ambiente) {

  if (Luz_Ambiente < Luz_Ambiente_Min) {
    //Encender bombilla luz 
    dar_luz(); 
  }
}





void loop() {
  // Habrá que modificar el bucle principal para leer cuando corresponda


int Luz_Ambiente=leer_sensor_luz();
  tratar_luz(Luz_Ambiente);

int Humedad_Tierra=leer_humedad();
  tratar_humedad(Humedad_Tierra);

int Tmprtr_Ambiente=leer_temperatura();
  tratar_temperatura(Tmprtr_Ambiente);



}
