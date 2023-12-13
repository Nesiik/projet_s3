#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "sprite.h"
#include "world.h"

#define PLAYER_SPRITE_SIZE 64

enum States { REST=0, WALK=1, TAKEOFF =2, FLIGHT=3, FALL=4, LANDING=5 }; // will be use for animation (hopefully)

typedef struct player_s{
    double x,y;
    double vx,vy;
    //Uint64 time;
    int state;
    sprite* sprite;
    unsigned char backward;
}player_t;

player_t* init_player(SDL_Renderer *renderer);
void move_player(player_t* player,world_t* world,double dt);
void print_state(player_t* player);
void handle_keyboard_player(player_t* player);
void render_player(SDL_Renderer* renderer, const player_t* player);
void free_player(player_t* player);

#endif