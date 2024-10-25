#include <Arduino.h>
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

//void setup() {

// Conectar a la red Wi-Fi
  conectarWiFi();

  // Iniciar el cliente NTP
  timeClient.begin();

  // Esperar a que se sincronice la hora
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  //void loop*()


  // Actualizar la hora cada minuto
  if (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Obtener la hora actual
    String horaActual = timeClient.getFormattedTime();


 // Mostrar el número de sensor, su valor leído y la hora en el Monitor Serial
      Serial.print("Hora: ");
      Serial.print(horaActual);