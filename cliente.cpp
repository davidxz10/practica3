#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream> 

using namespace std;

// Crear un socket TCP/IP
int crearSocket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error al crear el socket" << endl;
    }
    return sockfd;
}

// Configurar la dirección del servidor
struct sockaddr_in configurarDireccion(const char* ip, int puerto) {
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto); // Convierte el puerto al formato de red
    
    // Convertir la IP de texto a binario
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        cerr << "Direccion IP invalida." << endl;
    }
    return serv_addr;
}

// Conectar con el servidor
bool conectarServidor(int sockfd, struct sockaddr_in serv_addr) {
    cout << "Intentando conectar con el servidor..." << endl;
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        cerr << "Error al conectar" << endl;
        return false;
    }
    cout << "Conexion establecida correctamente." << endl;
    return true;
}

// Recibir los datos
vector<float> recibirDatos(int sockfd) {
    vector<float> datos_recibidos;
    unsigned char buffer; // Leemos byte a byte para ser compatibles con el empaquetado del servidor Python
    
    cout << "Recibiendo datos de temperatura..." << endl;
    // Bucle para recibir datos mediante recv() hasta que el servidor finaliza 
    while (recv(sockfd, &buffer, sizeof(buffer), 0) > 0) {
        datos_recibidos.push_back(static_cast<float>(buffer));
    }
    return datos_recibidos;
}

// Guardar los datos en un archivo de texto local
void guardarEnArchivo(const vector<float>& datos, const string& nombre_archivo) {
    // Apertura del fichero en modo escritura
    ofstream archivoSalida(nombre_archivo); 
    
    if (!archivoSalida.is_open()) {
        cerr << "No se pudo crear el archivo " << nombre_archivo << endl;
        return;
    }
    
    for (size_t i = 0; i < datos.size(); i++) {
        archivoSalida << datos[i] << endl; // Escribimos el valor en el fichero
    }
    
    archivoSalida.close(); // Cierre de fichero 
    cout << "Datos guardados en el archivo: " << nombre_archivo << endl;
}

// Imprimir los resultados por pantalla
void imprimirResultados(const vector<float>& datos) {
    cout << "\n--- Valores Recibidos ---" << endl;
    for (size_t i = 0; i < datos.size(); i++) {
        cout << "Sensor [" << i << "] -> " << datos[i] << endl;
    }
    cout << "-------------------------" << endl;
    cout << "Total de lecturas recibidas: " << datos.size() << endl;
}

int main() {
    const char* IP_SERVIDOR = "127.0.0.1"; 
    const int PUERTO = 12345;

    cout << "INICIANDO CLIENTE DE MONITORIZACION TERMICA" << endl;

    // Crear el socket
    int sockfd = crearSocket();
    if (sockfd == -1) return 1;

    // Configurar IP y Puerto
    struct sockaddr_in serv_addr = configurarDireccion(IP_SERVIDOR, PUERTO);
    
    // Conectar al servidor
    if (!conectarServidor(sockfd, serv_addr)) {
        close(sockfd);
        return 1; // Salimos si no hay conexión
    }

    // Recibir y almacenar los datos en memoria
    vector<float> datosTermicos = recibirDatos(sockfd);
    
    if (datosTermicos.empty()) {
        cout << "No se recibieron datos del servidor." << endl;
    } else {
        // Guardar los datos en el sistema local
        guardarEnArchivo(datosTermicos, "Resultados.txt");
        
        // Imprimir los datos para su verificación 
        imprimirResultados(datosTermicos);
    }

    // Cerrar la conexión y finalizar el programa 
    close(sockfd); 
    cout << "Conexion cerrada de forma segura. Fin del programa." << endl;
    
    return 0;
}
