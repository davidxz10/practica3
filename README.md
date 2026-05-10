# Comunicacion Cliente-Servidor usando sockets en C++ 
## 1.Descripción
Este repositorio contiene la tercera practica de la asignatura de Sistemas Operativos desarollado en C++ y Bash y tiene como objetivo trabajar las conexiones entre procesos usando Sockets TCP/IP.

---

## 2. Estructura del repositorio

```
├── bash.sh                          # Script en Bash
├── cliente.cpp                      # Código en C++
├── ServidorCamara.py                # Servidor escrito en Python
├── Resultados.txt                   # Datos archivo salida
├── cliente                          # Binario
├── LICENSE             
└── README.md
```

---

## 3. Requisitos del sistema
- Sistema operativo Linux (probado en Linux Mint 22.3)
- GNU Bash
- Gcc/G++
- Python3

### Instalacion de las herramientas
```bash
sudo apt update && sudo apt upgrade
sudo apt install bash g++ python3
```

---

## 4. Ejecución
```bash
./bash.sh
```

---

## 5. Salida esperada
[1/3] Iniciando el servidor Python (ServidorCamara.py)...

Servidor escuchando en 127.0.0.1:12345

[2/3] Ejecutando el cliente C++...

INICIANDO CLIENTE DE MONITORIZACION TERMICA

Intentando conectar con el servidor...

Conexion establecida correctamente.

Recibiendo datos de temperatura...

Conexión aceptada desde ('127.0.0.1', 53306)

Array de datos enviado al cliente.

Datos guardados en el archivo: Resultados.txt


--- Valores Recibidos ---

Sensor [0] -> 0

Sensor [1] -> 1

Sensor [2] -> 2

Sensor [3] -> 3

-------------------------

Total de lecturas recibidas: 768

Conexion cerrada de forma segura. Fin del programa.

[3/3] Cerrando el servidor Python (PID: 12261)...


## 6. Autoría
* Alumno: David

## 7. Licencia
GLP-3.0 license
