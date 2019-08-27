#include <iostream>
#include <vector>
int main(){
	int h = 2; // # de filas de la matrix
	int w = 4; // ancho de columna
	double aux[4] = {1,4,1,0};
	double aux1[4] = {5,3,0,1};
    _asm {
		FINIT
		MOV ecx, w	 		; reinicia el valor del contador con el ancho de columna
		MOV esi, 00h 		; el indice es cero para acceder desde el inicio a aux y aux1
		suma: 				; marca de inicio para la suma de dos listas
			FLD aux[esi] 	; apila el valor de aux para sumarlo con aux1
			FLD aux1[esi]	; apila el valor de aux1 para sumarlo con aux
			FADD 			; suma de aux y aux1 segun el indice
			FSTP aux[esi] 	; guarda la suma en el aux
			ADD esi, 08h 	; aumenta el indice para lista tipo double
			LOOP suma 		; descuenta el registro cx hasta recorrer la base
    }
    //mostrar fila
    for(int i = 0 ; i < w; i++){
		std::cout << aux[i] << " ";
		}
		std::cout << "\n";
    return 0;
    }
