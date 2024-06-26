import heapq

# Crear un laberinto en una matriz de strings
def crear_laberinto():
    laberinto = [
"+----------------+",
"|S      +----+   |",
"| +--+  |    |   |",
"| |  |  | ++ |   |",
"| |  |  | ++ +--+|",
"| |  |  | ++    ||",
"| |  +--+ ++    ||",
"| |      |      ||",
"| +----+ +--+   ||",
"|      |    |   ||",
"| +----+    +----|",
"|        E       |",
"+----------------+"
    ]
    return [list(fila) for fila in laberinto]

# Implementar el algoritmo A* sin heurística
def a_estrella(laberinto, inicio, fin):
    filas = len(laberinto)
    columnas = len(laberinto[0])

    # Movimientos posibles: derecha, izquierda, abajo, arriba
    movimientos = [(1, 0), (-1, 0), (0, 1), (0, -1)]

    # Cola de prioridad
    frontera = []
    heapq.heappush(frontera, (0, inicio))

    # Diccionarios para el costo y el camino
    costo_acumulado = {inicio: 0}
    came_from = {inicio: None}

    while frontera:
        _, actual = heapq.heappop(frontera)

        if actual == fin:
            break

        for movimiento in movimientos:
            x, y = actual
            dx, dy = movimiento
            siguiente = (x + dx, y + dy)

            if 0 <= siguiente[0] < filas and 0 <= siguiente[1] < columnas and laberinto[siguiente[0]][siguiente[1]] not in ('+', '|', '-'):
                nuevo_costo = costo_acumulado[actual] + 1

                if siguiente not in costo_acumulado or nuevo_costo < costo_acumulado[siguiente]:
                    costo_acumulado[siguiente] = nuevo_costo
                    heapq.heappush(frontera, (nuevo_costo, siguiente))
                    came_from[siguiente] = actual

    # Reconstruir el camino
    actual = fin
    camino = []
    while actual != inicio:
        camino.append(actual)
        actual = came_from[actual]
    camino.append(inicio)
    camino.reverse()

    return camino

# Mostrar el laberinto
def mostrar_laberinto(laberinto):
    for fila in laberinto:
        print("".join(fila))

# Mostrar el laberinto con el camino resuelto
def mostrar_laberinto_con_camino(laberinto, camino):
    for x, y in camino:
        if laberinto[x][y] not in ('S', 'E'):
            laberinto[x][y] = '*'
    mostrar_laberinto(laberinto)

# Ejecutar el código
laberinto = crear_laberinto()
inicio = (1, 1)
fin = (10, 8)

print("Laberinto sin resolver:")
mostrar_laberinto(laberinto)

camino = a_estrella(laberinto, inicio, fin)

print("\nLaberinto resuelto:")
mostrar_laberinto_con_camino(laberinto, camino)