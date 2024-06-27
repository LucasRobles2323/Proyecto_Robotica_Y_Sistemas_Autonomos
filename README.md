# Proyecto ICI4150-1- ROBOTICA Y SISTEMAS AUTONOMOS(1S2024)

## Integrantes

- Gerald Espinoza
- Lucas Robles

## Descripción

Este proyecto se realiza en conjunto con el proyecto del ramo **ICI4247-1- INGENIERIA WEB Y MOVIL(1S2024)** y fue seleccionada la propuesta de Proyecto 2: 

Se requiere un robot autónomo que pueda recorrer el siguiente laberinto, donde el robot pueda encontrar la salida. El camino debe tener en cuenta las limitaciones del vehículo para evitar colisiones. Al completar el laberinto, tu robot debería celebrar girando dos veces en el sentido de las agujas del reloj y luego dos giros en el sentido contrario a las agujas del reloj. La meta está marcada por el círculo rojo. Para aproximaciones de distancia, todos los bloques grises miden 50 cm * 10 cm.

![Propuesta 2](Otros//ImagenesReadme/IdeaProyecto.png)

##### Entrega Final


- EF1.1: Implementar un algoritmo, el cual puede ser : localización bayesiana, a*, Dijkstra
- EF1.2: Puesta en marcha del robot en el escenario propuesto con el algoritmo que permita realizar un comportamiento autónomo.
- EF1.3: Interfaz de monitoreo.

## Respuestas Entrega Final

### EF1.1: Implementar un algoritmo, el cual puede ser : localización bayesiana, a*, Dijkstra

Se hizo un algoritmo A* para recorrer el laberinto.

Este código implementa una solución para encontrar el camino más corto en un laberinto utilizando el algoritmo A* sin heurística. Aquí está el desglose de las partes del código:

Función crear_laberinto:

- Crea y retorna una representación del laberinto como una lista de listas de caracteres, donde cada carácter representa una celda del laberinto.
Función a_estrella:

- Implementa el algoritmo A* para encontrar el camino más corto desde un punto de inicio hasta un punto final en el laberinto.
- Utiliza una cola de prioridad para explorar las celdas del laberinto y un diccionario para registrar el costo acumulado para llegar a cada celda y el camino seguido.

Función mostrar_laberinto:

- Imprime el laberinto en la consola.
- Función mostrar_laberinto_con_camino:

Toma el laberinto y el camino encontrado por el algoritmo A*, marca el camino en el laberinto con asteriscos ('*'), y luego imprime el laberinto.
Ejecución del código:

- Se crea el laberinto y se define el punto de inicio y el punto final.
- Se muestra el laberinto sin resolver.
- Se ejecuta el algoritmo A* para encontrar el camino desde el inicio hasta el final.
- Se muestra el laberinto con el camino resuelto marcado.
El código proporciona una forma visual y programática de resolver un laberinto utilizando un enfoque algorítmico eficiente.



### EF1.2: Puesta en marcha del robot en el escenario propuesto con el algoritmo que permita realizar un comportamiento autónomo.

El escenario propuesto se compone de este laberinto: 

![algotimo 2](Otros//imagenesReadme/Screenshot2024-06-26210743.png)

Los asteriscos presentes en el escenario porpuesto representan un comando que el robot recibirá para efectuar un movimiento.

El laberinto solucionado contiene un total de 19 asteriscos, cada uno representando una acción traducida a movmiento en el robot, cada esquina contando como 2 movimientos debido a que debe realizar el movimento hacia adelante para posicionarse en la casilla y luego girarse.

9 movimientos frontales, un giro a la izquierda en 90° y 8 movimientos frontales -> 18 movimientos totales

Por lo que la sucecsión de acciones sería 

[F,F,F,F,F,F,F,F,L,F,F,F,F,F,F,F,F]

- F: Movimiento frontal

- L: Movimiento en 90° hacia la izquierda

En este ejemplo se usan solo esos movimientos.

Movimeintos del robot 

- F: Movimiento frontal

- L: Movimiento en 90° hacia la izquierda

- R: Movimiento en 90° hacia la derecha

- B: Movimiento hacia atrás

###  EF1.3: Interfaz de monitoreo.


Se intento usar la aplicacion movil desarrollada en el curso de Web como interfaz de monitoreo, debido a la naturaleza móvil de la aplicación era necesario tener un sistema que mantuviera el server corriendo de manera no local para así poder conectrase desde dispositivos móviles. Para realizar la conexión se utilizó la plataforma de google cloud para que así el intercambio de datos entre el robot y la página web fuera posible. No fue posible realizar dicha conexión.

Se intentó subir el backend de la página web a google cloud para así poder conectar el robot con la página y que esta recibiera los datos, no fue posible hacer dicha conexión.


