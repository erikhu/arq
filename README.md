# SOLUCIONADOR DE MATRICES NXN

Este proyecto fue creado con [Open watcom v2](https://github.com/open-watcom/open-watcom-v2)
Para poder crear aplicaciones para windows desde
sistemas GNU/Linux.

Metodo de gauss jordan con matrices inversas para encontrar la solucion de las variables,
esta existe. Practica de ensamblador con sintaxis intel.

## Como compilar el proyecto desde Open watcom v2 IDE
* Abrir el IDE de Open watcom
* File -> Open Project y se busca el archivo arq.wpj
* Una vez abierto el proyecto se presiona la tecla F5 y el proyecto compila, 
de esta manera actualiza o genera un nuevo archivo arq.exe
## Ejecucion

Por cmd
* Para ejecutarlo se debe abrir el cmd y se dirije a la carpeta para correr desde ahi arq.exe

Por Open watcom
* Actions -> Run
* Se abre una ventana y escribe arq.exe

## Importante
Esta limitado a solucionas matrices de hasta 5x5 pero se puede cambiar para que solucione matrices mucho mas grandes.
Para esto se deben cambian las constantes MAX_FILAS como el numero de filas para la matriz maxima a la cual se quiere solucionar, MAX_COLUMNAS como el numero maximo de columnas que deben ser el doble de MAX_FILAS, y MAX_TIRA el maximo tamana de elementos que tendra la matriz que ese MAX_COLUMNAS * MAX_FILAS. Asi se puede actualizar para que solucione matrices mucho mayores a 5x5.
