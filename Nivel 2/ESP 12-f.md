# ESP 12-f

Esto es un recordatorio de los pasos realizados para la descarga del Firmware con los comandos AT,
la documentacion consultada, y las conexiones necesarias para el ESP 12-f.

## Herramientas / Instalacion
Para poder utilizar la herramienta que descarga el Firmware sobre la placa, es necesario tener instalado [Python 2.4 o Python 3.7](https://www.python.org/downloads/)

### esptool.py
Para para la instalacion del esptool desde la terminal

```sh
$ pip install esptool

```
Acerca de usos y caracteristicas de [esptool.py](https://github.com/espressif/esptool).

### Firmware 
Puede descargarse la version para ESP-01 que igual funciono, desde [aca](https://wiki.aprbrother.com/en/Firmware_For_ABTemp.html). O alguna version directamente desde la pagina de [Espressif](https://bbs.espressif.com/viewtopic.php?t=1613)

## Conexiones
Tanto el instructivo para las instalaciones como los pines de conexion fueron tomados del instructivo de [rictroniks.wordpress.com](https://riktronics.wordpress.com/2016/10/19/flash-at-firmware-to-esp8266-wifi-module-easiest-way/)

El modulo tiene 2 modos de funcionamiento dependiendo de la conexion que se realice:
 - UART Download Mode (Flasheo de la memoria)
 - Flash Boot Mode (Funcionamiento normal)
Para la descarga del Firmware:

| EDU-CIAA | ESP 12-F |
|----------|----------|
| 3.3V | VCC |
| GND | GND |
| 3.3V | GPIO2|
| GND | GPIO0|
| GND | GPIO15|
| RX-232 | TX |
|TX -232| RX|

**No alimentar el modulo con mas de 3.3V**
