#include "raylib.h"
#include "audio.h"

// Variables globales del módulo
static Sound snd_arriba;
static Sound snd_abajo;
static Sound snd_derecha;
static Sound snd_izquierda;
static Sound snd_comida;

// Inicializa el dispositivo de audio y carga los archivos mp3
// Hay que llamar esto antes de usar cualquier otra función de audio
void audio_init(void) {
    InitAudioDevice();

    snd_arriba = LoadSound("upsnake.mp3");
    snd_abajo = LoadSound("downsnake.mp3");
    snd_derecha = LoadSound("rightsnake.mp3");
    snd_izquierda = LoadSound("leftsnake.mp3");
    snd_comida = LoadSound("foodsnake.mp3");
}

// Reproduce el sonido que corresponde según la dirección
// dx y dy son los valores de la dirección actual de la serpiente
void audio_direccion(int dx, int dy) {
    if (dx == 1) PlaySound(snd_derecha);
    else if (dx == -1) PlaySound(snd_izquierda);
    else if (dy == -1) PlaySound(snd_arriba);
    else if (dy == 1) PlaySound(snd_abajo);
}

// Se llama cuando la serpiente se come la manzana
void audio_comida(void) {
    PlaySound(snd_comida);
}

// Libera la memoria de los sonidos y cierra el dispositivo
void audio_cerrar(void) {
    UnloadSound(snd_arriba);
    UnloadSound(snd_abajo);
    UnloadSound(snd_derecha);
    UnloadSound(snd_izquierda);
    UnloadSound(snd_comida);
    CloseAudioDevice();
}