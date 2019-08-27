MOV eax, w
MUL p_auxy
MOV ecx, eax
col_fila_obj:
    ADD esi, 08h
    loop col_fila_obj

otra forma
MOV eax, 08h
MUL w
MUL p_auxy
ADD esi, eax

salvacion
MOV edi, esi						;guardar temporalmente la direccion de la columna que se usara luego para intercambiar
MOV ebx, ecx						;guardar temporalmente el registro contador para luego remotar su valor

MOV eax, 08h
MUL w
MUL p_auxy
sub eax, 08h
ADD esi, eax

MOV ecx, ebx
FLD matrix[esi]
FSTP aux_val
FSTP matrix[esi]
MOV esi, edi
FLD aux_val
FSTP matrix[esi]
ADD esi, 08h
