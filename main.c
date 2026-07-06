#include "raylib.h"
#include "snake.h"
#include "render.h"
#include "audio.h"

#define ANCHO 700
#define ALTO  700

// Los mismos estados que en menu.c pero ahora con uno más para game over
typedef enum { MENU, JUEGO, GAMEOVER } Estado;

// Código del menú (lo mismo que menu.c pero integrado aquí)
static void dibujar_menu(Rectangle btn, Vector2 mouse) {
    ClearBackground(RAYWHITE);

    DrawText("SNAKE", ANCHO/2 - MeasureText("SNAKE", 80)/2, ALTO/2 - 150, 80, DARKGREEN);
    DrawText("Proyecto en C", ANCHO/2 - MeasureText("Proyecto en C", 20)/2, ALTO/2 - 50, 20, GRAY);

    Color colorBtn = CheckCollisionPointRec(mouse, btn) ? GREEN : DARKGREEN;
    DrawRectangleRec(btn, colorBtn);
    DrawRectangleLinesEx(btn, 3, BLACK);
    DrawText("INICIAR", btn.x + (btn.width - MeasureText("INICIAR", 30))/2, btn.y + 15, 30, WHITE);

    DrawText("Presiona ENTER o click en INICIAR",
             ANCHO/2 - MeasureText("Presiona ENTER o click en INICIAR", 16)/2,
             ALTO/2 + 150, 16, DARKGRAY);
}

int main(void) {
    InitWindow(ANCHO, ALTO, "Snake");
    SetTargetFPS(60);
    audio_init();

    Estado estado = MENU;
    Juego juego;

    // Botón del menú
    Rectangle btnIniciar = { ANCHO/2.0f - 100, ALTO/2.0f + 50, 200, 60 };

    // Timer para controlar cuándo se mueve la serpiente
    // (no se mueve cada frame, sino cada x segundos según la velocidad)
    float timer  = 0.0f;
    float intervalo = 1.0f / 10.0f;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        //Lógica por estado
        if (estado == MENU) {
            bool click = CheckCollisionPointRec(mouse, btnIniciar) &&
                         IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (click || IsKeyPressed(KEY_ENTER)) {
                snake_init(&juego);
                timer = 0.0f;
                intervalo = 1.0f / 10.0f;
                estado = JUEGO;
            }
        }
        else if (estado == JUEGO) {
            snake_input(&juego);  // leer teclado siempre, no solo al actualizar

            timer += GetFrameTime();
            if (timer >= intervalo) {
                timer = 0.0f;
                snake_actualizar(&juego);

                if (!juego.vivo)
                    estado = GAMEOVER;
            }
        }
        else if (estado == GAMEOVER) {
            if (IsKeyPressed(KEY_ENTER))
                estado = MENU;
        }

        // Dibujo
        BeginDrawing();

        if (estado == MENU)
            dibujar_menu(btnIniciar, mouse);
        else if (estado == JUEGO)
            render_juego(&juego);
        else if (estado == GAMEOVER)
            render_gameover(juego.puntaje);

        EndDrawing();
    }

    audio_cerrar();
    CloseWindow();
    return 0;
}