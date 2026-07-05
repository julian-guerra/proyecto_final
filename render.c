#include "raylib.h"
#include "snake.h"
#include "render.h"

// Dibuja la cuadrícula del área de juego con dos tonos de verde
// El área va de (50,100) a (650,625), celdas de 25x25
void render_cuadricula(void) {
    Color verde1 = { 0, 200, 0, 255 }; // verde claro
    Color verde2 = { 0, 100, 0, 255 }; // verde oscuro

    for (int x = 50; x < 650; x += 25) {
        for (int y = 100; y < 625; y += 25) {
            // Alterna colores
            int col = (x - 50) / 25;
            int fil = (y - 100) / 25;
            Color c = ((col + fil) % 2 == 0) ? verde1 : verde2;
            DrawRectangle(x, y, 25, 25, c);
        }
    }
}

// Dibuja las líneas negras que marcan los límites del área de juego
void render_bordes(void) {
    DrawRectangle(47,97,606,5,BLACK); // arriba
    DrawRectangle(47,97,5,531,BLACK); // izquierda
    DrawRectangle(47,623,606,5,BLACK); // abajo
    DrawRectangle(648,97,5,531,BLACK); // derecha
}

// Dibuja cada segmento de la serpiente en color celeste
void render_serpiente(Juego *j) {
    for (int i = 0; i < j->longitud; i++)
        DrawRectangle((int)j->cuerpo[i].x, (int)j->cuerpo[i].y, 25, 25, (Color){0, 255, 255, 255});
}