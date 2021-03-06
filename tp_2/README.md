Trabajo Práctico 2
=============

## Descripción general

El trabajo consiste en la implementación del juego "Pokemon Journey", inspirado en la serie japonesa de televisión Pokémon. Dentro de este trabajo se emplean conocimientos sobre la utilización de Tipo de Datos Abstractos (TDA), tales como Pila, Cola, Lista, ABB y Heap, además del uso de estructuras personalizada (dónde se emplea la útilización de memoria dinámica). 

El juego consiste en el recorrido de un personaje principal por varios gimnasios, dónde luchará contra otros entrenadores. Una vez derrotado el líder de cada gimnasio, hará acumulado todas las medallas, y por lo tanto se consagrará como Maestro Pokémon. El juego tiene dos modos, un juego manual, donde se irá progresando batalla a batalla contra cada entrenador, y un juego simulado, donde éste proceso será automático, limitándose a mostrar una información básica de cada batalla y culminando en la derrota o en la victoria de la partida.

------------------------------------------------------------------------

## Organización

La implementación del juego está divida en varios archivos y carpetas que facilitan a la organización de la misma. Éstas carpetas están organizadas según las distintas partes del trabajo: La implementación; Las pruebas realizadas a la misma; Las herramientas utilizadas (previamente implementadas en los anteriores trabajos); y los archivos, en los cuales se encuentra la información necesaria para la ejecución del programa.

#### code

En esta carpeta se incluye los librerías exclusivas para éste juego. Entre ellas se encuentran:
      
  - **estructuras.h**: Funciones de creación y utilización de las estructuras más generales del juego, pokemon_t,entrenador_t, personaje_t y gimnasio_t.***1** Estas estructuras se utilizarán como base en los próximos archivos.
       
  - **batallas.h**: Funciones de batalla entre pokemones para los enfrentamientos de los gimnasios
      
  - **interfaz.h**: Funciones relacionadas con información visual (interacción del usuario por consola) y con la creación  y utilización de la estructura interfaz_t.***1** 
      
  - **juego.h**: Funciones relacionadas al funcionamiento interno del juego y con la creación y utilización de juego_t ***1** y lectura de archivos.


***1** - Serán explicadas y desarrolladas más adelante en el aparado Estructuras.

#### test
     
Dentro de esta carpeta, se encuentran los códigos y archivos relacionados con las pruebas de toda la implementación y sus distintas partes:

  - **pruebas_heap.c**: Pruebas unitarias del TDA heap.
  - **pruebas_interfaz.c**: Pruebas de la interfaz (pruebas visuales).
  - **pruebas_juego.c**: Pruebas unitarias del juego y de sus estructuras.(cargar y destruir personaje y gimnasios)
  - **txt**: Carpeta que incluyen los archivos para testear para el juego

#### toolbox
     
Dentro de ésta carpeta se encuentran las diferentes herramientas utilizadas en el resto de archivos, como los TDA
y las funciones de testeo (tools.c), además de incluir las constantes como colores (secuencia de escape ANSI), ERROR, EXITO y las inclusiones de la libería standard.

#### txt

Ésta carpeta está destinada a los archivos de textos requeridos para jugar el juego, es decir, los archivos de los gimnasios y el personaje. En este se puede agregar archivos, si el usuario los desea, siempre y cuando cumplan con los formatos predefinidos.

  El formato de las lineas de los archivos es el siguiente: 
      
      G;nombre_gimnasio; dificultad; id_funcion [valor entre 1 y 5]
 
      L;nombre_lider
 
      E;nombre_entrenador
      
      P;nombre_pokemon; velocidad; ataque; defensa

------------------------------------------------------------------------

## Compilación y Ejecución

Para compilar y ejecutar el programa, se hizo utilización de un archivo Makefile con los siguiente comandos:
      
      make juego     : Compila el archivo main.c junto a los archivos de code.
      
      make play      : Ejecuta el juego. (./juego)
      
      make test      : Compila y ejecuta el archivo de testeo del juego.
      
      make interfaz  : Compila y ejecuta el archivo de testeo de la interfaz.
      
      make heap      : Compila y ejecuta el archivo de testeo del heap.

Una vez ejecutado el juego, la forma standard de jugarlo, es incluyendo el archivo de personaje "txt/personaje.txt" y el archivo de los gimnasios del kanto, "txt/kanto.txt". Sin embargo, siguiendo el formato de la consigna, cada uno puede agregar nuevos archivos o modificar los actuales. 

------------------------------------------------------------------------

## Estructuras

#### pokemon_t
  
Ésta es de las estructuras más sencillas, ya que no contiene ningun puntero que necesite crearse y destruirse, simplemente contiene las características básicas del Pokémon (Ataque, Defensa y Velocidad), un booleano que indica si esta seleccionado dentro del party del personaje (el cual siempre será falso en los entrenadores, ya que no cuentan con dicha distinción) y finalmente un indicador del nivel del mismo, cuyo máximo es 63 (cantidad de puntos bonificados)

#### entrenador_t
  
El entrenador unicamente tiene la información de su nombre y un lista de pokemones, donde se guardaran como máximo 6 y deberá tener al menos uno para ser considerado válido. Éste último campo, el conjunto de pokemones, podría ser un vector, ya que la cantidad máxima es constante, sin embargo por una cuestión de facilitar la impresión por pantalla de la misma, ya que hay una función particular para eso que comparte con los campos del personaje. Así mismo, no podría no ser una lista o un vector, ya que se necesita poder acceder a todos los elementos sin tener que borrarlos, tanto para poder avanzar para cada batalla o mostrarlos por pantalla o para tomar un pokemon en caso de que sea un líder.

#### personaje_t

El personaje contiene la información de su nombre, la cantidad de medallas (gimnasios ganados) y dos listas de pokemones, el party (pokemones de combate) y la caja (pokemones obtenidos). La caja contiene todos los pokemones del personaje, y el party, la copia (es importante para la destrucción de los elementos) de aquellos pokemones elegidos para batallar. Éste último campo, tambien podría ser un vector, ya que al igual que la lista de pokemones del entrenador tiene un 6 pokemones como máximo (no así el caso de la caja que es ilimitada), y por el mismo motivo que antes, se prefirió una lista. Del mismo modo, en éstos campos se debe acceder a todos los elementos, por lo que no podría ser ni cola ni pila.

#### gimnasio_t

El gimnasio contiene su propia información, es decir, su nombre, su dificultad y el id de la función batalla que se debe usar al momento de las batalla, y a su vez, tiene una pila de entrenadores, donde se iran almacenando los entrenadores, de forma tal que el primer elemento, y por ende el último a desapilarse, sea el Líder del gimnasio. Para que un gimnasio sea considerado válido, deberá contar con al menos un Líder y un entrenador, ambos con al menos un pokemon.

#### interfaz_t
  
La interfaz es un tipo de dato que se utilizarán dentro del juego, y en la cual se contiene la infomación necesaria para poder mostrar los diferentes menús para la interacción con el jugador. Es por esto que tiene un campo que respresenta el estado, es decir la elección del jugador en el menú que se haya ejecutado, un vector de menús, que será creado en el heap y tendrá una cantidad fija de 5 menus (Inicio, Gimnasio, Batalla, Derrota y Victoria). La estructura particular de menu_t tendra las diferentes opciones posibles y sus descripciones.

#### juego_t

El juego contiene a todas las estructuras anteriormente nombraradas, tendrá un personaje_t, un heap minimal de gimnasios (contiene a todos los gimnasios_t del juego y por lo tanto a todos los entrenadores), para poder acceder directamente al gimnasio de menor dificulata (el próximo a luchar), la interfaz_t y finalmente un campo que indique el estado del juego, si está jugando, si ganó, perdió o hubo un error.

------------------------------------------------------------------------

## Consideraciones finales
    
- **Cargar gimnasios**

Por una cuestión de practicidad, consideré necesario que la carga de gimnasios no sea de manera individual, sino que el archivo contenga todos los gimnasios que requerirá el juego. Por lo tanto, para incluir gimnasios, se podrian escribir dentro del archivo actual o realizar un nuevo archivo con todos los gimnasios del juego.

- **Casos limite de los archivos**

Al momento de leer los archivos, consideré que cualquier error en formato implicara no cargar ninguna estructura y devolver error, cortando con la ejecución del juego. El motivo es para no suponer nunca que el usuario haya querido poner un entrenador sin pokemones o un gimnasio sin entrenadores a propósito, sino dar la posibilidad de que sea un equivocación, y por lo tanto no tener en cuenta el archivo completo.

- **Derrota en la simulación**

Por más que no especifique la consigna, me pareció oportuno que una vez se pierda, poder mandar el menú de derrota para que el jugador decida si quiere hacer un cambio de pokemones y volver a simular, o directamente salir del juego. Ya que si en el caso contrario, cortara el juego o lo mandara de nuevo al inicio, únicamente podria cambiar los pokemones modificando la formación del archivo.

- **Menú Gimnasio**

Al no especificarse exactamente el momento en el que se usa, si exclusivamente al principio de cada gimnasio, o en el caso que lo usé, como un separador entre cada batalla con un entrenador, me decanté por ésto último por varios motivos. En el caso de que unicamente se utilizara este menú para el inicio de un gimnasio, ésta seria la única vez en todo el gimnasio para poder modificar el party, y a su vez, éste menú, por la forma en que lo implementé, solo muestra como información del gimnasio al entrenador siguiente para combatir. Por éstos motivos, consideré oportuno darle al jugador la posibilidad de cambiar de pokemones de combate entre cada enfrentamiento con un entrenador y al comienzo del gimnasio, y así mismo, poder brindarle la información del gimnasio (y por ende la del próximo entrenador). 
