Tipo de Dato Abstracto Lista, Cola y Pila
=============

	El trabajo consiste en la implementación de un TDA ABB con las respectivas funciones para su funcionamiento. 

### Funcionamiento del TDA

En primer lugar, las funciones de menos complejidad son : **crear, vacio y raiz**. Para crear el árbol basta con crear su espacio en la memoria dinámica e inicializar los punteros. A su vez se requiere como obligación tener un comparador (imprescindible para la búsqueda), y como opcional un destructor(ya que pueden ser elementos en el stack). Por otro lado, vacio y raiz, evaluan practicamente las mismas cosas, que exista el árbol y que existala raiz, si no existe la raiz , como también si no existe el árbol, está vacio y si existe la raíz, se devuelve su elemento. 

Para las funciones más complejas, como **la búsqueda, la inserción, la eliminación, los recorridos, la iteración interna y la destrucción del árbol**, opté por implementaciones recursivas. La función de destruir el árbol consiste en recorrer el árbol de tal manera de no perder punteros, por lo tanto implementé un recorrido postorden, donde como última instancia se ejecuta el nodo, y con un procedimiento que libera completamente un nodo (aplicando el destructor, si existe, al elemento y liberando la memoria del nodo) y una vez liberados todos los nodos, libera el espacio asignado al la estructura abb_t. 
	
La **función de búsqueda** se implementa de tal forma que según una comparación, con el comparador, se determina con qué parte del árbol se queda, hasta que que la comparación sea igual, ahí devuelve dicho elemento. La función de inserción se basa en los mismo principios, pero de manera que recorre hasta el final de la rama y devuelva dicha posicíión para que se inserte un elemento como hoja del árbol (nodo sin hijos) y quede ordenado dentro del árbol, siguiendo el principio de que todo lo que está a la derecha del nodo es mayor al mismo y todo lo que está a la izquierda, menor. Para las funciones de recorridos y de interación, hice una única implementación dónde se aplica una función al elemento del nodo, pero dependiendo del orden que corresponda (inorden, preorden y postorden). Una vez se aplica dicha función se aumenta el índice de un contador que determinará por cuantos elementos se aplicó la misma, y una vez ésta sea verdadera no se deberia aplicar más a ningún elemento. Para los recorridos, hice uso de un struct llamado array_t, el cual me facilitaba pasar un vector, su última posición ocupada, y su tamanio, unicamente como un void*, ya que la funcion debia cumplir cierto firma (void* elemento, void* extra) en este caso siendo el extra mi struct array_t. La función en cuestión, que se encarga de ir insertando elementos al vector, unicamente pone el elemento corriente en la última posicion sin ocupar del vector y luego evalua si ésta fue su última inserción (si ya se llenó el array), si es así devuelve verdadero y corta el recorrido.
	
Por último, queda la **función de borrado**, la cual principalmente se basa en buscar elementos y determinar su condición para saber como será las reasignaciones de los punteros. Los casos son los siguientes:
 - RAIZ: Si es raíz hay dos alternativas.Una es que tenga hijos, por lo que deberiamos buscar un predecesor junto a su padre para que esté herede los hijos del mismo, y el precesor pueda ocupar el lugar de la raíz (reasignado el nodo_raiz del arbol y heredando sus hijos).El otro caso es que sea hoja, y por ende borrandolo, el aŕbol quedaria vacio (nodo_raiz = NULL)

 - HOJA (no raíz): Si el elemento es hoja, como no depende de nadie, unicamente habría que eliminarlo y que su padre apunte a NULL.

 - PADRE e HIJO(no raíz): Acá ya hay varias alternativas. Las más sencillas son que no tenga hijo menor y sí un hijo mayor, por lo que este solamente ocupe su lugar; y la otra, es que su predecesor inorden no tenga hijos mayores, por lo que éste ocupa su lugar y hereda sus hijos mayores. El otro caso, más complejo, es buscar un Predecesor Inorden, pero éste necesitara a su padre que heredará sus hijos izquierdos (si los tiene) (no sus derechos porque sino no seria el mayor de los menores) y el predecesor pasa a ocupar el lugar del nodo a borrar, heredando ambos hijos.

Para la realización de las pruebas me basé en un estilo de TDD hasta dónde pude, ya que por ejemplo para poder determinar varios resultados de algunas funciones debia implementar el resto, por lo que al princinpio hice pruebas básicas y de inserción con comparación de punteros unicamente como puntapié, y luego pruebas más exahustivas, abarcando la mayoria de casos. El archivo test.h y test.c estan basados en pa2mm.h de Lucas, unicamente con algunas modificaciones de nombres y algunas funciones extra.

------------------------------------------------------------------------

### Compilación y ejecución:

Para la compilación y ejecución del trabajo hice uso de un Makefile dónde:

- **Make o Make abb** : 	Compila las pruebas_abb.c junto con abb.c y test.c(bilbioteca de testeo) y el resto de flags

- **Make test** : Ejecuta abb junto con valgrind

- **Make debug** : Ejecuta abb junto con gdb con interfaz
	
-----------------------------------------------------------------------

### Teoría

#### Qué es un ABB y cómo se diferencia de un Árbol Binario
	
Un árbol binario cumple con la única condicion de que cada nodo tiene dos hijos, en cambio un ABB cumple con ciertar premisas que fácilita la búsqueda de elementos. Estas premisas consisten en un orden dentro de árbol, el hijo derecho es mayor al padre y el hijo izquierdo es menor. De está forma, todos los predecesor izquierdos son menores a la raiz mientras que los derechos serán mayores, y por lo cual, dado un elemento, se puede buscar restringiendo los elementos.
	
#### Cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.
	
El objetivo de tener una función de destrucción es facilitar el borrado de elementos, ya que si se destruye el nodo y no el elemento, el usuario deberia haber guardado la referencia al mismo para poder destruirlo por su cuenta. En caso de que el elemento viva en el stack, no hace falta esta función, pero si uno quiere usar elementos en el heap, es imprescindible que dicho elemento se libere de la memoria al terminar con su uso.
	
#### Cuál es la complejidad de las diferentes operaciones del ABB 
	
- **Crear** :  **O(1)** | Unicamente se crea la estructura abb_t en el heap.

- **Buscar / Insertar / Borrar** : **O(n)** | Todas éstas funciones se caracterizan por la búsqueda, tanto buscar en sí, como insertar (la posición dónde insertar) y como borrar (la posicion del nodo a borrar y del nodo que reemplaza). En caso de este TDA sea un AVL, dónde el árbol se balance, estaríamos hablando de una complejidad 0 (log n). Sin embargo, como no es balanceado, cualquier operación de búsqueda, en el peor de los casos, termina teniendo una complejidad 0 (n) ya que puede degenerar en un lista.
	
- **vacio y raiz** : **O(1)** | Solo se evalua la existencia del arbol y de la raiz.
	
- **iterar / recorridos / destruir** : **O(n)** | Se debe recorrer todos los elementos del árbol tanto para iterarlo, como para recorrero o destruirlo. En el caso de iteración o recorridos puede ser menos (la función no itera todo o se llena el vector del recorrido), pero el peor de los casos es que los tenga que recorrer todos uno por uno.
	
