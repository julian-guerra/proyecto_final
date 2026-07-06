#ifndef AUDIO_H
#define AUDIO_H

// Carga todos los sonidos al iniciar
void audio_init(void);

// Reproduce el sonido según la dirección que tomó la serpiente
void audio_direccion(int dx, int dy);

// Reproduce el sonido de cuando se come la comida
void audio_comida(void);

// Libera los sonidos al cerrar
void audio_cerrar(void);

#endif