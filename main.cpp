#include <iostream>
#include <vector>
using namespace std;
int main(){
	int h = 3; // # de filas de la matrix
	int w = 6; // ancho de columna
	double aux_val; // variable que puede ser usada cada que se requiera operar con doble precision
	int iaux_val; // variable que puede ser usada en cualquier momento que se requiera operar con enteros
	int iaux_val1;
	int iaux_val2;
	int pointery; // se usa para saber la posicion de la fila superior
	int p_auxy; // la posicion de la fila inferior con la que se quiere intercambiar (este valor siempre debe ser mayor a pointery)
	double c_mul; // valor numero que se multiplica con fila
	int interrupcion = 0;
	double diagonal;
	double negativo = -1;
	double aux[6];
	double aux1[6];
	double matrix[18] = {1,0,0,1,0,0,-1,2,3,0,1,0,0,1,2,0,0,1};

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
		while1:																;Sistema de resolucion Gauss Jordan
		CMP ebx, h				  									;se verifica que la matrix tenga el mismo ancho y alto
			JGE end_while1	 	  								;si no son iguales se concluye que no puede solucionarse
				MOV eax, 08h
				MUL w
				MUL ebx
				MOV iaux_val, eax
				MOV eax, 08h
				MUL ebx
				ADD eax, iaux_val
				MOV esi, eax
				FLD matrix[esi]
				FST diagonal
				FTST
        FNSTSW ax
        SAHF
				JNE end_if1												; compara si la diagonal no es cero
					MOV pointery, ebx
					FFREE st(0)											;libera la posicion tope
					MOV eax, h
					DEC eax
					CMP ebx, eax
					JGE error												; si la fila actual es igual o mayor a las filas de la matriz entonces no tiene solucion
						MOV ecx, ebx
						filas_abajo: 									;recorre las filas inferiores en busca de alguna
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
							JE continuar_filas_abajo
								FSTP diagonal
								MOV p_auxy, ecx
								MOV eax, 08h
								MUL w											;encontramos el tamano en bytes por fila
								MUL pointery							;encontramos la posicion de la fila superior en la matrix
								MOV esi, eax
								MOV ecx, w								;reinicia contador para recorrer todas las columnas de la fila superior
								intercambio:							;etiqueta que apunta hacia el intercambio de filas
								  FLD matrix[esi]
								  MOV edi, esi
								  MOV iaux_val1, ecx
								  FILD p_auxy
								  FILD pointery
								  FSUB
								  FISTP iaux_val
								  MOV eax, 08h
								  MUL w										;encontramos el tamano en bytes por fila
								  MUL iaux_val						;encontramos la posicion de la fila inferior en la matrix
								  ADD esi, eax						;asignamos el indice para la fila inferior
								  MOV ecx, iaux_val1
								  FLD matrix[esi]					;asigna el valor de la columna de la fila inferior
								  FSTP aux_val
								  FSTP matrix[esi]				;remplaza la columna de la fila superior en la fila inferior
								  MOV esi, edi						;reestablece el indice de la fila superior
								  FLD aux_val
								  FSTP matrix[esi]				;remplaza la columna de la fila superior en el auxiliar
								  ADD esi, 08h						;apunta a la siguiente posicion en la matrix
								  LOOP intercambio
								JMP end_if1
							continuar_filas_abajo:
							MOV eax, h
							DEC eax
							CMP ecx, eax
							JGE error										; la matriz no tiene solucion
								INC ecx
								JMP filas_abajo
				end_if1:													; termina el intercambio y pasa a convertir en 1 las diagonales
				FFREE st(0)
				FLD1
				FLD diagonal
				FDIV
				FSTP c_mul
				MOV eax, 08h
				MUL w
				MUL ebx
				MOV esi, eax
				MOV ecx, w        								;reinicia el valor del contador con el ancho de columna
				multiplicacion:   								;marca de inicio para la multiplicacion de una lista por una constante
				  FLD c_mul
				  FLD matrix[esi]
				  FMUL														;multiplica la constante por el valor apilado de la matriz
				  FSTP matrix[esi]								;desapilamos en la matriz el resultado de la multiplicacion
				  ADD esi, 08h
				  LOOP multiplicacion

				MOV iaux_val, ebx ; linea en inversa 96
				INC iaux_val
				ceros_abajo:
					MOV eax, h
					CMP iaux_val, eax
					JGE siguiente
						MOV ecx, w ; tener encuenta en caso de val extraños
						MOV esi, 00h
						asignar_aux: ; toda la fila superior
							MOV edi, esi
							MOV eax, 08h
							MUL w
							MUL ebx
							MOV esi, eax
							ADD esi, edi
							FLD matrix[esi]
							FSTP aux[edi]
							MOV esi, edi
							ADD esi, 08h
							LOOP asignar_aux
						MOV eax, 08h
						MUL w
						MUL iaux_val
						MOV iaux_val1, eax
						MOV eax, 08h
						MUL ebx
						ADD eax, iaux_val1
						MOV esi, eax
						FLD matrix[esi]
						FLD negativo
						FMUL
						FSTP c_mul
						MOV esi, 00h 							;reinicia el indice del registro esi para iniciar desde cero
						MOV ecx, w        				;reinicia el valor del contador con el ancho de columna
						multiplicacion1:   				;marca de inicio para la multiplicacion de una lista por una constante
							FLD c_mul		    				;apila el valor de la constante para multiplicar con el valor de la matriz
							FLD aux[esi]    				;apila el valor de la matriz para multiplicar con la constante
							FMUL										;multiplica la constante por el valor apilado de la matriz
							FSTP aux[esi]						;desapilamos en la matriz el resultado de la multiplicacion
							ADD esi, 08h						;aumenta el indice para la liste de tipo double
							LOOP multiplicacion1 		;decrementa el registro ecx y luego verifica que sea distinto de cero
					MOV ecx, w	 							;reinicia el valor del contador con el ancho de columna
					MOV esi, 00h 							;el indice es cero para acceder desde el inicio a aux y aux1
					suma: 										;marca de inicio para la suma de dos listas
						MOV edi, esi
						MOV eax, 08h
						MUL w
						MUL iaux_val
						MOV esi, eax
						ADD esi, edi
						FLD matrix[esi]
						FLD aux[edi] 						;apila el valor de aux para sumarlo con aux1
						FADD
						FSTP matrix[esi] 					;guarda la suma en el aux
						MOV esi, edi
						ADD esi, 08h 						;aumenta el indice para lista tipo double
					  LOOP suma 							;descuenta el registro cx hasta recorrer la base
					INC iaux_val
					JMP ceros_abajo
				siguiente:
				INC ebx
				JMP while1
		end_while1:

		MOV ecx, h
		ceros_arriba:
			CMP ecx,1
			JLE fin
			MOV iaux_val, ecx; k fila inferior
			DEC ecx
			MOV iaux_val1, ecx; l fila superior
			alreves:
				CMP ecx, 0
				JLE fin_alreves
				MOV ecx, w ; tener encuenta en caso de val extraños
				MOV esi, 00h
				asignar_aux1: ; toda la fila inferior
					MOV edi, esi
					MOV eax, 08h
					MUL w
					MUL iaux_val
					MOV esi, eax
					ADD esi, edi
					FLD matrix[esi]
					FSTP aux[edi]
					MOV esi, edi
					ADD esi, 08h
					LOOP asignar_aux1
				MOV eax, 08h
				MUL w
				MUL iaux_val1
				MOV iaux_val2, eax
				MOV eax, 08h
				MUL iaux_val
				ADD eax, iaux_val2
				MOV esi, eax
				FLD matrix[esi]
				FLD negativo
				FMUL
				FSTP c_mul
				MOV esi, 00h 							;reinicia el indice del registro esi para iniciar desde cero
				MOV ecx, w        				;reinicia el valor del contador con el ancho de columna
				multiplicacion2:   				;marca de inicio para la multiplicacion de una lista por una constante
					FLD c_mul		    				;apila el valor de la constante para multiplicar con el valor de la matriz
					FLD aux[esi]    				;apila el valor de la matriz para multiplicar con la constante
					FMUL										;multiplica la constante por el valor apilado de la matriz
					FSTP aux[esi]						;desapilamos en la matriz el resultado de la multiplicacion
					ADD esi, 08h						;aumenta el indice para la liste de tipo double
					LOOP multiplicacion2 		;decrementa el registro ecx y luego verifica que sea distinto de cero
				MOV ecx, w	 							;reinicia el valor del contador con el ancho de columna
				MOV esi, 00h 							;el indice es cero para acceder desde el inicio a aux y aux1
				suma1: 										;marca de inicio para la suma de dos listas
					MOV edi, esi
					MOV eax, 08h
					MUL w
					MUL iaux_val1
					MOV esi, eax
					ADD esi, edi
					FLD matrix[esi]
					FLD aux[edi] 						;apila el valor de aux para sumarlo con aux1
					FADD
					FSTP matrix[esi] 					;guarda la suma en el aux
					MOV esi, edi
					ADD esi, 08h 						;aumenta el indice para lista tipo double
					LOOP suma1							;descuenta el registro cx hasta recorrer la base
				MOV ecx, iaux_val1
				DEC ecx
				JMP alreves
			fin_alreves:
				MOV ecx, iaux_val
				DEC ecx
			 	JMP ceros_arriba
			JMP fin
		error:
			MOV interrupcion, 1
		fin:
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
		cout << "c_mul: " << c_mul << "\n";
		cout << "interrupcion: " << interrupcion << "\n";
    return 0;
    }
