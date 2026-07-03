#include "raylib.h"

#define ANCHO_PANTALLA 700
#define ALTO_PANTALLA  700

// Estados
typedef enum { MENU, JUEGO } Estado;

int main(void) {
    // Inicialización
    InitWindow(ANCHO_PANTALLA, ALTO_PANTALLA, "Snake");
    SetTargetFPS(60);

    Estado estado = MENU;
    
    // Definimos el botón como un rectángulo (x, y, ancho, alto)
    Rectangle btnIniciar = { ANCHO_PANTALLA/2.0f - 100, ALTO_PANTALLA/2.0f + 50, 200, 60 };

    // Bucle Principal
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        // Estados y controles
        if (estado == MENU) {
            // Detecta click en el botón o si se presiona ENTER
            bool clickBoton = CheckCollisionPointRec(mouse, btnIniciar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (clickBoton || IsKeyPressed(KEY_ENTER)) {
                estado = JUEGO;
            }
        } else if (estado == JUEGO) {
            // Salir del juego y volver al menú
            if (IsKeyPressed(KEY_ESCAPE)) estado = MENU;
        }

        // Renderizado
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (estado == MENU) {
            // Textos del menú
            DrawText("SNAKE", ANCHO_PANTALLA/2 - MeasureText("SNAKE", 80)/2, ALTO_PANTALLA/2 - 150, 80, DARKGREEN);
            DrawText("Proyecto en C", ANCHO_PANTALLA/2 - MeasureText("Proyecto en C", 20)/2, ALTO_PANTALLA/2 - 50, 20, GRAY);

            // Dibuja el botón interactivo (cambia de color si el mouse está encima)
            Color colorBtn = CheckCollisionPointRec(mouse, btnIniciar) ? GREEN : DARKGREEN;
            DrawRectangleRec(btnIniciar, colorBtn);
            DrawRectangleLinesEx(btnIniciar, 3, BLACK);
            DrawText("INICIAR", btnIniciar.x + (btnIniciar.width - MeasureText("INICIAR", 30))/2, btnIniciar.y + 15, 30, WHITE);

            DrawText("Presiona ENTER o click en INICIAR", ANCHO_PANTALLA/2 - MeasureText("Presiona ENTER o click en INICIAR", 16)/2, ALTO_PANTALLA/2 + 150, 16, DARKGRAY);
        } 
        else if (estado == JUEGO) {
            // Pantalla temporal del juego
            DrawText("Juego en progreso...", ANCHO_PANTALLA/2 - MeasureText("Juego en progreso...", 30)/2, ALTO_PANTALLA/2 - 20, 30, BLACK);
            DrawText("(ESC para volver)", ANCHO_PANTALLA/2 - MeasureText("(ESC para volver)", 18)/2, ALTO_PANTALLA/2 + 30, 18, GRAY);
            bool tecla_esc = IsKeyPressed(KEY_ESCAPE);
            if (tecla_esc){
                estado = MENU;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
