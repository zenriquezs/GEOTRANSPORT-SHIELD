# Proyecto de Monitoreo y Seguimiento de Transporte en Hidalgo(GeoTransport Shield)

## Descripción general
Este proyecto aborda la problemática del transporte en Hidalgo, específicamente en el Arco Norte, donde se ha observado un aumento alarmante en los incidentes de robo de carga en las carreteras estatales. Para contrarrestar esta situación, se implementa un sistema de monitoreo y seguimiento utilizando tecnologías inalámbricas.

## Tecnologías Utilizadas
- **Hardware:**
 - [Placa WiFi LoRa 32 (V3)](https://www.amazon.com/s?k=Placa+WiFi+LoRa+32+V3&ref=nb_sb_noss)
 -  [Módulo GPS Neo-6M](https://www.amazon.com/s?k=M%C3%B3dulo+GPS+Neo-6M&ref=nb_sb_noss)
 - [Sensor de temperatura y humedad DHT11](https://www.amazon.com/s?k=Sensor+de+temperatura+y+humedad+DHT11&ref=nb_sb_noss)
 -  [Raspberry Pi (Gateway)](https://www.amazon.com/s?k=Raspberry+Pi&ref=nb_sb_noss)

- **Software:**
 -  [ Arduino IDE](https://www.arduino.cc/en/software)
 -  [ Node-RED](https://nodered.org/docs/getting-started/local)
 - [ MQTT](https://mosquitto.org/download/)
 - [ InfluxDB](https://portal.influxdata.com/downloads/)
 - [ Grafana](https://grafana.com/get)

 
## Paletas de nodos Utilizadas en Node Red
- dashboard-evi 1.0.2
- node-red 3.0.2
- node-red-contrib-hostip 0.0.3
- node-red-contrib-influxdb 0.7.0
- node-red-contrib-lto-network 1.0.6
- node-red-contrib-unsafe-function 0.8.0
- node-red-contrib-web-worldmap 4.6.5
- node-red-contrib-whatsapp-cmb 1.0.2
- node-red-dashboard 3.6.5
- node-red-node-email 1.18.4
- node-red-node-exif 0.3.1
- node-red-node-serialport 1.0.3
- sense-neuralnetwork


## Configuraciónes importantes del Código (Transmisor)
### Descripción

Este archivo contiene el código fuente de un dispositivo IoT que utiliza tecnología LoRa para la comunicación inalámbrica , ademas de tener un Modulo GPS y un sensor DHT11 a lo cual el  módulo LoRa tiene la funcion de  enviar datos de ubicación, temperatura, humedad y voltaje a través de una red LoRa. Asimismo, muestra los datos en la  pantalla Heltec.

### Librerías Utilizadas en Arduino
- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
- [heltec.h](https://github.com/HelTecAutomation/Heltec_ESP32)
- [DHT.h](https://github.com/adafruit/DHT-sensor-library)

### Definiciones importantes

- **GPS_RX_PIN** y **GPS_TX_PIN**: Pines utilizados para la comunicación con el módulo GPS.
- **DHTPIN**: Pin utilizado para la comunicación con el sensor DHT11.
- **DHTTYPE**: Tipo de sensor DHT utilizado.
- **BAND**: Define la banda de frecuencia LoRa utilizada.
- **spread_factor**: Factor de esparcimiento LoRa.
- **dir_local** y **dir_destino**: Direcciones utilizadas en el sistema de comunicación LoRa.
- **tiempo_intervalo**: Intervalo de tiempo entre transmisiones de datos.

### Funciones importantes

- **setup()**: Inicializa el dispositivo y los sensores, y configura la comunicación LoRa.
- **loop()**: Bucle principal del programa que lee datos de los sensores, envía los datos por LoRa y muestra los datos en la pantalla Heltec.
- **envia_lora()**: Función para enviar datos por LoRa.
- **sensorLeeDHT()**: Lee los datos del sensor DHT11.
- **displayData()**: Muestra los datos en la pantalla Heltec.

## Configuración (Transmisor)
1. Configuración de los pines de comunicación serial para el GPS y el sensor DHT11.
![Configuración de los pines](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436235425_458887043334429_6840623238146122829_n.jpg?_nc_cat=110&ccb=1-7&_nc_sid=5f2048&_nc_ohc=33CE7Dai3KgQ7kNvgHPDgnY&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAUNXS31EZYtOr6iwII6J62bkRhA3AvdteHvx_Cm6nIrw&oe=6644A4EB)

2. Definir direcciones en un sistema de comunicación
![Direcciones](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436255367_458887033334430_6982264031401776534_n.jpg?_nc_cat=102&ccb=1-7&_nc_sid=5f2048&_nc_ohc=IrSg-5HfjX4Q7kNvgFuQSaF&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAaed5_TSmqaSHeJNsiLDPnbKccfeiRyYQKeSm0wW4N1w&oe=6644B107)

3. Establecimiento de la banda y el factor de dispersión LoRa.
![Establecimiento de la banda ](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436232622_458892376667229_3220963062338091565_n.jpg?_nc_cat=106&ccb=1-7&_nc_sid=5f2048&_nc_ohc=YJC-9mWhbIEQ7kNvgF4K4kz&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAE-eJwSnanmugVU1jXMb-amhHWpRuXKkNDfQIciDhAZw&oe=6644BDA5)

4. Recepción de datos del Módulo GPS Neo-6M y Sensor de temperatura y humedad DHT11.
![Recepción de datos ](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436255910_458888780000922_752188048744724611_n.jpg?_nc_cat=102&ccb=1-7&_nc_sid=5f2048&_nc_aid=0&_nc_ohc=PcbgnnOPdpIQ7kNvgGTPL-9&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYDqDSiQ1E-bQNng3w-JLSpI3D4tj-7eStghA7m_Ti99ag&oe=6644CFFE)

5. Carga el código en tu dispositivo.

## Configuraciónes importantes del Código (Receptor)
### Descripción

Este archivo contiene el código fuente de un dispositivo IoT que utiliza tecnología LoRa para la comunicación inalámbrica y MQTT para la comunicación con un servidor. El dispositivo está diseñado para enviar y recibir mensajes LoRa y publicar información en un servidor MQTT.

### Bibliotecas requeridas

- [heltec.h](https://github.com/HelTecAutomation/Heltec_ESP32)
- [WiFi.h](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [PubSubClient.h](https://github.com/knolleary/pubsubclient)

### Definiciones importantes

- **BAND**: Define la banda de frecuencia LoRa utilizada (en este caso, 915 MHz).
- **spread_factor**: Factor de esparcimiento LoRa.
- **ssid** y **password**: Credenciales de la red WiFi a la que se conectará el dispositivo.
- **MQTT_IP**, **MQTT_puerto**, **MQTT_usuario** y **MQTT_contrasena**: Configuración de conexión MQTT, incluida la dirección IP del servidor, el puerto, el nombre de usuario y la contraseña.
- **MQTT_TOPIC_D1**, **MQTT_TOPIC_D2**, etc.: Tópicos MQTT para diferentes dispositivos o sensores.
- **MQTT_COMMAND**: Comando MQTT para cambiar algo en el dispositivo.

### Funciones importantes

- **setup()**: Inicialización del dispositivo, configuración de LoRa, conexión WiFi y MQTT.
- **loop()**: Bucle principal del programa, que maneja la recepción de mensajes LoRa, la publicación de datos en MQTT y otras operaciones.
- **publica_estado()**: Publica los valores en el servidor MQTT.
- **enviarlora()**: Envía un mensaje LoRa al dispositivo especificado.
- **recibirlora()**: Procesa los mensajes LoRa entrantes.
- **inicia_wifi()**: Inicia la conexión WiFi.
- **inicia_mqtt()**: Inicia la conexión MQTT.

### Configuración (Receptor)
1. Establecimiento de la banda y el factor de dispersión LoRa.
![Establecimiento de la banda ](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436232622_458892376667229_3220963062338091565_n.jpg?_nc_cat=106&ccb=1-7&_nc_sid=5f2048&_nc_ohc=YJC-9mWhbIEQ7kNvgF4K4kz&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAE-eJwSnanmugVU1jXMb-amhHWpRuXKkNDfQIciDhAZw&oe=6644BDA5)

2. Definir direcciones en un sistema de comunicación
![Direcciones](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436255367_458887033334430_6982264031401776534_n.jpg?_nc_cat=102&ccb=1-7&_nc_sid=5f2048&_nc_ohc=IrSg-5HfjX4Q7kNvgFuQSaF&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAaed5_TSmqaSHeJNsiLDPnbKccfeiRyYQKeSm0wW4N1w&oe=6644B107)

3. Configura las credenciales de WiFi y MQTT según tu entorno.
![Configura las credenciales de WiFi y MQTT según tu entorno. ](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/435999918_458908796665587_6514518093115397567_n.jpg?_nc_cat=102&ccb=1-7&_nc_sid=5f2048&_nc_ohc=69YTRQbb1VwQ7kNvgHRLao7&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYBqywZn1dBsZvu258Iu_wYA77Nz0-9OvryqFF1FAnxTmw&oe=6644DBD7)

4. Carga el código en tu dispositivo.


##  Configuraciónes Node-Red
### Descripción
Este proyecto integra diversos nodos en Node-RED para monitorear y controlar sensores de temperatura y humedad, así como para visualizar los datos en un panel de control y enviar notificaciones en caso de valores fuera de rango.

## Configuraciones de nodos
![Nodos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436206065_458929326663534_5530785465182898519_n.jpg?_nc_cat=107&ccb=1-7&_nc_sid=5f2048&_nc_ohc=65-Ck9FfRrkQ7kNvgECBQOz&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYDnei1lZqut9QPFS_pJSZ1aN83jzxNl_h8GaGXIZmidlQ&oe=6644D7BA)
### MQTT In
- **Topic**: `<NOMBRE_DEL_TOPIC>` 
- **QoS**: 2
- **Broker**: `<ID_DEL_BROKER>`

### Funciones
- **Función Formato DHT11_HUMEDAD**: Extrae la humedad del mensaje recibido.
- **Función Formato GPS_Data**: Extrae la latitud y longitud del mensaje recibido.

### Visualización de datos
- **UI Gauge (Temperatura)**: Muestra la temperatura en grados Celsius.
- **UI Gauge (Humedad)**: Muestra el porcentaje de humedad.
- **Worldmap**: Muestra la ubicación en un mapa.

![DASHBOARD](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436270459_458930153330118_762916704406892469_n.jpg?_nc_cat=103&ccb=1-7&_nc_sid=5f2048&_nc_ohc=h0odaIv2zEUQ7kNvgFtr9en&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYB6n_uO4jU6mhT7TLg2Oa98hV8YSsbohtLAFRfXtze7Kg&oe=6644F2F7)
### Almacenamiento de datos
- **Función Guardar en Array (Temperatura/Humedad)**: Guarda los datos en un array para el historial.
- **UI Chart**: Muestra gráficos de la temperatura y humedad en tiempo real.

### Notificaciones
- **Función**: Envia notificaciones vía WhatsApp en caso de valores fuera de rango de temperatura y humedad.

## Instalación
1. Clona este repositorio.
2. Importa los codigos de Arduino(Transmisor y Receptor) y el flujo de Node-RED.
3. Configura los archivos .INO y el flujo con tus datos específicos.
4. Ejecuta los Sketch y el flujo en Node-RED.

