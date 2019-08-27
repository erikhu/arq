#include <iostream>
#include <vector>
int main(){
	int h = 4; // # de filas de la matrix
	int w = 8; // ancho de columna
	double c_mul = 2; // valor numero que se multiplica con fila
	double aux[8] = {1,4,6,3,1,0,0,0};
	double aux1[8] = {5,3,9,3,0,0,0,1};
	double matrix[32] = {1,4,6,1,1,0,0,0,5,3,9,1,0,1,0,0,6,3,5,7,0,0,1,0,5,7,7,1,0,0,0,1};
	int contador = 0;
	for(int i = 0 ; i < 32; i++){
	std::cout << matrix[i] << " ";
		if(contador >= w-1){
			std::cout << "\n";
			contador = 0;
		}else{
			contador = contador + 1;
		}
	}
	std::cout << "\n";
	double aux_val;
	int iaux_val;

	int pointery = 0; // se usa para saber la posicion de la fila actual en el arreglo
	int p_auxy = 3; // la posicion de la otra fila con la que se quiere intercambiar
    _asm {
		FINIT
		MOV ecx, w	 							;reinicia el valor del contador con el ancho de columna
		MOV esi, 00h 							;el indice es cero para acceder desde el inicio a aux y aux1
		suma: 										;marca de inicio para la suma de dos listas
			FLD aux[esi] 						;apila el valor de aux para sumarlo con aux1
			FLD aux1[esi]						;apila el valor de aux1 para sumarlo con aux
			FADD 										;suma de aux y aux1 segun el indice
			FSTP aux[esi] 					;guarda la suma en el aux
			ADD esi, 08h 						;aumenta el indice para lista tipo double
			LOOP suma 							;descuenta el registro cx hasta recorrer la base

		MOV esi, 00h 							;reinicia el indice del registro esi para iniciar desde cero
		MOV ecx, w        				;reinicia el valor del contador con el ancho de columna
		multiplicacion:   				;marca de inicio para la multiplicacion de una lista por una constante
			FLD c_mul		    				;apila el valor de la constante para multiplicar con el valor de la matriz
			FLD aux[esi]    				;apila el valor de la matriz para multiplicar con la constante
			FMUL										;multiplica la constante por el valor apilado de la matriz
			FSTP aux[esi]						;desapilamos en la matriz el resultado de la multiplicacion
			ADD esi, 08h						;aumenta el indice para la liste de tipo double
			LOOP multiplicacion 		; decrementa el registro ecx y luego verifica que sea distinto de cero

		MOV eax, 08h
		MUL w
		MUL pointery
		MOV esi, eax
		MOV ecx, w								;reinicia contador para recorrer todas las columnas de una fila
		intercambio:							;etiqueta que apunta hacia el intercambio de filas
			FLD matrix[esi]					;apila el valor de la columna de la primera fila para intercambiar
			MOV edi, esi						;guardar temporalmente la direccion de la columna que se usara luego para intercambiar
			MOV ebx, ecx						;guardar temporalmente el registro contador para luego remotar su valor

			FILD p_auxy
	 		FILD pointery
			FSUB
			FISTP iaux_val
			MOV eax, 08h
			MUL w
			MUL iaux_val
			ADD esi, eax

			MOV ecx, ebx
			FLD matrix[esi]
			FSTP aux_val
			FSTP matrix[esi]
			MOV esi, edi
			FLD aux_val
			FSTP matrix[esi]
			ADD esi, 08h

			LOOP intercambio
    }
    //mostrar fila
		for(int i = 0 ; i < 32; i++){
		std::cout << matrix[i] << " ";
			if(contador >= w-1){
				std::cout << "\n";
				contador = 0;
			}else{
				contador = contador + 1;
			}
		}

		std::cout << "\n";
    return 0;
    }
