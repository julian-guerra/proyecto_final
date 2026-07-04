#include "raylib.h"
#include "snake.h"
#include "audio.h"

// Inicializa el estado del juego desde cero
void snake_init(Juego *j) {
    // La serpiente arranca en el centro más o menos
    j->cuerpo[0] = (Vector2){ 350, 350 };
    j->cuerpo[1] = (Vector2){ 325, 350 };
    j->cuerpo[2] = (Vector2){ 300, 350 };
    j->longitud = 3;

    j->direccion = (Vector2){ 1, 0 };  // empieza moviendose a la derecha
    j->proxDir   = (Vector2){ 1, 0 };

    j->comida = snake_nueva_comida(j);
    j->puntaje = 0;
    j->vivo = 1;
}

// Genera una posición aleatoria para la comida dentro del área de juego
// El área va de x=50 a x=650 y de y=100 a y=625, en celdas de 25px
Vector2 snake_nueva_comida(Juego *j) {
    Vector2 pos;
    int ok;

    // Sigue intentando hasta que la comida no caiga encima de la serpiente
    do {
        ok = 1;
        int col = GetRandomValue(2, 23);  // columnas disponibles
        int fil = GetRandomValue(4, 20);  // filas disponibles
        pos.x = 50 + col * 25;
        pos.y = 100 + fil * 25;

        for (int i = 0; i < j->longitud; i++) {
            if (j->cuerpo[i].x == pos.x && j->cuerpo[i].y == pos.y) {
                ok = 0;
                break;
            }
        }
    } while (!ok);

    return pos;
}


