#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"

#define MAX_SERPIENTE 256  // tamaño máximo que puede crecer la serpiente

// Toda la info del juego en un struct
typedef struct {
    Vector2 cuerpo[MAX_SERPIENTE]; // posiciones de cada segmento
    int     longitud; // cuántos segmentos tiene ahora
    Vector2 direccion; // hacia donde va en este frame
    Vector2 proxDir; // hacia donde va a ir en el próximo update
    Vector2 comida; // posición de la comida
    int     puntaje;
    int     vivo; // 0 = game over
} Juego;

// Prototipos
void    snake_init(Juego *j);
Vector2 snake_nueva_comida(Juego *j);
void    snake_input(Juego *j);
void    snake_actualizar(Juego *j);

#endif