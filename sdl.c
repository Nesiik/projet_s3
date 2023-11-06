#include "sdl.h"

void handle_events(SDL_Event *event,world_t *world , ressources_t* ressources){
    while( SDL_PollEvent( event ) ) {
        switch (event->type){
        case SDL_QUIT:
            world->gameover = Quit;
            break;
        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = Quit;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch (world->gameover)
            {
            case Menu:
                if (event->button.button == SDL_BUTTON_LEFT) {
                int mouseX = event->button.x;
                int mouseY = event->button.y;

                for (char i = 0; i < MAIN_MENU_ITEM_COUNT; i++) {
                    Item menuItem = ressources->MenuItems.ItemList[i];

                    if (mouseX >= menuItem.rect.x && mouseX <= menuItem.rect.x + menuItem.rect.w &&
                        mouseY >= menuItem.rect.y && mouseY <= menuItem.rect.y + menuItem.rect.h)
                    {
                        ressources->MenuItems.selectedItem = i;
                        switch (i) {
                            case 0: // Jouer
                                //init_data(world);
                                //world->gameover = Alive;
                                //world->depart = SDL_GetTicks();
                                break;
                            case 1: // Option
                                break;
                            case 2: // Quitter
                                world->gameover = Quit;
                                break;
                            
                            default:
                                break;
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}


void render_main_menu(SDL_Renderer *renderer,ressources_t *ressources){
    for (int i = 0; i < MAIN_MENU_ITEM_COUNT; i++) {
        SDL_Color color;

        if(i == ressources->MenuItems.selectedItem){
            color = (SDL_Color){ 180, 180, 180 };
        }
        else{
            color = (SDL_Color){ 100, 100, 100 };
        }

        SDL_Surface* surface = TTF_RenderText_Solid(ressources->font, ressources->MenuItems.ItemList[i].text,  color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        if(ressources->MenuItems.ItemList[i].rect.w == 0 || ressources->MenuItems.ItemList[i].rect.h == 0){
            SDL_QueryTexture(texture, NULL, NULL, &ressources->MenuItems.ItemList[i].rect.w, &ressources->MenuItems.ItemList[i].rect.h);
        }

        SDL_RenderCopy(renderer, texture, NULL, &ressources->MenuItems.ItemList[i].rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}


void afficher_texte(SDL_Renderer* renderer, TTF_Font* police, const char text[], int x, int y ) {
	SDL_Color fg = { 255, 255, 255 };
	SDL_Surface* surf = TTF_RenderText_Solid(police,text, fg);

    SDL_Rect dest = {x,y,surf->w,surf->h};
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_RenderCopy(renderer, tex, NULL, &dest);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(surf);
}

SDL_Window* create_window(){
    SDL_Window* window = SDL_CreateWindow(
    "SDL2Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    1280, 
    720, 
    SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        printf("Erreur lors de la creation de l'image : %s", SDL_GetError());
    }
    return window;
}

SDL_Renderer* create_renderer(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        printf("Erreur lors de la creation du renderer : %s", SDL_GetError());
    }
    return renderer;
}


void init_ressources(SDL_Renderer *renderer, ressources_t* ressources){
    ressources->font = TTF_OpenFont("../assets/arial.ttf",28);
    
    ressources->MenuItems.ItemList[0].rect = (SDL_Rect){100,200,0,0};
    ressources->MenuItems.ItemList[0].text = "Jouer";
    ressources->MenuItems.ItemList[1].rect = (SDL_Rect){100,250,0,0};
    ressources->MenuItems.ItemList[1].text = "Options";
    ressources->MenuItems.ItemList[2].rect = (SDL_Rect){100,300,0,0};
    ressources->MenuItems.ItemList[2].text = "Quitter";

    ressources->MenuItems.selectedItem = -1;
}