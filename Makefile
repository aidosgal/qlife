CC = gcc
SRC = src/main.c
TARGET = qlife
CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2` -I/usr/local/include
# macOS specific linking for OpenGL
LIBS = `pkg-config --libs sdl2` -framework OpenGL -L/usr/local/lib -lGLEW

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o bin/$(TARGET) $(LIBS)

clean:
	rm -rf bin/$(TARGET)

run: all
	./bin/$(TARGET)

.PHONY: all clean run
