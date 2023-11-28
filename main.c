#include <SDL.h>
#include <SDL_ttf.h>
#include "sdl.h"
#include "option.h"
#include "player.h"

void init(SDL_Renderer * renderer, ressources_t *textures, world_t * world, player_t * player){
    //get_window_options();
    init_data(world);
    init_ressources(renderer, textures);
    init_player(renderer,player);
}

int main( int argc, char* args[] )
{
    SDL_Event* event = malloc(sizeof(SDL_Event));
    world_t* world = malloc(sizeof(world_t));
    ressources_t* ressources = malloc(sizeof(ressources_t));
    player_t* player = malloc(sizeof(player_t));
    
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
        printf("%s",SDL_GetError());
    }
    if(TTF_Init() < 0){
        printf("%s",SDL_GetError());
    }
    if(IMG_Init(IMG_INIT_PNG) == 0){
        printf("%s",SDL_GetError());
    }

    SDL_Window* window = create_window();
    SDL_Renderer *renderer = create_renderer(window);

    init(renderer,ressources,world,player);
    set_full_screen(window,FakeFS);
    SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "0");
    int* r;
    while(!fin(world)){
        if(SDL_RenderClear(renderer) < 0){
            printf("%s",SDL_GetError());
        }
        handle_events(event,world,ressources,player);
        render_worlds(renderer,ressources,world);
        switch (world->gameover)
        {
            case Menu:
                render_main_menu_text(renderer,ressources);
                break;
            case Alive:
                render_player(renderer,player);
                /*unsigned int time_limit; // a deplacer dans alive plus tard
                unsigned int timer = SDL_GetTicks();    
                unsigned int countdown = (time_limit - timer)/1000; 
                afficher_texte(renderer,"../assets/arial.ttf",countdown,900,600);   //a deplacer dans alive plus tard
                */
                //printf("resultat collision : %d \n",world_collision(world,&player->pos)); //%d \n
                r = get_dirt_level(world,&player->pos);
                if(r== NULL ){
                    break;
                }
                printf("x dirt : %d , y dirt : %d \n",r[0],r[1]);
                free(r);
                //world_collision(world,&player->pos);
                break;
            default:
                break;
        }
        SDL_RenderPresent(renderer);
    }
    
    TTF_CloseFont(ressources->font);
    free(event);
    free_levels(world);
    free(world);
    free_ressources(ressources);
    free(ressources);
    free_player(player);
    free(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}