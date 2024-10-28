// Proyecto: Monitoreo de Humedad en Invernadero de Germinación con ESP32
// Autor: [Tu Nombre]
// Fecha: [Fecha Actual]

#include <Arduino.h>
//#include "secrets.h"

// Número de sensores conectados
const int numSensores = 7;

// Pines analógicos donde están conectados los sensores
const int pinesSensores[numSensores] = {36, 35, 32, 33, 25, 26, 27};

// Arreglo para almacenar las lecturas de los sensores
int valoresSensores[numSensores];

// Variables para definir los límites de seco y húmedo para cada sensor (para calibración posterior)
// int valorSeco[numSensores];   // Valor cuando el suelo está completamente seco
// int valorHumedo[numSensores]; // Valor cuando el suelo está completamente húmedo

// Variables para el control del tiempo sin usar funciones bloqueantes
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 500; // Intervalo de X segundos

void setup() {
  // Iniciar comunicación serial a 115200 baudios
  Serial.begin(115200);

  // Configurar la resolución del ADC a 12 bits (0 - 4095)
  analogReadResolution(12);
  
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


