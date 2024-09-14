# Ejemplo comunicacion mediante archivo

## Descripción
Este ejemplo muestra como realizar envio de mensajes entre "usuarios" mediante un archivo central.

## Compilacion
Para compilar el proyecto se debe ejecutar el siguiente comando:
```bash
g++ chat.cpp -o chat #(Windows)
gcc chat.cpp -o chat #(Linux)
```

## Ejecucion
Para ejecutar el proyecto se debe ejecutar el siguiente comando:
```bash
.\chat.exe -u [Nombre de usuario] #(Windows)
./chat -u [Nombre de usuario] #(Linux)
```
## Variables de entorno
- `ARCH_MENSAJES` : Archivo de mensajes centralizado

## Posibles adiciones
- Libreria "Dotenv" para manejo de variables de entorno