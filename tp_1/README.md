Trabajo Práctico 1
=============

## Introducción sobre el funcionamiento del trabajo presentado

El trabajo práctico aplica conocimientos de la utilización de archivos y memoria dinámica, y consta de un programa con temática de Pokemon, dónde un usuario, cargando un archivo de origen, en este caso un arrefice, elige ciertos párametros para que la infomación dentro (Pokemones), se pase a un nuevo archivo (Acuario) si cumple con la pauta ingresada. Para más detalles, se encuentra explicado en la consigna.

La implementación consiste de 2 partes, la biblioteca personalizada "evento_pesca.c" y el código del main.c, el cual opté por una implementación interactiva.

### evento_pesca.c

- **crear_arrecife**

En la principal se abre el archivo para lectura y se crea el arrecife con malloc, si no puede alguno de los dos, devuelve NULL, luego una funcion se encarga de crear y cargar el bloque de pokemones dentro del arrefice; dentro de esta una parte crea el bloque y otra función se encarga de cargar todos los pokemones, donde se lee el archivo mientras se va modificando el tamaño del bloque de pokemones.

- **crear_acuario**

Crea el bloque para el acuario y tambien el bloque correspondiente para los pokemones, en caso de que algun malloc falle, devuelve NULL.

- **traladar_pokemon** 

Una primera función cuenta todos los pokemones transferibles según la funcion seleccionar, y si es cantidad es menor a la cantidad que se pasa por parametro, sale devolviendo ERROR; en caso contrario, realiza el traslado completo, ésta funcion recorre todo el arrecife y para cada pokemon que cumple con la funcion seleccionar, lo copia al acuario y luego lo sacar del arrecife; para pasarlo al acuario, primero agranda con realloc el bloque de pokemones y luego pasa ese pokemon a la ultima posición sin ocupar; para sacarlo del arrecife,copia el último pokemon al lugar del pokemon para sacar (ya que no importa el orden), modifica el tope y achica el arrecife al tamaño actual. En caso de llegar a la cantidad que se pasó por parámetros, deja de trasladar.

- **censar_arrecife**

Ejecuta la funcion mostrar tantas veces como pokemones haya en el arrecife (iteracion for)

- **guardar_datos_acuario**

Abre para escritura el nuevo archivo, si no puede, sale, sino escribe en formato tantos pokemones haya en el acuario (iteracion for)

- **liberar_acuario/liberar_arrefice**

Primero libera el bloque de pokemones, luego el bloque del acuario o el arrecife

### main.c

Para la implementación queria contar mejor la idea general que tiene el programa. Tanto el archivo del arrecife como donde guarda el acuario, se pasan por argumentos de comando, en caso de no tener alguno, el programa no corre. Luego es todo interactivo con el usuario, decidí hacerlo así para que pueda elegir qué funciones de selección o de mostrar por pantalla utilizar, y tambien para determinar la cantidad en cada traslado. Para esto, antes de un traslado, se pregunta al usuario si quiere seguir haciendo otro, por lo que si acepta, elige que funciones usar, y sino sale del programa liberando la memoria dinámica y guardando los datos. En caso de que haya algún error con los archivos o malloc/realloc, intenté expresar por pantalla los errores puntualmente
así se sabe cuales fueron esos problemas. Para la implementacion de las funciones personalizables, usé una estructura con un array de punteros a funciones, sus topes, y un string que explique la funcion, así dentro de la iteracion while sea posible utilizar otras funciones solamente ingresando un número. Para cargar dichas funciones hay que hacer uso de cargar_funciones, función que ingresando este struct, la funcion, y su nombre o explicacion, se agrega al struct.

//Algo que me gustaria modificar es considerar que si la cantidad que ingresa para el traslado es mayor a los pokemones trasladables, avise de esto y no termine la función de traslado con error, sino que pueda seguir haciendo otro traslado y cierre el programa al guardar.

## Como compilar y ejecutar

Para este aspecto hice uso de un archivo Makefile con ciertas instrucciones.

- **make / make evento_pesca** : compila el archivo main junto con evento_pesca.c.

- **make exe** :  ejecuta el programa con el archivo "arrecife.txt" guardando los datos en "acuario.txt". Tambien puede ejecutarse a mano con **./evento_pesca** e ingresando los dos archivos tanto para el arrecife como el acuario.

- **make help / ./evento_pesca --help** : ejecuta la ayuda al usuario para saber como ejecurarlo 
en el caso de querer usar otros archivos.

- **make val" y make gdb** : se ejecutan valgrind y gdb respectivamente en caso de querer hacer pruebas. 

## Conceptos utilizados

1. **Punteros**:

Los punteros o pointers pueden describirse como variables que guardan direcciones de memoria para cierto tipo de dato. Esto es útil para usar valores independientemente de su ámbito y que todo se remita al main. Es gracias a esto que se pueden modificar valores desde otras funciones a valores que se guardar dentro del ámbito de la funcion principal. Los operadores son " * " para definir el tipo de dato y " & " para obtener direcciones de memoria de ciertas variables. Dentro de todos los tipo posibles de datos que se utilizan para punteros, hay que destacar void* que funciona como un puntero a ningún tipo de dato en particular, por lo que después, puede ser asignado a otro tipo de dato.

2. **Aritmética de punteros**:

Una forma de entender aritmética de punteros es haciendo su paralelismo con los arrays. Ya es sabido que los arrays o vectores, son direcciones de memoria continua, por lo que array[0] y array[1] estan continuos en la memoria, lo mismo pasa con los punteros. Un puntero (*pointer) es el valor de la primera dirección de memoria (lo que seria array[0]) asignada al tipo de dato que acompaña al puntero, por lo que *(pointer + 1) o pointer[1] seria el valor de la direccion de memoria continua y del tamaño del mismo tipo de dato que pointer, *(pointer + 2) o pointer[2] la continua a esta y así sucesivamente. 

3. **Punteros a funciones**:

Los punteros a funciones funcionan con la misma lógica que los punteros tradicionales, unicamente que en vez de referirse a direcciones en la memoria estática o dinámica (.stack y .heap respectivamente), se refiere a direcciones dentro del .code, lugar donde se guarda el código fuente del programa antes de ser compilado. Por lo que hacer uso de punteros a funciones facilita el traspaso de código a otras funciones, y por lo tanto, es posible parametrizar funciones y ampliar las posibilidades dentro de una función que las recibe.
	
4. **Malloc y Realloc**:

Malloc y Realloc son dos funciones de stdlib.h que funcionan como herramienta para manejar la memoria dinámica pertenciente al heap. Siempre que se crea un bloque en la memoria dinámica hay que "liberarlo" luego de su uso, sino todo lo que se reserve va a seguir ocupado. Para ésto, se hace uso de "void free (void* ptr)" para liberar la memoria utilizada en la dirección "ptr" de memoria (puntero).
	
La función **void* malloc (size_t size)** es la encargada de crear un bloque de memoria de tamaño size y devuelve la dirección de memoria del mismo como un puntero "void*", en caso de no poder crear el bloque, devuelve un puntero NULL.

En cambio, la funcion **void* realloc (void* ptr, size_t size)** lo que hace es modificar el tamaño a "size" de un bloque (de dirección "ptr") previamente creado por un malloc. Ésta función puede tener varias alternativas:

- Primero, modificar el tamaño correctamente y devolver la misma dirección que se le ingresó; 

- Segundo, encuentra un nuevo bloque del tamaño ingresado, donde copia el contenido del la dirección que se le ingresó y libera la misma, por lo que devuelve un puntero a ese nuevo bloque;

- Por último, no encuentra lugar en la memoria de ese tamaño y devuelve NULL. Es por esto que es importante usa un auxiliar para guardar el puntero que pase (ya que puede ocurrir el 2do caso) y si ese auxiliar no recibe NULL, recién ahí asignarlo a la variable original que tenia el puntero.
	
