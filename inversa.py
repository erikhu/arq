#      --- Importando librerias ---      #
import fpformat
#      --- Se definen variables ---      #
dimx = 0
dimy = 0
mini = 0

# --- Se definen funciones/metodos ---  #
# Generado de la matriz
def generador(y,x):
    mat = []

    for k in range(y):
        mat.append([])

    for i in range(y):
        for j in range(x):
            print
            mat[i].append(float(raw_input("a_" + str(i+1) + str(j+1) + " = ")))

    return mat

# Despliega matriz
def impri(m):
    print "\n"
    print "\t||" + ("\t" * (len(m[0]) + 1)) + "||"
    
    for i in range(len(m)):
        print "\t||\t",
        
        for j in range(len(m[0])):
            print fpformat.fix(m[i][j],2),"\t",

        print "||"
        print "\t||" + ("\t" * (len(m[0]) + 1)) + "||"
        
    print "\n"
 
# Sumador de listas

def adic(l1, l2):
    ln = [0]*len(l1)

    for i in range(len(l1)):
        ln[i] = l1[i] + l2[i]

    return ln

# Multiplicador por constante

def multi(l1, k):
    ln = [0]*len(l1)
    
    for i in range(len(l1)):
        ln[i] = k * l1[i]

    return ln

# Buscador y cambiador de filas

def swap_finder(m, l, x):
#verifica que la fila no sea la ultima
    if l == (x-1):
        print "La matriz es una matriz singular."
        print "Eso implica que no se puede resolver.\n\n"
        return m, False
    else:
#Busca intercambiarlo con una fila inferior la cual la misma col no sea 0
        for i in range(l, x):
            if m[i][l] != 0:
                m[l], m[i] = m[i], m[l]
                return m, True

        print "La matriz es una matriz singular."
        print "Eso implica que no se puede resolver.\n\n"
        return m, False

# Sistema de resolucion Gauss-Jordan

def solver(m,p):
    for i in range(p):
        boo = True
        
        if m[i][i] == 0:
            m, boo = swap_finder(m, i, p)

        if boo:
			#convierte en 1 el numero de la diagonal
            m[i] = multi(m[i], 1/float(m[i][i]))

        else:
			#si es falso entonces no se puede sol
            return m

        #len(m) = p
        for j in range(i+1,len(m)):
			#multiplica y suma para hacer ceros columna hacia abajo
            m[j] = adic(m[j], multi(m[i], -1*float(m[j][i])))
#hace ceros las columnas arriba de la diagonal
#recorre desde p-1(fila superior) hasta 0
    for k in range(p-1, -1, -1):
		#recorre desde k-1(columna de la misma fila) hasta 0
        for l in range(k-1, -1, -1):
            m[l] = adic(m[l], multi(m[k], -1*float(m[l][k])))

    return m

#       --- Programa Principal ---       #

print "\n"*5

dimy = int(raw_input("Ingrese la cantidad de filas de la matriz: "))

dimx = int(raw_input("Ingrese la cantidad de columnas de la matriz: "))

#solicita los valores
matriz = generador(dimy, dimx) 

impri(matriz)

mini = dimy

solucion = solver(matriz, mini)

print "\t\t*** Solucion ***"

impri(matriz)
