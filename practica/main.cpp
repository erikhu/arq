#include <iostream>
#include <conio.h>
using namespace std;
int main(){
  const int MAX_COLUMNAS = 10;
  const int MAX_FILAS = 5;
  const int MAX_TIRA = 50;
  int h; // # de filas de la matrix
  int w; // ancho de columna
  cout << "\n\n\nSaludos, bienvenido a este programa\n";
  cout << "Arquitectura de Computadores 2019-1\n";
  cout << "Alumnos: Erik Alexander Gonzalez Cardona / Andres Felipe Cadena Velez \n";
  cout << "Este es un solucionador de matrices NxN con N > 1 y N <= 5 que utiliza el metodo de la matriz \n";
  cout << "inversa de gauss \n -------------------------------------- \n ";
  cout << "Ingrese por favor el numero de ecuaciones (N): ";
  cin >> h;
  w = h * 2;
  int tira = h*w;
  double aux[MAX_COLUMNAS];
  double aux1[MAX_COLUMNAS];
  double independientes[MAX_FILAS];
  double matrix[MAX_TIRA];
  int contador = 0;
  int i_independiente = 0;
  cout << "Para la ecuacion 1 \n";
  for(int i = 0; i < tira; ++i){
    if(contador < h){
      cout << "Ingrese el coeficiente(" << contador + 1 << "): ";
      cin >> matrix[i];
      ++contador;
    }else{
      cout << "\nIngrese el termino independiente: ";
      cin >> independientes[i_independiente];
      for(int i2 = 0; i2 < h; ++i2){
				if(i_independiente == i2){
					matrix[i+i2] = 1;
				}else{
					matrix[i+i2] = 0;
				}
			}
      ++i_independiente;
      contador = 0;
      i = i + (h-1);
      if(i+1 < tira){
        cout << "\nPara la ecuacion " << i_independiente+1 << "\n";
      }
		}
	}
  contador = 0;
  double aux_val; // variable que puede ser usada cada que se requiera operar con doble precision
  int iaux_val; // variable que puede ser usada en cualquier momento que se requiera operar con enteros
  int iaux_val1;
  int iaux_val2;
  int pointery; // se usa para saber la posicion de la fila superior
  int p_auxy; // la posicion de la fila inferior
  double c_mul; // valor numero que se multiplica con fila
  int interrupcion = 0;
  double diagonal;
  double negativo = -1;
  std::cout << "\n";
  _asm {
	FINIT
	MOV ebx, 0
while1:
	CMP ebx, h
	JGE end_while1
	MOV eax, 08h
	MUL w
	MUL ebx
	MOV iaux_val, eax
	MOV eax, 08h
	MUL ebx
	ADD eax, iaux_val
	MOV esi, eax			;encuentra la direccion del valor de la diagonal en la fila
	FLD matrix[esi]
	FST diagonal
	FTST
	FNSTSW ax
	SAHF
	JNE end_if1			;si el valor matrix[i][i] es cero continua para intercambiar con otra fila
	  MOV pointery, ebx		;indice para la fila superior
	  FFREE st(0)
	  MOV eax, h
	  DEC eax
	  CMP ebx, eax
	  JGE error			;si la fila actual es igual o mayor a las filas de la matriz entonces no tiene solucion
	  MOV ecx, ebx
filas_abajo:
	  MOV eax, 08h
	  MUL w
	  MUL ecx
	  MOV iaux_val, eax		;indice para la fila inferior
	  MOV eax, 08h
	  MUL ebx
	  ADD eax, iaux_val
	  MOV esi, eax			;direccion del valor de la diagonal para la fila inferior
	  FLD matrix[esi]
	  FTST
	  FNSTSW ax
	  SAHF
	  JE continuar_filas_abajo	;sigue buscando un valor de la diagonal que no sea cero

	FSTP diagonal
	MOV p_auxy, ecx
	MOV eax, 08h
	MUL w
	MUL pointery
	MOV esi, eax			;direccion de la fila superior
	MOV ecx, w
intercambio:
	FLD matrix[esi]
	MOV edi, esi			;temporalmente almacena la direccion del elemento a cambiar de la fila superior
	MOV iaux_val1, ecx
	FILD p_auxy
	FILD pointery
	FSUB
	FISTP iaux_val			;encuentra la cantidad de pasos que hay entre la fila superior e inferior
	MOV eax, 08h
	MUL w
	MUL iaux_val
	ADD esi, eax			;direccion del elemento a cambiar de la fila inferior
	MOV ecx, iaux_val1
	FLD matrix[esi]
	FSTP aux_val			;temporalmente guarda el elemento de la fila inferior
	FSTP matrix[esi]		;remplaza el elemento de la fila superior en la fila inferior
	MOV esi, edi			;reestablece el indice de la fila superior
	FLD aux_val
	FSTP matrix[esi]		;remplaza el elemento de la fila inferior en la fila superior
	ADD esi, 08h			;apunta a la siguiente posicion en la matrix
	LOOP intercambio
	JMP end_if1

continuar_filas_abajo:
	MOV eax, h
	DEC eax
	CMP ecx, eax
	JGE error			;la matriz no tiene solucion
	INC ecx
	JMP filas_abajo

end_if1:				;pasa a convertir en 1 la diagonal
	FFREE st(0)
	FLD1
	FLD diagonal
	FDIV
	FSTP c_mul			; el valor es temporalmente 1/diagonal
	MOV eax, 08h
	MUL w
	MUL ebx
	MOV esi, eax			;direccion en la matriz de la fila actual
	MOV ecx, w
multiplicacion:
	FLD c_mul
	FLD matrix[esi]
	FMUL
	FSTP matrix[esi]		;se multiplico por una constante el elemento de la matriz
	ADD esi, 08h
	LOOP multiplicacion

	MOV iaux_val, ebx
	INC iaux_val			;se inicia desde la fila siguiente a la actual pero la actual no cambia
ceros_abajo:
	MOV eax, h
	CMP iaux_val, eax
	JGE siguiente

	MOV ecx, w
	MOV esi, 00h
asignar_aux:				;toda la fila superior en aux para luego operar
	MOV edi, esi
	MOV eax, 08h
	MUL w
	MUL ebx
	MOV esi, eax
	ADD esi, edi
	FLD matrix[esi]
	FSTP aux[edi]			;remplaza elemento de la fila superior o la actual en el arreglo aux
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
	FSTP c_mul			;constante negativo para hacer ceros los elementos debajo del 1
	MOV esi, 00h
	MOV ecx, w
multiplicacion1:
	FLD c_mul
	FLD aux[esi]
	FMUL				;multiplica la constante con el elemento de la matriz aux y luego lo remplaza
	FSTP aux[esi]
	ADD esi, 08h
	LOOP multiplicacion1

	MOV ecx, w
	MOV esi, 00h
suma: 					;marca de inicio para la suma de dos listas
	MOV edi, esi			;temporalmente almacena la direccion de aux
	MOV eax, 08h
	MUL w
	MUL iaux_val
	MOV esi, eax
	ADD esi, edi			;encuentra la direccion analoga de aux en la matriz principal
	FLD matrix[esi]
	FLD aux[edi]
	FADD				;suma el elemento de aux con el elemento analogo en la matriz
	FSTP matrix[esi]		;remplaza el resultado en la posicion del elemento en la matriz
	MOV esi, edi
	ADD esi, 08h 			;aumenta el indice para lista tipo double
	LOOP suma 			;descuenta el registro cx hasta recorrer la base
	INC iaux_val
	JMP ceros_abajo			;continua eliminando los ceros debajo del 1
siguiente:
	INC ebx
	JMP while1

end_while1:
	MOV ecx, 1
ceros_arriba:
	CMP ecx, h
	JG fin_ceros_arriba
	MOV iaux_val, ecx
	MOV eax, h
	SUB eax, iaux_val
	MOV p_auxy, eax			;indice de la fila inferior
	INC ecx
alreves:
	CMP ecx, h
	JG fin_alreves
	  MOV iaux_val1, ecx
	  MOV eax, h
	  SUB eax, iaux_val1
	  MOV pointery, eax		;indice fila superior

	  MOV ecx, w
	  MOV esi, 00h
asignar_aux1:
	  MOV edi, esi
	  MOV eax, 08h
	  MUL w
	  MUL p_auxy ;
	  MOV esi, eax
	  ADD esi, edi
	  FLD matrix[esi]		;remplaza elemento de la fila inferior o la actual en el arreglo aux
	  FSTP aux[edi]
	  MOV esi, edi
	  ADD esi, 08h
	  LOOP asignar_aux1

	  MOV eax, 08h
	  MUL w
	  MUL pointery
	  MOV iaux_val2, eax
	  MOV eax, 08h
	  MUL p_auxy
	  ADD eax, iaux_val2
	  MOV esi, eax
	  FLD matrix[esi]		;se apila el elemento de la fila superior que esta arriba del 1
	  FLD negativo
	  FMUL
	  FSTP c_mul
	  MOV esi, 00h
	  MOV ecx, w
multiplicacion2:
	  FLD c_mul
	  FLD aux[esi]
	  FMUL
	  FSTP aux[esi]
	  ADD esi, 08h
	  LOOP multiplicacion2

	  MOV ecx, w
	  MOV esi, 00h
suma1:
	  MOV edi, esi
	  MOV eax, 08h
	  MUL w
	  MUL pointery
	  MOV esi, eax
	  ADD esi, edi
	  FLD matrix[esi]
	  FLD aux[edi]
	  FADD
	  FSTP matrix[esi]		;suma aux con la fila superior para hacer cero el elemento arriba del 1
	  MOV esi, edi
	  ADD esi, 08h
	  LOOP suma1
	MOV ecx, iaux_val1
	INC ecx
	JMP alreves
fin_alreves:
	MOV ecx, iaux_val
	INC ecx
	JMP ceros_arriba
fin_ceros_arriba:

  MOV ecx, w
  MOV esi, 00h
en_ceros:
  FLDZ					;hace ceros todo el arreglo aux
  FSTP aux[esi]
  ADD esi, 08h
  LOOP en_ceros

  MOV ebx, 0
en_la_fila:
	CMP ebx, h
	JGE fin
	  MOV esi, 00h
	  MOV ecx, h
mul_matrices:
	  MOV edi, esi			;direccion del elemento del arreglo independientes
	  MOV eax, 08h
	  MUL w
	  MUL ebx
	  MOV iaux_val, eax
	  MOV eax, 08h
	  MUL h
	  ADD eax, iaux_val
	  MOV esi, eax
	  ADD esi, edi			;direccion del elemento analogo al arreglo independientes en la matriz invertida
	  FLD matrix[esi]
	  FLD independientes[edi]
	  FMUL
    MOV eax, 08h
    MUL ebx
    MOV esi, eax			;direccion del elemento aux que suma cada multiplicacion
	  FLD aux[esi]
	  FADD
	  FSTP aux[esi]			;se guarda el resultado dentro del mismo elemento aux y acomula
	  MOV esi, edi
	  ADD esi, 08h
    MOV iaux_val, ecx
	  LOOP mul_matrices
fin_mul_matrices:
	INC ebx
	JMP en_la_fila
error:
	MOV interrupcion, 1
fin:
		}

   if(interrupcion != 0){
     cout << "No tiene solucion\n";
   }else{
     cout << "La solucion es: \n";
     cout << "[";
     for(int i = 0; i < h; i++){
	     cout << aux[i] << " ";
     }
     cout << "]";
     cout << "\n";
   }

   cout << "El programa a finalizado. \nHasta luego \n";
   char c = 565;
   c = getch();

   return 0;
}
