Tipo de Dato Abstracto Lista, Cola y Pila
=============

## Introducción

El trabajo consta de la implementación de un TDA lista con sus propias funciones para su utilización, tanto como para la creación,destrucción y estado de la lista (si está vacia o con  cuantos elementos cuenta) como para la inserción y eliminación de elementos. A su vez, cuenta con funciones para la utilización del mismo como una pila o una cola, con funciones para apilar, encolar, desapilar y desencolar.

## Funcionamiento del TDA
	
Para la implementación de las funciones intenté modularizar acciones básicas para la **inserción, eliminación, y búsqueda/recorrido**, ésta última con funciones recursivas. Básicamente para insertar y para borrar  hay tres casos: entre dos elementos, al inicio y al final. Estos dos últimos son sencillos ya que solamente tiene que actualizar nodo_inicio y nodo_final de la lista (funciones "anclar"). En cambio para insertar entre dos elementos, además de buscar al elemento en la posición que hay que insertar o eliminar, hay que saber su anterior para poder reemplazar los nodos. Es por eso que primero hay que buscar en la posición anterior (función nodo_en_posicion),conseguir el siguiente (el buscado) y con el mismo, su sucesor. Para la búsqueda, utilizo una función recursiva que recibe el nodo de inicio (nodo_incio para este caso), un contador inicializado a 0, el cual se utiliza para saber cuantas veces se iteró; y una posición, que será el valor del contador para que devuelva el elemento. En caso de insertar, el nuevo elemento ocupará el lugar en posicion desplazando al que se encontraba anteriormente allí y siendo el sucesor del que se encuentra en la posicion anterior. Es por esto que si se inserta al inicio, no tiene un antecesor, o si se inserta al final (o en una posicion arbitraria) no tiene un sucesor, y en ambos caso se debe actualizar los nodos inicio y fin de la lista. En caso de eliminar, el siguiente del buscado será el siguiente del antecesor y el buscado será eliminado, si se borra el último elemento, el anterior pasa a ser el último, o si se borra el primer elemento, el siguiente pasará a ser el primero.
	
Después de esto, varias funciones siguen la misma lógica, **insertar, apilar y encolar** agregan un elemento al final de la lista, desapilar quita del nodo_fin y desencolar del nodo_inicio. Con estos nodos de la lista fácilmente se puede devolver el primer y último elemento para el tope de la pila y el primero de la cola, así mismo, con la cantidad de la lista facilmente se puede saber si ésta está vacia o la cantida de elementos. Lo último referido a la lista es su destrucción, para esto con una función recursiva recorro los nodos liberando desde el último al primero y una vez liberado el espacio de los nodos, libero la lista.
	
Por último lugar, quedan los **iteradores**, para crear el iterador externo únicamente hay que asignarle un espacio en la memoria y incializarlo con el nodo_inicio de la lista y la lista misma. Luego las funciones son bastante básicas, informando el estado del iterador según su corriente para saber si avanaza, el elemento del mismo, o avanzando, cambiando el corriente por su siguiente. Por otro lado, para el iterador interno opté por una implementación recursiva dónde las condiciones de corte son: si no existe el nodo, es decir se iteró toda la lista, o si no se cumple la función, si ninguna de éstas condiciones se cumplen avanza al siguiente elemento.

Para la creación de las pruebas intenté crear entornos particulares para cada tipo de funciones que forman parte del TDA, así podia asegurarme el funcionamiento básico de las mismas, tanto como lista, cola o pila. Para cada operación, traté de chequear mediante las mismas funciones del TDA, que las condiciones de la lista se cumplan una vez se haya realizado una modificación con la función que esté probando. Esto implicó cierta confianza en funciones como lista_último, lista_primero, o lista_elemento_en_posicion para chequear inserciones en el lugar correcto o que elementos borrados no se encuentren en la lista.
	
## Compilación y Ejecución

Tanto para compilar como para ejecutar hice uso de un Makefile.
	
- **Make**: Compila el archivo lista_pruebas.c junto con lista.c (tda) y pa2mm.h (archivo de testeo) 
	
- **Make test**: Ejecuta lista_se (ejecutable de lista_pruebas.c) con Valgrind, en el caso de no contar con el archivo previamente compilado o actualizado, ejecuta Make para compilarlo.
	
- **Make debug**: Ejecutar lista_se con GDB en caso de querer debuguear

## Conceptos teóricos

### ¿Cuáles son las características fundamentales de las Pilas? ¿Y de las Colas?

Tanto la pila como la cola son un TDA cuyo objetivo es almacenar elementos según su orden de inserción y la gran diferencia entre ambos es que la forma de que se desapila y se desencola. Para desapilar, se sigue el principio de LIFO (last input, first output) por lo que el primer elemento que se desapila es el último que se apila, y para desencolar, en cambio, se utiliza el principio de FIFO (first input, first output), por lo que el primer elemento que se encola es el también el primero que se desencola. A la vez, ambos TDA tienen la característica de no poder ingresar a los elementos intermedios, unicamente se pude acceder al "tope" o último elemento en el caso de la pila y al primer elemento en el caso de la cola, ya que estos elementos son los que se borran del TDA conlas funciones desapilar y desencolar.  

### ¿Qué es lo que entendés por una lista? ¿Cuáles son las diferencias entre ser simple o doblemente enlazada?

Una lista es un conjunto de elementos ordenados y enlazados entre sí. Una particularidad de la lista, a diferencia de cola y pila, es que se tiene acceso a cualquier elemento del conjunto, tanto para ver, como para borrar o insertar en posición. En una lista se inserta al final y para borrar se sigue el principio de LIFO, de la misma manera que lo hace la pila. La diferencia entre una lista simple y otra doblemente enlazadaes que una simple solo conoce a su próximo elemento, y una doble conoce tanto al que le sigue como al que le precede. 

### ¿Qué es un iterador? ¿Cuál es su función?

Un iterador es un herramienta, que puede ser un procedimiento o un TDA aparte, que se utiliza para recorrer todos los elementos de una lista. Lo particular de ésta herramienta es que ayuda a encapsular el procedimiento y simplificar la complejidad del recorrido. En el caso de querer operar con cada elemento de la lista, uno tendria que buscar el elemento, recorriendo todos los anteriores, operar y de nuevo hacer un recorrido hasta el próximo. Con un iterador, uno puede guardar la posicion del elemento y luego avanzar al siguiente con una complejidad O(1) en vez de O(n).

## ¿En qué se diferencia un iterador interno de uno externo?

La diferencia entre un iterador interno y uno externo, principalmente, es que el interno es un procedimiento propio del TDA lista, que hace uso de la propia estructura del TDA para recorrer y ejecutar una funcion para cada elemento, y en cambio, el iterador externo es un TDA aparte con sus propias funciones y cuya utilización depende exclusivamente del usuario.
 
