#include <TinyGPS++.h>
#include <heltec.h>
#include "DHT.h"

// Definir pines y configuraciones
const int GPS_RX_PIN = 21;
const int GPS_TX_PIN = 22;
const int DHTPIN = 13;
#define DHTTYPE DHT11

HardwareSerial SerialGPS(1);
TinyGPSPlus gps;
DHT dht(DHTPIN, DHTTYPE);

String temperatura = "";
String humedad = "";
String latitud = "";
String longitud = "";
String voltaje_bateria = "";
String voltaje_entrada = "";


//Establecimiento de la banda y el factor de dispersión LoRa.
#define BAND 915E6
byte spread_factor = 8;

//Definir Direcciones en un sistema de comunicación
byte dir_local = 0xD1;
byte dir_destino = 0xC1;


byte id_msjLoRa = 0;
String paqueteEnv = "";

long tiempo_antes = 0;
long tiempo_intervalo = 30000;
long tiempo_espera = tiempo_intervalo + random(3000);

float prev_latitude = 0.0;
float prev_longitude = 0.0;

float XS = 0.0025;  
uint16_t MUL = 1000;
uint16_t MMUL = 100;

void setup() {
  Heltec.begin(true, true, true, true, BAND);
  LoRa.setSpreadingFactor(spread_factor);
  Serial.begin(9600);
  SerialGPS.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  dht.begin();
  LoRa.receive();
  //Heltec.display->init();
  //Heltec.display->flipScreenVertically();
}

void loop() {
  float latitude = 0.0;
  float longitude = 0.0;
  float speed = 0.0;
  int hour = 0;
  int minute = 0;
  int second = 0;

  // Leer datos del GPS
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      if (gps.location.isUpdated()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        speed = gps.speed.kmph();
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second();

        // Actualizar los valores de longitud y latitud solo si no son cero
        if (latitude != 0.0) {
          prev_latitude = latitude;
        }
        if (longitude != 0.0) {
          prev_longitude = longitude;
        }
      }
    }
  }

  // Leer datos del sensor DHT11
  sensorLeeDHT();

  // Medir el voltaje
  uint16_t c1 = analogRead(37) * XS * MUL;
  uint16_t c2 = analogRead(36) * 0.769 + 150;

  // Actualizar los valores de voltaje
  voltaje_bateria = String(c1) + " mV";
  voltaje_entrada = String(c2) + " mV";

  // Formar el paquete a enviar por LoRa
  paqueteEnv = "{\"Latitud\":" + String(prev_latitude, 6) + ",\"Longitud\":" + String(prev_longitude, 6) + ",\"Temperatura\":" + temperatura + ",\"Humedad\":" + humedad + ",\"Voltaje_Bateria\":" + voltaje_bateria + ",\"Voltaje_Entrada\":" + voltaje_entrada + "}";

  // Enviar por LoRa
  envia_lora(dir_destino, dir_local, id_msjLoRa, paqueteEnv);
  id_msjLoRa++;

  // Mostrar datos en el monitor serial
  if (Serial) {
    Serial.println(paqueteEnv);
  }

  // Mostrar datos en la pantalla Heltec
  displayData(temperatura, humedad, prev_latitude, prev_longitude, voltaje_bateria, voltaje_entrada);

  // Actualizar tiempos para próxima transmisión
  tiempo_antes = millis();
  tiempo_espera = tiempo_intervalo + random(3000);

  if (LoRa.parsePacket()) {
    // Procesar mensajes LoRa recibidos si es necesario
  }
}

void envia_lora(byte destino, byte remite, byte id, String mensaje) {
  LoRa.beginPacket();
  LoRa.write(destino);
  LoRa.write(remite);
  LoRa.write(id);
  LoRa.write(mensaje.length());
  LoRa.print(mensaje);
  LoRa.endPacket();
}

void sensorLeeDHT() {
  humedad = String(int(dht.readHumidity()));
  temperatura = String(dht.readTemperature());
}

void displayData(String temp, String hum, float lat, float lon, String vbat, String vin) {
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_CENTER);
  Heltec.display->drawString(64, 0, "GPS Data");
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 10, "Voltaje Bateria:");
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 10, vbat);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 20, "Temperatura:");
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 20, temp + " C");
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 30, "Humedad:");
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 30, hum + " %");
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 40, "Latitud:");
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 40, String(lat, 6));
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 50, "Longitud:");
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 50, String(lon, 6));
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 70, "Voltaje Entrada:");
  Heltec.display->setTextAlignment(TEXT_ALIGN_RIGHT);
  Heltec.display->drawString(128, 70, vin);
  Heltec.display->display();
}
