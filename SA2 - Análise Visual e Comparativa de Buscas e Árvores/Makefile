CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c11
SRC     = src/main.c src/arvore.c src/buscas.c
TARGET  = busca_arvore

.PHONY: all clean run billion

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Habilita o experimento com 1 bilhao de elementos (exige muita RAM)
billion: $(SRC)
	$(CC) $(CFLAGS) -DENABLE_BILLION -o $(TARGET) $^

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) resultados/resultados.csv resultados/*.dot
