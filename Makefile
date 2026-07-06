
# make -> compila el proyecto
# make clean -> elimina el ejecutable

CC     = gcc
TARGET = snake
SRC    = main.c snake.c render.c audio.c
LIBS   = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)