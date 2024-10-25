// Proyecto: Monitoreo de Humedad en Invernadero de Germinación con ESP32
// Autor: [Tu Nombre]
// Fecha: [Fecha Actual]

// Librerías necesarias
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Credenciales de la red Wi-Fi
const char* ssid     = "Tu_SSID";
const char* password = "Tu_Contraseña";

// Configuración del cliente NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // Sin zona horaria, actualiza cada minuto

// Número de sensores conectados
const int numSensores = 7;

// Pines analógicos donde están conectados los sensores
const int pinesSensores[numSensores] = {34, 35, 32, 33, 25, 26, 39};

// Arreglo para almacenar las lecturas de los sensores
int valoresSensores[numSensores];

// Variables para definir los límites de seco y húmedo para cada sensor (para calibración posterior)
// int valorSeco[numSensores];   // Valor cuando el suelo está completamente seco
// int valorHumedo[numSensores]; // Valor cuando el suelo está completamente húmedo

// Variables para el control del tiempo sin usar funciones bloqueantes
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 500; // Intervalo de X segundos

// Función para conectar a la red Wi-Fi
void conectarWiFi() {
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConexión Wi-Fi exitosa");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nNo se pudo conectar a la red Wi-Fi");
  }
}

void setup() {
  // Iniciar comunicación serial a 115200 baudios
  Serial.begin(115200);

  // Configurar la resolución del ADC a 12 bits (0 - 4095)
  analogReadResolution(12);

  // Conectar a la red Wi-Fi
  conectarWiFi();

  // Iniciar el cliente NTP
  timeClient.begin();

  // Esperar a que se sincronice la hora
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
}

void loop() {
  unsigned long tiempoActual = millis();

  // Actualizar la hora cada minuto
  if (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;

    // Obtener la hora actual
    String horaActual = timeClient.getFormattedTime();

    // Leer y mostrar los valores de cada sensor
    for (int i = 0; i < numSensores; i++) {
      valoresSensores[i] = analogRead(pinesSensores[i]);

      // Mostrar el número de sensor, su valor leído y la hora en el Monitor Serial
      Serial.print("Hora: ");
      Serial.print(horaActual);
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


