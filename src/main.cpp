// Proyecto: Monitoreo de Humedad en Invernadero de Germinación con ESP32
// Autor: [Tu Nombre]
// Fecha: [Fecha Actual]

// ** ESP32 tiene dos ADC. Usar los pines del ADC 1 si se utiliza el Wi-Fi, ya que  el ADC2 comparte pines con el WIfi. 
// Pines ADC1: 32 a 29. 
#include <Arduino.h>
//#include "secrets.h"

// Número de sensores conectados
const int numSensores = 5;

// Pines analógicos donde están conectados los sensores
const int pinesSensores[numSensores] = {36, 32, 33, 25, 26};

// Arreglo para almacenar las lecturas de los sensores
int valoresSensores[numSensores];

// Variables para definir los límites de seco y húmedo para cada sensor (para calibración posterior)
// int valorSeco[numSensores];   // Valor cuando el suelo está completamente seco
// int valorHumedo[numSensores]; // Valor cuando el suelo está completamente húmedo

// Variables para el control del tiempo sin usar funciones bloqueantes
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 2000; // Intervalo de X segundos

void setup() {
  // Iniciar comunicación serial a 115200 baudios
  Serial.begin(115200);

  // Configurar la resolución del ADC a 12 bits (0 - 4095)
  analogReadResolution(12);

  //analogSetPinAttenuation(pin, ADC_11db); // atenuación modifica el rango de voltaje que el ADC puede medir. Establece la atenuación para un pin específico
//analogSetCycles(64); // Valores entre 1 y 255. Aumentar el número de ciclos para reducir el ruido. 
//analogSetSamples(8); // Valores entre 1 y 255.  Incrementar el número de muestras para mejorar la sensibilidad.
//analogSetClockDiv(1); // Valores entre 1 y 255.  Puedes experimentar con este valor para reducir el ruido. Un valor mayor reduce la velocidad de muestreo.

  
}

void loop() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    
    // Leer y mostrar los valores de cada sensor
    for (int i = 0; i < numSensores; i++) {
      valoresSensores[i] = analogRead(pinesSensores[i]);

     
      Serial.print(" - Sensor ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(valoresSensores[i]);

      // Comentario para uso futuro: Mapear los valores leídos a porcentajes de humedad
      // int porcentajeHumedad = map(valoresSensores[i], valorSeco[i], valorHumedo[i], 0, 100);
      // Serial.print("Humedad: ");
      // Serial.print(porcentajeHumedad);
      // Serial.println("%");
    }
    Serial.println("---------------------------"); // Separador para mayor claridad
  }

  // Aquí puedes agregar más código que no bloquee el funcionamiento del programa
}


