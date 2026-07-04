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

// Lee el teclado y actualiza la dirección que va a tomar la serpiente
// No permite dar media vuelta (ir en la dirección contraria)
void snake_input(Juego *j) {
    if (IsKeyPressed(KEY_RIGHT) && j->direccion.x != -1) {
        j->proxDir = (Vector2){ 1, 0 };
        audio_direccion(1, 0);
    }
    if (IsKeyPressed(KEY_LEFT) && j->direccion.x != 1) {
        j->proxDir = (Vector2){ -1, 0 };
        audio_direccion(-1, 0);
    }
    if (IsKeyPressed(KEY_UP) && j->direccion.y != 1) {
        j->proxDir = (Vector2){ 0, -1 };
        audio_direccion(0, -1);
    }
    if (IsKeyPressed(KEY_DOWN) && j->direccion.y != -1) {
        j->proxDir = (Vector2){ 0, 1 };
        audio_direccion(0, 1);
    }
}

// Mueve la serpiente un paso, revisa si comió algo o si murió
void snake_actualizar(Juego *j) {
    // Aplicar la dirección nueva
    j->direccion = j->proxDir;

    // Calcular la nueva posición de la cabeza
    Vector2 nuevaCabeza;
    nuevaCabeza.x = j->cuerpo[0].x + j->direccion.x * 25;
    nuevaCabeza.y = j->cuerpo[0].y + j->direccion.y * 25;

    // Revisar colisión con los bordes
    if (nuevaCabeza.x < 50 || nuevaCabeza.x >= 650 ||
        nuevaCabeza.y < 100 || nuevaCabeza.y >= 625) {
        j->vivo = 0;
        return;
    }

    // Revisar colisión consigo misma (ignorando la cola que va a desaparecer)
    for (int i = 0; i < j->longitud - 1; i++) {
        if (nuevaCabeza.x == j->cuerpo[i].x && nuevaCabeza.y == j->cuerpo[i].y) {
            j->vivo = 0;
            return;
        }
    }

    // Mover el cuerpo: cada segmento toma la posición del anterior
    for (int i = j->longitud - 1; i > 0; i--)
        j->cuerpo[i] = j->cuerpo[i - 1];
    j->cuerpo[0] = nuevaCabeza;

    // Ver si comió la comida
    if (nuevaCabeza.x == j->comida.x && nuevaCabeza.y == j->comida.y) {
        audio_comida();
        j->puntaje++;
        // Agregar un segmento al final si hay espacio
        if (j->longitud < MAX_SERPIENTE)
            j->longitud++;
        j->comida = snake_nueva_comida(j);
    }
}
