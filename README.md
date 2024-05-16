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

## Configuración del Gateway IoT

Para nuestro Gateway IoT, es necesario contar con una Raspberry Pi previamente configurada con el sistema operativo Raspbian.

![Raspberry](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/440942315_462030883020045_8914836050148913492_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=5f2048&_nc_ohc=FVFTtciv5_EQ7kNvgGyeUKi&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYCkVZy3z4VTrvWsas9iAW1jwpks-aI3EbSOcuAuzpZ5dA&oe=664B44A3)

## Instalación de Servicios
Utilizaremos contenedores proporcionados por la aplicación IOTstack para la instalación de los servicios necesarios para nuestro proyecto, incluyendo Node-RED, Grafana y InfluxDB.

![Services](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443697865_462038419685958_7255652886975180424_n.jpg?_nc_cat=101&ccb=1-7&_nc_sid=5f2048&_nc_ohc=dmaw6fgYlloQ7kNvgE3dBK0&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYBTVSHxgY8oEc4S16_TDcHHp6JsJSCGtMBFYGOXP34-xg&oe=664B65B4)


1. Descarga y ejecución del menú de IOTstack:
- bash
- cd ~/IOTstack
- ./menu.sh

![Comandos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436202234_462034766352990_472832190792485744_n.jpg?_nc_cat=103&ccb=1-7&_nc_sid=5f2048&_nc_ohc=mt4YcsMw80YQ7kNvgFcFr6f&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYChh5xdg9gUSJXxvOqs0XCEkXBgmYHKNzUkP_dxTf6j-A&oe=664B4433)

2. Selecciona los contenedores deseados del catálogo proporcionado para su instalación.

3. Una vez instalados, activa los contenedores con el siguiente comando:
- cd ~/IOTstack
- docker-compose up -d

![Comandos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443699106_462034746352992_2754388878349414799_n.jpg?_nc_cat=107&ccb=1-7&_nc_sid=5f2048&_nc_ohc=Esn-2HyeLJQQ7kNvgEnVWhJ&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYATJ-B8GThx25IC4dSqGz-CLcIThA-kLwoO-U2Uuv2TBQ&oe=664B51D3)

## Instalación y Configuración de Mosquitto
Para utilizar el servicio Mosquitto, primero debemos asegurarnos de que estamos utilizando el sistema operativo Raspbian Buster.
- lsb_release -a

![Comandos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443873778_462034736352993_8546870462017293521_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=5f2048&_nc_ohc=C4295ZQHcGgQ7kNvgEbgXw2&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYDxnZRWu68RIFFAdpskwu17IOZgN6beiUzDkg3MSJswHQ&oe=664B66A0)

### Agregar el Repositorio de Mosquitto
Importa la llave del repositorio y agrega el repositorio Mosquitto correspondiente a tu versión de Raspbian.
- wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
- sudo apt-key add mosquitto-repo.gpg.key
- cd /etc/apt/sources.list.d/
- sudo wget http://repo.mosquitto.org/debian/mosquitto-buster.list

![Comandos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443697258_462034706352996_1303846566650950438_n.jpg?_nc_cat=102&ccb=1-7&_nc_sid=5f2048&_nc_ohc=CoYM5JOnGL8Q7kNvgErp-uM&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYBIBHlKHAYMbAmFBykj7hUEf07c-ZcMHbW78uWybjKeHA&oe=664B4CDC)

### Instalación de Mosquitto
Instala Mosquitto y los clientes de Mosquitto.

- sudo apt install mosquitto mosquitto-clients

![Comandos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436236167_462034693019664_9133623292363947329_n.jpg?_nc_cat=107&ccb=1-7&_nc_sid=5f2048&_nc_ohc=V1h1gijO1AgQ7kNvgHro69d&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYDrGpaVBudBtZcI3ZgnBrLnZR2tr9QFE78LSEF1ecV7Kw&oe=664B3986)

### Configuración y Prueba de Mosquitto
Para que MQTT se inicie automáticamente al reiniciar la Raspberry Pi:

- sudo systemctl enable mosquitto

![Comandos](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436311289_462034696352997_3159305224379812235_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=5f2048&_nc_ohc=JC9b4R-LJ3YQ7kNvgHJJbKN&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYDiHlJQGBmy1cWtk7aU1nDkXIH91354kRcwJVWps4xkdg&oe=664B6D1E)

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

![DASHBOARD](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436270459_458930153330118_762916704406892469_n.jpg?_nc_cat=103&ccb=1-7&_nc_sid=5f2048&_nc_ohc=M7dOembK_TkQ7kNvgE-_NUK&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAuZn4gvpU1kLI9rkE_Jnt1R2mYRxxGPwZUmnKcR-Rgqw&oe=664B5237)

### Notificaciones
- **Función**: Envia notificaciones vía WhatsApp en caso de valores fuera de rango de temperatura y humedad.

## Almacenamiento de datos en Node-RED
Hemos configurado nodos de InfluxDB en nuestro flujo de Node-RED para almacenar los datos recibidos en nuestra base de datos. Estos nodos envían los datos de manera estructurada a InfluxDB, que ofrece un almacenamiento eficiente de series temporales. Esta integración nos proporciona escalabilidad y flexibilidad para gestionar grandes volúmenes de datos y realizar análisis efectivos.
   ![INFLUXDB](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/435924901_462046626351804_2752548772844671832_n.jpg?_nc_cat=101&ccb=1-7&_nc_sid=5f2048&_nc_ohc=mLGUU2vJEBYQ7kNvgEyW6j2&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAucrZRp1QUTBsq6OjekSr8P7tbEWHVsm-uEPCJfPL0hw&oe=664B5D89)
   
  Estos nodos están configurados para enviar datos a una base de datos de InfluxDB ubicada en 127.0.0.1:8086 a través del protocolo HTTP. Utilizan la base de datos llamada "database", perteneciente a la organización "Sensores_Transporte".
  
   ### Configuración de los nodos de InfluxDB en Node-RED.
- **Temperatura:**
  - **Measurement:** Temperatura
  - **Bucket:** SensorTemperatura

- **GPS:**
  - **Measurement:** Influx_GPS
  - **Bucket:** GPS_BD

- **Humedad:**
  - **Measurement:** Humedad
  - **Bucket:** SensorHumedad

Cada nodo está diseñado para manejar un tipo específico de datos y enviarlos a la base de datos correspondiente en InfluxDB, lo que permite una organización eficiente y una gestión adecuada de los datos dentro del sistema de Node-RED.


## Visualización de datos con Grafana

Grafana es una herramienta poderosa para la visualización de datos y el monitoreo de sistemas. Con Grafana, podemos crear paneles personalizados que muestran datos en tiempo real de manera visualmente atractiva. En este caso, utilizaremos Grafana para visualizar los datos almacenados en la base de datos de InfluxDB que hemos configurado previamente en Node-RED.

### Pasos para la configuración:

1. **Instalación de Grafana:**
   - Descarga e instala Grafana desde el [sitio web oficial de Grafana](https://grafana.com/get).

2. **Conexión a la base de datos de InfluxDB:**
   - Abre la interfaz web de Grafana y accede al panel de configuración.
   ![GRAFANA](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436258003_462052059684594_1042560935193682446_n.jpg?_nc_cat=108&ccb=1-7&_nc_sid=5f2048&_nc_ohc=FY3iBug6qu0Q7kNvgGcT752&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYAg5i5Z52N8l3x_dl8gZ3XMSDRCLd9JJzHEPklTDgXtTw&oe=664B7A9B)
   
   - Agrega una nueva fuente de datos y selecciona InfluxDB.
   ![GRAFANA](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/436455494_462052043017929_7072058896767949797_n.jpg?_nc_cat=101&ccb=1-7&_nc_sid=5f2048&_nc_ohc=tZv3jU6SFCcQ7kNvgEOuaZj&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYB-assb66FogK9iDHwjO2jBAHSANQ-NpbZeNqJvkc-Nyw&oe=664B72BC)
   
   - Completa los campos necesarios con la información de conexión a la base de datos de InfluxDB que has configurado previamente en Node-RED.
![GRAFANA](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443698913_462051983017935_426352716898106986_n.jpg?_nc_cat=100&ccb=1-7&_nc_sid=5f2048&_nc_ohc=yR2w9K-GQpcQ7kNvgHns0nE&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYBhHYY8PYWn0J77MuO6Yl_6HUC9SIvv5JjER1Z22Y4M7A&oe=664B63A9)

3. **Creación de paneles:**
   - Una vez que Grafana esté conectado a la base de datos de InfluxDB, puedes comenzar a crear paneles para visualizar tus datos.
   - Haz clic en "Crear" y selecciona el tipo de panel que deseas crear (gráfico de líneas, gráfico de barras, tabla, etc.).
   - Configura la consulta para seleccionar los datos de la base de datos de InfluxDB que deseas visualizar en el panel.
  ![GRAFANA](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443699229_462055833017550_7294549411968241810_n.jpg?_nc_cat=109&ccb=1-7&_nc_sid=5f2048&_nc_ohc=W36Hb1cD5VAQ7kNvgG4PXdp&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYBz6aVrTrxJ9PgWMm_3JsdeSZOKafwg4F-SlPZQzlgGbA&oe=664B5CEF)
  
4. **Personalización y configuración avanzada:**
   - Personaliza la apariencia y configuración del panel según tus necesidades.
   - Agrega múltiples series temporales, ajusta los ejes, define alertas, y más para crear visualizaciones efectivas de tus datos.
   ![GRAFANA](https://scontent.fmex45-1.fna.fbcdn.net/v/t39.30808-6/443841211_462055819684218_1346133273310196898_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=5f2048&_nc_ohc=P36DHgmMxjsQ7kNvgHTnuZp&_nc_ht=scontent.fmex45-1.fna&cb_e2o_trans=q&oh=00_AYBk1DVX-hkBL9KyHJugKaPtBmDH1VDJ54PVe_xHEzXaUw&oe=664B5022)

Con Grafana, puedes crear visualizaciones potentes y personalizadas de tus datos almacenados en InfluxDB, lo que te permite comprender mejor tus sistemas y tomar decisiones informadas.



## Instalación
1. Clona este repositorio.
2. Importa los codigos de Arduino(Transmisor y Receptor) y el flujo de Node-RED.
3. Configura los archivos .INO y el flujo con tus datos específicos.
4. Ejecuta los Sketch y el flujo en Node-RED.
