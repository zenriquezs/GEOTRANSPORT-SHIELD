#include "heltec.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "images.h"

//Establecimiento de la banda y el factor de dispersión LoRa.
#define BAND 915E6  
byte spread_factor = 8;

// LoRa Mensaje a enviar por direcciones
String paqueteEnv = "";   // Contenido del mensaje a enviar
byte dir_local = 0xc1;    // Concentrador 1 Direccion
byte dir_destino = 0xFF;  // Dispositivo 1 destinatario
byte msjContador = 0;     // identificador de mensaje
// tiempo entre lecturas
long t_anterior = 0;
int t_intervalo = 3000;

// LoRa Mensaje Recibido
byte dir_envio = 0xC1;         // Concentrador 1 de origen
int dir_remite = 0xD0;         // Inicia Remitente de mensaje
String paqueteRcb = "";        // Contenido del mensaje recibido
String newPaquetesReceb = "";  // Nuevo contenido del mensaje recibido después de ser procesado
byte paqrcbID = 0;             // ID del mensaje recibido
byte paqrcbEstado = 0;
// 0:vacio, 1: nuevo, 2:incompleto
// 3:otro destinatario, 4:Broadcast

// Mensajes por Puerto Serial
volatile boolean serial_msj = true;  // Variable para habilitar o deshabilitar mensajes por el Puerto Serial

char* ssid = "AccessPoint_2.4";  // WIFI: conexión a Router o Punto de anclaje
char* password = "12345678"; 
char* MQTT_IP = "192.168.0.103";   // Direccion ip del servidor MQTT
uint16_t MQTT_puerto = 1883;        // Puerto del servidor
char* MQTT_usuario = "UserItsoeh";  // Usuario para autenticarse en el servidor MQTT.
char* MQTT_contrasena = "Clave";    // Contraseña para autenticarse en el servidor MQTT.

// MQTT: Dispositivo Sensor topicos configuracion
//LoRa_D3/Biodigestor
char* MQTT_ID = "Gestore";                      //Identificador del cliente MQTT.
char MQTT_TOPIC_D1[50] = "LoRa_D1/GPS_Kikiza";          //Tópico MQTT para la temperatura.
char MQTT_TOPIC_D2[50] = "LoRa_D2/Aquajet";          //Tópico MQTT para voltaje
char MQTT_TOPIC_D3[50] = "LoRa_D3/Biodigestor";  //Tópico MQTT para lora D3.
char MQTT_TOPIC_D4[50] = "LoRa_D4/Cultivos";          //Tópico MQTT para la humedad
char MQTT_TOPIC_D5[50] = "LoRa_D5/GPS_Animal";          //Tópico MQTT para la humedad
//char MQTT_TOPIC_V[50] = "biodigestor/loraD1/voltaje"; // : Tópico MQTT para voltaje
char MQTT_SensorEstado[10] = "OFF";         // Estado del sensor MQTT.
volatile boolean mqtt_desconectado = true;  // : Indica si el cliente MQTT está desconectado.

// MQTT: Dispositivo Actuador
char* MQTT_COMMAND = "Lora_D-/cambia";      //Comando MQTT para cambiar algo en el dispositivo.
char MQTT_ActuadorEstado[10] = "OFF";       // Estado del actuador MQTT.
volatile boolean actuador_estado = false;   // Indica el estado del actuador.
volatile boolean actuador_bandera = false;  // Bandera que indica si se debe activar el actuador.

// Clientes WiFi y MQTT
WiFiClient wificlient;
PubSubClient mqttclient(wificlient);

String topico = "";

// parametros de recepción
  int rssi_lora = 0;
  int snr_lora = 0;

void logo(){
	Heltec.display -> clear();
	Heltec.display -> drawXbm(0,5,logo_width,logo_height,(const unsigned char *)logo_bits);
	Heltec.display -> display();
}

void Presentacion(){
  Heltec.display -> clear();
  Heltec.display -> drawString(2, 10, "Conexion con pantalla OK");
  Heltec.display ->drawString(2, 20, "Direccion local: " + String(dir_local, HEX));
  Heltec.display -> display();
}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/,
               true /*Heltec.Heltec.Heltec.LoRa Disable*/,
               serial_msj /*Serial Enable*/,
               true /*PABOOST Enable*/,
               BAND /*long BAND*/);


  // ranges from 6-12,default 7 see API docs
  LoRa.setSpreadingFactor(spread_factor);

  //LoRa.onReceive(cbk);
  LoRa.receive();

  // Display
  Heltec.display->init(); 
  logo();
  delay(1500);
  Presentacion();
  delay(1000);

  // conexión WIFI y MQTT
  inicia_wifi();  // establecer la conexión WiFi
  if (WiFi.status() == WL_CONNECTED) {
    inicia_mqtt();
    delay(500);
    inicia_mqtt();
  }  // Verifica si el dispositivo está conectado a la red WiFi
  Heltec.display -> clear();
}

void loop() {
  ///////////////////////////////////// Revisa mensajes LoRa entrantes////////////////////////////////////

  // Revisión de mensajes LoRa entrantes
  int msjRcbLoRa = LoRa.parsePacket();

  //Serial.println(msjRcbLoRa);
  if (msjRcbLoRa != 0) {
    // Procesamiento del mensaje LoRa recibido
    recibirlora(msjRcbLoRa);
    rssi_lora = LoRa.packetRssi();
    snr_lora = LoRa.packetSnr();

    // Impresión de detalles del mensaje LoRa recibido
    if (serial_msj == true) {
      Serial.println("remite,msjID,mensaje,estado,Rssi,Snr");
      Serial.print(String(dir_remite, HEX));
      Serial.print(",");
      Serial.print(paqrcbID);
      Serial.print(",");
      Serial.print(paqueteRcb);
      Serial.print(",");
      Serial.print(paqrcbEstado);
      Serial.print(",");
      Serial.print(rssi_lora);
      Serial.print(",");
      Serial.println(snr_lora);
    }
    yield();  // procesa wifi

    // LED parpadea Rebibido Lora
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
    yield();  // procesa wifi

    //Mostrar dato en pantalla
        pantalla_Mostrar();
        Heltec.display -> display();
  }
  /////////////////////// Procesa a MQTT mensaje completo////////////////////////////

  if (msjRcbLoRa != 0 && paqrcbEstado == 1) {

    // Añade el dispositivo a los tópicos MQTT
    String remite = String(dir_remite, HEX);
    remite.toUpperCase();

    // Realizar la comparación con una serie de if-else
    if (remite == "D1") {
      topico = MQTT_TOPIC_D1;
    } else if (remite == "D2") {
      topico = MQTT_TOPIC_D2;
    } else if (remite == "D3") {
      topico = MQTT_TOPIC_D3;
    } else if (remite == "D4") {
      topico = MQTT_TOPIC_D4;
    } else if (remite == "D5") {
      topico = MQTT_TOPIC_D5;
    }

    Serial.println(topico);

    // Publica los valores de Humedad, CO, Metano y Temperatura en el broker MQTT.
    publica_estado();
    Heltec.display->drawString(2, 42, "Topic update: ");
    Heltec.display->drawString(12, 52,  topico);
    Heltec.display -> display();
    Serial.println("--------------------------------------------------------------------------");  //paqueteRcb
  }
  yield();  // procesa wifi
  delay(20);

  ///////////////////////////////////// reenviar a dispositivo//////////////////////////////////
  if (actuador_bandera == true) {
    msjContador = msjContador + 1;
    enviarlora(dir_destino, dir_local,
               msjContador, paqueteEnv);
    actuador_bandera = false;
  }
  yield();  // procesa wifi
  delay(20);

  if (WiFi.status() != WL_CONNECTED) {
    inicia_wifi();
  } else {
    if (mqttclient.connected() == false) {
      mqtt_desconectado = true;
      inicia_mqtt();  // reintento
    }
    if (mqttclient.connected() == true) {
      if (mqtt_desconectado == true) {
        publica_estado();
        mqtt_desconectado = false;
      }
      mqttclient.loop();
    }
  }
  yield();  // procesa wifi
  Heltec.display->clear();
}

void publica_estado() {
  // Verifica si el cliente MQTT está conectado al broker.
  if (mqttclient.connected()==true){
  // Publica los valores en el broker MQTT.
  mqttclient.publish(topico.c_str(), paqueteRcb.c_str());
  mqttclient.subscribe(MQTT_COMMAND);
  }else{
  // Suscribe al comando MQTT para escuchar los cambios en el dispositivo.
  mqtt_desconectado = true;
  }
}

void enviarlora(byte destino, byte remite, byte paqueteID, String paquete) {
  // espera que el radio esté listo para enviar un paquete
  while (LoRa.beginPacket() == 0) {
    if (serial_msj == true) {
      Serial.println("Esperando radio disponible...");
    }
    yield();  // procesa wifi
    delay(100);
  }
  // Iniciar el paquete LoRa
  LoRa.beginPacket();
  // Escribir los datos en el paquete LoRa
  LoRa.write(destino);           //disp de destino
  LoRa.write(remite);            //disp que envia
  LoRa.write(paqueteID);         //Id de paquete unico
  LoRa.write(paquete.length());  //Long de datos
  LoRa.print(paquete);           //Escribir en paquete

  // Finalizar y enviar el paquete LoRa
  LoRa.endPacket();
}


void recibirlora(int tamano) {
  // Si el tamaño del paquete es 0, se considera como un paquete vacío
  if (tamano == 0) {
    paqrcbEstado = 0;  //vacio
    return;
  }

  // lectura de paquete
  paqueteRcb = "";           // Inicializar la cadena que almacenará el paquete recibido
  dir_envio = LoRa.read();   //Leer la dirección del dispositivo que envía
  dir_remite = LoRa.read();  //Leer la dirección del dispositivo remitente
  paqrcbID = LoRa.read();    //Leer el identificador único del paquete

  // Leer el tamaño esperado del paquete
  byte paqrcbTamano = LoRa.read();

  // Leer los datos del paquete mientras estén disponibles
  while (LoRa.available()) {
    paqueteRcb += (char)LoRa.read();
  }

  // Verificar si la longitud del paquete coincide con el tamaño esperado
  if (paqrcbTamano != paqueteRcb.length()) {
    paqrcbEstado = 2;  // Tamaño incompleto
    return;
  }

  // Verificar si el paquete fue destinado a otro dispositivo
  if (dir_envio != dir_local) {
    paqrcbEstado = 3;  // otro destino
    return;
  }

  // Verificar si el paquete es un mensaje de difusión (broadcast)
  if (dir_envio == 0xFF) {
    paqrcbEstado = 4;  // Broadcast
    return;
  }

  // Si no se cumple ninguna de las condiciones anteriores, se considera un mensaje nuevo
  paqrcbEstado = 1;  // mensaje Nuevo
}

void inicia_wifi(void) {
  int intentoswifi = 10;  // Número máximo de intentos de conexión
  int cuentawifi = 0;     // Contador de intentos de conexión

  Heltec.display->clear();
  Heltec.display->drawString(55, 10,  "WIFI");
  Heltec.display->drawString(10, 20,  "Reintentado conectar a:" );
  Heltec.display->drawString(60, 30, String(ssid));
  Heltec.display -> display();

  if (serial_msj) {  // Verifica si se deben imprimir mensajes en el puerto serial
    Serial.print(" WiFi Conectando a ");
    Serial.println(ssid);  // Imprime el nombre de la red WiFi a la que se está conectando
  }

  WiFi.disconnect(true);  // Desconecta cualquier conexión WiFi previa y borra las credenciales
  delay(1000);

  WiFi.mode(WIFI_STA);         // Configura el modo de WiFi como estación (WIFI_STA)
  WiFi.setAutoConnect(true);   // Activa la reconexión automática en caso de desconexión
  WiFi.begin(ssid, password);  // Intenta conectarse a la red WiFi especificada con las credenciales proporcionadas
  delay(100);

  // Bucle para esperar hasta que se establezca la conexión o se alcance el número máximo de intentos
  while (WiFi.status() != WL_CONNECTED && cuentawifi < intentoswifi) {
    if (serial_msj) {
      Serial.print(".");  // indicar que se esta intentado conectar
    }
    cuentawifi = cuentawifi + 1;
    // Parpadeo de Monitor Wifi
    digitalWrite(LED, HIGH);
    delay(300);
    digitalWrite(LED, LOW);
    delay(200);
  }
  if (serial_msj) {
    // mensaje a serial
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {  // Verifica si se ha establecido la conexión correctamente
      Serial.print(" Estado: ");
      Serial.println(WiFi.status());
      Serial.print(" MAC: ");
      Serial.println(WiFi.macAddress());
      Serial.print(" IP: ");
      Serial.println(WiFi.localIP());
      Serial.print(" RSSI: ");
      Serial.println(WiFi.RSSI());
      Serial.println();

      Presentacion();
      delay(500);
      Heltec.display ->drawString(5, 30, "* Conexion a WIFI OK ");
      Heltec.display -> display();
      delay(1500);
    }
    // Si no se ha podido establecer la conexión, imprime un diagnóstico de WiFi
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.printDiag(Serial);
      Serial.println();
    }
  }
}

void inicia_mqtt(void) {
  int intentosmqtt = 5;  // Número máximo de intentos de conexión MQTT
  int cuentamqtt = 0;    // Contador de intentos de conexión MQTT

  Heltec.display->clear();
  Heltec.display->drawString(50, 10,  "MQTT");
  Heltec.display->drawString(10, 20,  "Reintentado conectar a:" );
  Heltec.display->drawString(15, 30, String(MQTT_IP));
  Heltec.display -> display();

  if (serial_msj) {
    Serial.print(" MQTT Conectando a ");
    Serial.println(MQTT_IP);  // Imprime la dirección IP del servidor MQTT al que se está intentando conectar
  }

  mqttclient.setServer(MQTT_IP, MQTT_puerto);                  // Configura el servidor MQTT y el puerto
  mqttclient.connect(MQTT_ID, MQTT_usuario, MQTT_contrasena);  // Intenta conectar al servidor MQTT con el ID, usuario y contraseña especificados
  mqttclient.setCallback(recibirmqtt);                         // Establece la función de devolución de llamada para procesar mensajes MQTT entrantes

  // Bucle para intentar conectar al servidor MQTT
  while (!mqttclient.connected() && (cuentamqtt <= intentosmqtt)) {
    if (serial_msj) {
      Serial.print(".");
    }
    cuentamqtt = cuentamqtt + 1;
    // LED Monitor parpadeo MQTT
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
  // Publica el estado si se ha conectado al servidor MQTT
  if (mqttclient.connected()) {
    publica_estado();

    Presentacion();
    Heltec.display ->drawString(5, 30, "* Conexion a WIFI OK ");
    Heltec.display -> display();
    delay(500);
    Heltec.display ->drawString(5, 40, "* Conexion a MQTT OK ");
    Heltec.display -> display();
    delay(1500);
  }
  if (serial_msj) {
    //Fin de "...."
    Serial.println();
    Serial.print(" MQTT Conectado: ");
    Serial.print(mqttclient.connected());
    Serial.print("\t MQTT Estado: ");
    Serial.println(mqttclient.state());
  }
}

// llega mensaje MQTT, callback mqtt
void recibirmqtt(char* p_topic, byte* p_payload, unsigned int p_length) {
  Serial.println("un mensaje mqtt");
  Serial.println(p_topic);  // Imprime el tema del mensaje MQTT recibido

  // convierte a texto
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }
  // Extrae el identificador del dispositivo del tema del mensaje
  // String dispositivo = p_topic[16] + String(p_topic[17]);
  char dispositivo[3] = "D0";
  dispositivo[1] = p_topic[17];
  dir_destino = (int)strtol(dispositivo, NULL, 16);
  paqueteEnv = payload;
  actuador_bandera = true;

  // Suscribe al cliente MQTT al tema MQTT_COMMAND si está conectado, de lo contrario, establece la bandera de desconexión MQTT en verdadero
  if (mqttclient.connected() == true) {
    mqttclient.subscribe(MQTT_COMMAND);
  } else {
    mqtt_desconectado = true;
  }
}