# Snake en C

Videojuego Snake en lenguaje C, utilizando la biblioteca Raylib para los gráficos, la ventana de juego y el audio. El jugador controla una serpiente con las teclas de dirección, come manzanas para crecer y sumar puntos, y pierde si choca con los bordes o consigo misma.

---

## Dependencias e instalación

El proyecto corre en Linux y requiere tener Raylib instalado manualmente desde el código fuente, ya que no está disponible como paquete en los repositorios por defecto de Ubuntu.

### 1. Instalar dependencias del sistema

```bash
sudo apt update
sudo apt install build-essential git \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev \
    libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
```

### 2. Compilar e instalar Raylib

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install RAYLIB_LIBTYPE=STATIC
sudo ldconfig
```

Para verificar que quedó instalado correctamente:

```bash
ls /usr/local/lib/libraylib.a
ls /usr/local/include/raylib.h
```

Si ambos archivos aparecen, Raylib está listo.

---

## Pasos para compilar y ejecutar

### Clonar el repositorio

```bash
git clone <url-del-repositorio>
cd <nombre-de-la-carpeta>
```

### Compilar

```bash
make
```

Esto genera el ejecutable `snake` en la misma carpeta.

Si no se tiene `make`, también se puede compilar manualmente:
```bash
gcc main.c snake.c render.c audio.c -o snake -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Ejecutar

```bash
./snake
```

Los archivos de audio (`.mp3`) deben estar en la misma carpeta desde donde se ejecuta el programa.

### Limpiar el ejecutable

```bash
make clean
```

---

## Cómo se juega

| Tecla | Acción |
| `up, down, right, left` | Mover la serpiente |
| `ENTER` | Iniciar el juego desde el menú |
| `ESC` | Salir del juego|

- Cada manzana que se come suma 1 punto y la serpiente crece.
- El juego termina si la serpiente choca con los bordes o consigo misma.

---

## Descripción del diseño

El proyecto está dividido en cuatro módulos, cada uno con su archivo `.c` y `.h`:

### `main.c`
Punto de entrada del programa. Maneja los tres estados del juego mediante un `enum`:
- `MENU` — muestra la pantalla de inicio con el botón Iniciar.
- `JUEGO` — corre el bucle del juego usando un timer con `GetFrameTime()` para que la serpiente se mueva a velocidad constante independientemente de los FPS.
- `GAMEOVER` — muestra el puntaje final y espera que el jugador presione ENTER para volver al menú o ESC para salir.

### `snake.c` / `snake.h`
Contiene toda la lógica del juego:
- `snake_init()` — inicializa la posición de la serpiente, la comida y el puntaje.
- `snake_input()` — lee el teclado y actualiza la dirección, bloqueando la media vuelta.
- `snake_actualizar()` — mueve la serpiente un paso, detecta colisiones con bordes y con el cuerpo propio, y verifica si se comió la manzana.
- `snake_nueva_comida()` — genera una posición aleatoria para la manzana que no caiga sobre la serpiente.

El estado completo del juego se guarda en un `struct Juego` que se pasa por puntero entre funciones.

### `render.c` / `render.h`
Separa todo el dibujo de la lógica:
- Dibuja la cuadrícula con dos tonos de verde alternados.
- Dibuja los bordes negros del área de juego.
- Dibuja la serpiente y la manzana.
- Dibuja el HUD con el puntaje en la parte superior.
- Dibuja la pantalla de game over con el puntaje final.

### `audio.c` / `audio.h`
Maneja los efectos de sonido usando la API de audio de Raylib:
- `audio_init()` — inicializa el dispositivo de audio y carga los cinco archivos `.mp3`.
- `audio_direccion()` — reproduce el sonido correspondiente al moverse (arriba, abajo, izquierda, derecha).
- `audio_comida()` — reproduce el sonido al comer una manzana.
- `audio_cerrar()` — libera los sonidos y cierra el dispositivo de audio.

### Archivos de audio
| Archivo | Evento |
|---|---|
| `upsnake.mp3` | Movimiento hacia arriba |
| `downsnake.mp3` | Movimiento hacia abajo |
| `leftsnake.mp3` | Movimiento hacia la izquierda |
| `rightsnake.mp3` | Movimiento hacia la derecha |
| `foodsnake.mp3` | Comer una manzana |