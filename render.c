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

// Dibuja la comida como un cuadrado rojo
void render_comida(Juego *j) {
    DrawRectangle((int)j->comida.x, (int)j->comida.y, 25, 25, RED);
}

// Dibuja el título "SNAKE" y el puntaje
void render_hud(int puntaje) {
    DrawText("SNAKE", 400, 20, 60, DARKBLUE);
    DrawText("Puntuacion:", 50, 40, 22, BLACK);
    DrawText(TextFormat("%d", puntaje), 185, 40, 22, BLACK);
}

// Pantalla de game over con el puntaje final
void render_gameover(int puntaje) {
    ClearBackground(RAYWHITE);
    DrawText("GAME OVER", 700/2 - MeasureText("GAME OVER", 60)/2, 250, 60, RED);
    DrawText(TextFormat("Puntaje: %d", puntaje),
             700/2 - MeasureText(TextFormat("Puntaje: %d", puntaje), 28)/2,
             330, 28, DARKGRAY);
    DrawText("Presiona ENTER para volver al menu",
             700/2 - MeasureText("Presiona ENTER para volver al menu", 18)/2,
             390, 18, GRAY);
}

// Dibuja todo lo del juego de una vez
void render_juego(Juego *j) {
    ClearBackground(RAYWHITE);
    render_cuadricula();
    render_bordes();
    render_comida(j);
    render_serpiente(j);
    render_hud(j->puntaje);
}