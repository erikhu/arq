#include <iostream>
#include <vector>
int main(){
	int h = 4; // # de filas de la matrix
	int w = 2*h; // ancho de columna
	double aux_val; // variable que puede ser usada cada que se requiera operar con doble precision
	int iaux_val; // variable que puede ser usada en cualquier momento que se requiera operar con enteros
	int pointery = 0; // se usa para saber la posicion de la fila superior
	int p_auxy = 1; // la posicion de la fila inferior con la que se quiere intercambiar (este valor siempre debe ser mayor a pointery)
	int convertir = true;
	double c_mul = 2; // valor numero que se multiplica con fila
	double diagonal;
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


	  _asm {
		FINIT
		MOV eax, 0
		while1:
			CMP eax, h				  ;se verifica que la matrix tenga el mismo ancho y alto
			JGE end_while1	 	  ;si no son iguales se concluye que no puede solucionarse
				MOV ebx, eax
				MOV eax, 08h
				MUL w
				MUL ebx
				MOV iaux_val, eax
				MOV eax, 08h
				MUL ebx
				ADD eax, iaux_val
				MOV esi, eax
				FLD matrix[esi]
				FSTP diagonal
				MOV convertir, 1

				FLD diagonal
				FTST
				JE end_if1 ; intenta cambiar filas
					FLD diagonal
					FADD
					FSTP matrix[esi]

				end_if1:
				MOV eax, 0
				CMP eax, convertir
				JZ end_while1 ;convierte en 1 el numero de la diagonal

				MOV eax, ebx
				INC eax
				JMP while1
		end_while1:
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

		std::cout << "aux: \n" ;
		for(int i = 0; i < 8; i++){
			std::cout << aux[i] << " ";
		}

		std::cout << "\n";
    return 0;
    }
