#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "config.h"

SDL_Window* window;
SDL_Renderer* renderer;

bool initialize_window(void){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(!window){
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        0
    );
    if(!renderer){
        fprintf(stderr, "Error creating SDL Renderer.\n");
    }
    return true;
}


int main(){
    bool initialize_is_success = initialize_window();
    if(initialize_is_success == false){
        return -1;
    }
    printf("Hello from peskland\n");
    return 0;
}