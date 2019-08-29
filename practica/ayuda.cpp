				ALGORITMOS
--------------------------------------------------------------------------------
------------------------suma la aux con aux1 y lo guarda en aux---------------------
MOV ecx, w	 	;reinicia el valor del contador con el ancho de columna
MOV esi, 00h 		;el indice es cero para acceder desde el inicio a aux y aux1
suma: 			;marca de inicio para la suma de dos listas
  FLD aux[esi] 		;apila el valor de aux para sumarlo con aux1
  FLD aux1[esi]		;apila el valor de aux1 para sumarlo con aux
  FADD 			;suma de aux y aux1 segun el indice
  FSTP aux[esi] 	;guarda la suma en el aux
  ADD esi, 08h 		;aumenta el indice para lista tipo double
  LOOP suma 		;descuenta el registro cx hasta recorrer la base

------------------------multiplica una constante (c_mul) por cada elemento de una fila en aux-----------------
MOV esi, 00h 		;reinicia el indice del registro esi para iniciar desde cero
MOV ecx, w        	;reinicia el valor del contador con el ancho de columna
multiplicacion:   	;marca de inicio para la multiplicacion de una lista por una constante
  FLD c_mul		;apila el valor de la constante para multiplicar con el valor de la matriz
  FLD aux[esi]    	;apila el valor de la matriz para multiplicar con la constante
  FMUL			;multiplica la constante por el valor apilado de la matriz
  FSTP aux[esi]		;desapilamos en la matriz el resultado de la multiplicacion
  ADD esi, 08h		;aumenta el indice para la liste de tipo double
  LOOP multiplicacion 	;decrementa el registro ecx y luego verifica que sea distinto de cero

----------intercambia dos filas de la matrix (segun pointery(fila superior) y p_auxy(fila inferior))----------
MOV eax, 08h		;asignacion a eax el tamano del tipo double
MUL w			;encontramos el tamano en bytes por fila
MUL pointery		;encontramos la posicion de la fila superior en la matrix
MOV esi, eax		;asignamos la posicion de la fila superior en el indice
MOV ecx, w		;reinicia contador para recorrer todas las columnas de la fila superior
intercambio:		;etiqueta que apunta hacia el intercambio de filas
  FLD matrix[esi]	;apila el valor de la columna de la fila superior para luego intercambiar
  MOV edi, esi		;guardar temporalmente el indice que se usara luego para intercambiar valores
  MOV ebx, ecx		;guardar temporalmente el registro contador para luego retomar su ultimo valor
  FILD p_auxy		;apila la posicion de la fila inferior que sera restado con la posicion de la superior
  FILD pointery		;apila la posicion de la fila superior
  FSUB			;se resta la posicion de la fila superior con la inferior
  FISTP iaux_val	;asigna el resultado anterior en la variable auxiliar para enteros
  MOV eax, 08h		;asignacion a eax el tamano del tipo double
  MUL w			;encontramos el tamano en bytes por fila
  MUL iaux_val		;encontramos la posicion de la fila inferior en la matrix
  ADD esi, eax		;asignamos el indice para la fila inferior
  MOV ecx, ebx		;volvemos a agregar a ecx el contador que se guardo en ebx para poder continuar el ciclo
  FLD matrix[esi]	;asigna el valor de la columna de la fila inferior
  FSTP aux_val		;guarda temporalmente el valor de la columna de la fila inferior
  FSTP matrix[esi]	;remplaza la columna de la fila superior en la fila inferior
  MOV esi, edi		;reestablece el indice de la fila superior
  FLD aux_val		;apila el valor de la columna anterior de la fila inferior
  FSTP matrix[esi]	;remplaza la columna de la fila superior en el auxiliar
  ADD esi, 08h		;apunta a la siguiente posicion en la matrix
  LOOP intercambio	;decrementa cx y termina cuando cx es cero

----remplazar valores de aux en determinada fila (por p_auxy)-------------------
MOV esi, 00h		;reinicio del indice
MOV ecx, w		;contador ecx como el tamano de las columnas o el ancho de alguna fila
remplazo:		;etiqueta que apunta hacia el intercambio de filas
  MOV edi, esi		;guarda el indice en otro registro para luego ser utilizado
  FLD aux[esi]		;apila el valor de la columna de la fila para luego reemplazar
  MOV eax, 08h		;asignacion a eax el tamano del tipo double
  MUL w			;encontramos el tamano en bytes por fila
  MUL p_auxy		;encontramos la posicion de la fila en la matrix
  ADD esi, eax		;asigna la posicion para encontrar el valor a reemplazar
  FSTP matrix[esi]	;asigna el nuevo valor a la matrix
  MOV esi, edi		;regresa al ultimo valor del indice
  ADD esi, 08h		;aumenta una posicion en el indice para aux
  LOOP remplazo		;decrementa cx y termina cuando cx es cero
