#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "config.h"

bool game_is_running = false;
SDL_Window* window;
SDL_Renderer* renderer;
int last_frame_time = 0;

struct game_object {
    float posX;
    float posY;
    float width;
    float height;
    float velX;
    float velY;
} ball, paddle;

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
    paddle.width = 100;
    paddle.height = 15;
    paddle.velX = 0;
    paddle.velY = 0;
    paddle.posX = 320;
    paddle.posY = (WINDOW_HEIGHT - ball.height - 30);

    ball.width = 15;
    ball.height = 15;
    ball.velX = -90;
    ball.velY = 100;
    ball.posX = WINDOW_WIDTH / 2;
    ball.posY = WINDOW_HEIGHT / 2;
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

            if(event.key.keysym.sym == SDLK_LEFT){
                paddle.velX = -400;
            }

            if(event.key.keysym.sym == SDLK_RIGHT){
                paddle.velX = 400;
            }
            break;

        case SDL_KEYUP:
            if(event.key.keysym.sym == SDLK_LEFT){
                paddle.velX = 0;
            }

            if(event.key.keysym.sym == SDLK_RIGHT){
                paddle.velX = 0;
            }
            break;
    }
}

void update(){
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(time_to_wait > 0 && time_to_wait < FRAME_TARGET_TIME){
        SDL_Delay(time_to_wait);
    }

    float delta_time = (SDL_GetTicks() - last_frame_time)/1000.0f;
    last_frame_time = SDL_GetTicks();

    if(ball.posY + ball.height >= paddle.posY){
        if(ball.posX > paddle.posX && ball.posX < paddle.posX + paddle.width){
            ball.velY = -ball.velY;
        }
    }

    // it checks for colission on top of the window.
    if(ball.posY <= 0) {
        ball.velY = -ball.velY;
    }
    // it checks for colision with left window.
    if(ball.posX <= 0){
        ball.velX = - ball.velX;
    }
    // it checks for colision with right window.
    if(ball.posX + ball.width >= WINDOW_WIDTH){
        ball.velX = -ball.velX;
    }

    // it checks for the point and reset the game.
    if(ball.posY + ball.height >= WINDOW_HEIGHT){
        ball.velY = 100;
        ball.velX = 200;
        ball.posY = 200;
        ball.posX = 200;
    }


    ball.posX += ball.velX * delta_time;
    ball.posY += ball.velY * delta_time;
    paddle.posX += paddle.velX * delta_time ;

    printf("Paddle X: %.2f - sum: %.2f ball x: %.2f  y: %.2f\n", paddle.posX,paddle.posX + paddle.width, ball.posX, ball.posY );
}

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0,255);

    SDL_RenderClear(renderer);

    SDL_Rect paddle_rect;
    paddle_rect.x = paddle.posX;
    paddle_rect.y = paddle.posY;
    paddle_rect.w = paddle.width;
    paddle_rect.h = paddle.height;

    SDL_Rect ball_rect;
    ball_rect.x = ball.posX;
    ball_rect.y = ball.posY;
    ball_rect.w = ball.width;
    ball_rect.h = ball.height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255,255);
    SDL_RenderFillRect(renderer, &paddle_rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0,255);
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