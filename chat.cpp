#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
// #include "dotenv.h"  // No se logro incluir desde compilacion en windows

using namespace std;

void displayMessages(const string &userName, string filePath){
    ifstream inFile(filePath);
    if (!inFile){
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)){

        if (line.find("To:@" + userName) != string::npos){
            cout << "\033[1;32m" << line << "\033[0m" << endl; // Verde para mensajes entrantes
        }
        else if (line.find("From:@" + userName) != string::npos){
            cout << "\033[1;34m" << line << "\033[0m" << endl; // Azul para mensajes salientes
        }
    }

    inFile.close();
}

int main(int argc, char *argv[]){
    if (argc != 3 || strcmp(argv[1], "-u") != 0){
        cerr << "Uso: " << argv[0] << " -u [Nombre de Usuario]" << endl;
        return 1;
    }
    string userName, receiver, message;
    userName = argv[2];
    // Leer el archivo .env con lectura de archivo normal
    ifstream file(".env");
    string line;
    string filePath;

    if (file.is_open()){
        while (getline(file, line)){
            if (line.find("ARCH_MENSAJES") != string::npos){
                filePath = line.substr(line.find("=") + 1);
            }
        }
        file.close();
    }
    else{
        cerr << "Error: No se pudo abrir el archivo .env" << endl;
        return 1;
    }

    // cout << "filePath: " << filePath << endl;
    if ((filePath == "")){
        cerr << "Error: La variable de entorno ARCH_MENSAJES no está definida." << endl;
        return 1;
    }

    while (true){
        cout << "Ingrese su nombre del destinatario \033[1;31m(o 'salir' para terminar)\033[0m: ";
        getline(cin, receiver);

        if (receiver == "salir"){
            break;
        }

        cout << "Ingrese su mensaje \033[1;31m(o 'salir' para terminar)\033[0m: ";
        getline(cin, message);

        if (message == "salir"){
            break;
        }

        ofstream outFile(filePath, ios::app);
        if (!outFile){
            cerr << "Error: No se pudo abrir el archivo." << endl;
            return 1;
        }

        outFile << "From:@" << userName << " | To:@" << receiver << " | " << message << endl;
        outFile.close();

        cout << "Mensajes (\033[1;32mRecibidos\033[0m | \033[1;34mEnviados\033[0m):\n";
        displayMessages(userName, filePath);
    }

    return 0;
}