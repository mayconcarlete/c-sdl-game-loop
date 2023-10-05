#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "config.h"

bool game_is_running = false;
SDL_Window* window;
SDL_Renderer* renderer;
int last_frame_time = 0;

struct ball {
    float x;
    float y;
    float width;
    float height;
} ball ;

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

void setup(){
    // todo
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height = 15;
}

void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            game_is_running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                game_is_running = false;
            }
            break;
    }
}

void update(){
    // todo:
    // Logic to keep the timestep
    // while(!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME){
        SDL_Delay(time_to_wait);
    }
    
    float delta_time = (SDL_GetTicks() - last_frame_time)/1000.0f; // get delta time factor to convert from pixel/frame to pixels/second

    ball.x +=  delta_time * 70;
    ball.y += delta_time * 50;



    last_frame_time = SDL_GetTicks();
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);

    SDL_RenderClear(renderer);

    // draw here;
    SDL_Rect ball_rect = {
        ball.x,
        ball.y,
        ball.width,
        ball.height
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    SDL_RenderFillRect(renderer, &ball_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(){
    game_is_running = initialize_window();
    if(game_is_running == false){
        return -1;
    }

    setup();

    while(game_is_running){
       process_input();
       update();
       render();
    }
out:
    destroy_window();
    return 0;
}