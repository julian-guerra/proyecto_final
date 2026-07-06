#ifndef RENDER_H
#define RENDER_H

#include "snake.h"

void render_cuadricula(void);
void render_bordes(void);
void render_serpiente(Juego *j);
void render_comida(Juego *j);
void render_hud(int puntaje);
void render_gameover(int puntaje);
void render_juego(Juego *j);

#endif