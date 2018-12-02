# PI-Final-Project
Trabajo Practico Final de Programacion Imperativa



Compilacion y Ejecucion:

Dentro de la carpeta ProyectoFinal ejecutar con la linea de comandos "make" o "make all".
Con esto se deberia haber compilado el programa y haber creado el ejecutable main.out.
Para ejecutarlo usar el comando "./main.out".



Archivos:

El programa consta de 4 partes principales.

Hay dos TAD, airportADT y movementsADT que se encuentran en la carpeta TAD junto con su header correspondiente.

Por otro lado, hay una libreria para el front llamada frontend.c que tiene funciones de lectura
de los archivos de texto y una implementacion de menu, y otra para el back llamada baskend.c que
incluye funciones relacionadas al procesado y almacenado de informacion. Ambos tienen un header correspondiente.

Por ultimo, se encuentra el main.c.


Notas:

1. Dado que el archivo de movimientos contiene una gran cantidad de elementos, consideramos poco sensato levantar
toda la informacion al mismo tiempo. Es por eso que lo decidimos hacer por bloques (MBLOCK en el programa). Sin embargo,
no estamos seguros de que numero es el optimo teniendo en cuenta la memoria y la velocidad. Experimentalmente
determinamos que un numero cercano al mas optimo en terminos de velocidad es 5000, asique elegimos este, sin embargo,
de determinar un numero mejor, es muy sencillo elegir otro, simplemente es cambiar un define.

2. Para la implementacion de los TAD hubo que decidir si la informacion que se debe guardar como un string
lo haciamos mediante shallow copy o deep copy. En principio, la primera es la que favorece a la optimizacion
de los recursos de tiempo y memoria, sin embargo, consideramos que lo hace a expensas de seguridad del programa.
Por ejemplo, si utilizaramos shallow copy y el usuario decidiera hacer un free del string con el que ingreso los datos,
todo el sistema fallaria. Es por esto que decidimos sacrificar un poco la eficiencia en pos de que el programa sea mas seguro.
En cualquier caso, si se decidiera que es mas importante la eficiencia, deberia ser relativamente sencillo cambiar el programa
para que soporte shallow copy.

