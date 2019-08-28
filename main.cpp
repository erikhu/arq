#include <iostream>
#include <vector>
using namespace std;
int main(){
	int h = 4; // # de filas de la matrix
	int w = 8; // ancho de columna
	double aux_val; // variable que puede ser usada cada que se requiera operar con doble precision
	int iaux_val; // variable que puede ser usada en cualquier momento que se requiera operar con enteros
	int iaux_val1;
	int pointery = 0; // se usa para saber la posicion de la fila superior
	int p_auxy = 1; // la posicion de la fila inferior con la que se quiere intercambiar (este valor siempre debe ser mayor a pointery)
	int convertir = true;
	double c_mul = 2; // valor numero que se multiplica con fila
	double diagonal;
	double aux[8] = {1,4,6,3,1,0,0,0};
	double aux1[8] = {5,3,9,3,0,0,0,1};
	double matrix[32] = {0,0,6,1,1,0,0,0,0,5,9,1,0,1,0,0,6,1,2,7,0,0,1,0,5,7,7,1,0,0,0,1};

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
	contador = 0;
	std::cout << "\n";
	  _asm {
		FINIT
		MOV ebx, 0
		while1:
		CMP ebx, h				  ;se verifica que la matrix tenga el mismo ancho y alto
			JGE end_while1	 	  ;si no son iguales se concluye que no puede solucionarse
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
        FNSTSW ax
        SAHF
				JNE end_if1; compara si la diagonal no es cero
					MOV pointery, ebx
					FFREE st(0)	;libera la posicion tope
					MOV eax, h
					DEC eax
					CMP ebx, eax
					JGE end_while1; si la fila actual es igual o mayor a las filas de la matriz entonces no tiene solucion
						MOV ecx, ebx
						filas_abajo: ;recorre las filas inferiores en busca de alguna
							MOV eax, 08h
							MUL w
							MUL ecx
							MOV iaux_val, eax
							MOV eax, 08h
							MUL ebx
							ADD eax, iaux_val
							MOV esi, eax
							FLD matrix[esi]
							FTST
							FNSTSW ax
							SAHF
							JE continuar_filas_abajo	; si es cero continua el recorrido
								FFREE st(0)
								MOV p_auxy, ecx
								MOV eax, 08h							;asignacion a eax el tamano del tipo double
								MUL w											;encontramos el tamano en bytes por fila
								MUL pointery							;encontramos la posicion de la fila superior en la matrix
								MOV esi, eax							;asignamos la posicion de la fila superior en el indice
								MOV ecx, w								;reinicia contador para recorrer todas las columnas de la fila superior
								intercambio:							;etiqueta que apunta hacia el intercambio de filas
								  FLD matrix[esi]					;apila el valor de la columna de la fila superior para luego intercambiar
								  MOV edi, esi						;guardar temporalmente el indice que se usara luego para intercambiar valores
								  MOV iaux_val1, ecx						;guardar temporalmente el registro contador para luego retomar su ultimo valor
								  FILD p_auxy							;apila la posicion de la fila inferior que sera restado con la posicion de la superior
								  FILD pointery						;apila la posicion de la fila superior
								  FSUB										;se resta la posicion de la fila superior con la inferior
								  FISTP iaux_val					;asigna el resultado anterior en la variable auxiliar para enteros
								  MOV eax, 08h						;asignacion a eax el tamano del tipo double
								  MUL w										;encontramos el tamano en bytes por fila
								  MUL iaux_val						;encontramos la posicion de la fila inferior en la matrix
								  ADD esi, eax						;asignamos el indice para la fila inferior
								  MOV ecx, iaux_val1						;volvemos a agregar a ecx el contador que se guardo en ebx para poder continuar el ciclo
								  FLD matrix[esi]					;asigna el valor de la columna de la fila inferior
								  FSTP aux_val						;guarda temporalmente el valor de la columna de la fila inferior
								  FSTP matrix[esi]				;remplaza la columna de la fila superior en la fila inferior
								  MOV esi, edi						;reestablece el indice de la fila superior
								  FLD aux_val							;apila el valor de la columna anterior de la fila inferior
								  FSTP matrix[esi]				;remplaza la columna de la fila superior en el auxiliar
								  ADD esi, 08h						;apunta a la siguiente posicion en la matrix
								  LOOP intercambio				;decrementa cx y termina cuando cx es cero
								JMP end_if1
						continuar_filas_abajo:
							MOV eax, h
							DEC eax
							CMP ecx, eax
							JGE end_while1; la matriz no tiene solucion
								INC ecx
								JMP filas_abajo
				end_if1:
				MOV eax, 0
				CMP eax, convertir
					JZ end_while1 ;convierte en 1 el numero de la diagonal
						MOV eax, ebx
				INC ebx
				JMP while1
		end_while1:
		}
    //mostrar fila
		contador = 0;
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
		cout << "diagonal: " << diagonal << "\n";
		cout << "pointery: " << pointery << "\n";
		cout << "p_auxy: " << p_auxy << "\n";

    return 0;
    }
