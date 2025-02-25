#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define TILE_WIDTH 64
#define TILE_HEIGHT 32

SDL_Window* window = NULL;
SDL_GLContext glContext;

void initSDL(void);
void closeSDL(void);
void initOpenGL(void);
void drawIsometricTile(float x, float y, float z);
void render(void);
void handleEvents(void);

int main(void) {
    initSDL();
    initOpenGL();


    int running = 1;
    while (running) {
        handleEvents();
        render();
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }

    closeSDL();
    return 0;
}

void initSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Isometric Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL) {
        printf("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (glewInit() != GLEW_OK) {
        printf("GLEW initialization failed!\n");
        exit(1);
    }
}

void closeSDL(void) {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void initOpenGL(void) {
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black

    glEnable(GL_TEXTURE_2D);
}

void drawIsometricTile(float x, float y, float z) {
    float isoX = (x - y) * TILE_WIDTH / 2;
    float isoY = (x + y) * TILE_HEIGHT / 2 - z * TILE_HEIGHT / 4;

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex2f(isoX, isoY);
    glVertex2f(isoX + TILE_WIDTH, isoY - TILE_HEIGHT);
    glVertex2f(isoX + TILE_WIDTH, isoY + TILE_HEIGHT);
    glVertex2f(isoX, isoY + TILE_HEIGHT);
    glEnd();
}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            drawIsometricTile(i, j, 0);
        }
    }
}

void handleEvents(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
    }
}
