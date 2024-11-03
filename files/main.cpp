#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "./constants.h"
#include <iostream>
using namespace std;


int initialize_SDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { cout << "erro SDL_Init"; return 1; }
    if (IMG_Init(IMG_INIT_PNG) == 0) { cout << "erro IMG_Init"; return 1; }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) { cout << "erro Mix_OpenAudio"; return 1; }
    if (TTF_Init() == -1) { cout << "erro TTF_Init"; return 1; }
    return 0;
}

int main(int argc, char **argv)
{
    // Inicializações de SDL
    if(initialize_SDL() == 1){return 1;}

    SDL_Window *window = SDL_CreateWindow("SDL2 It's Works!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDHT, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
    SDL_Renderer *baseRenderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *logo = IMG_LoadTexture(baseRenderer, "./assets/sdl.png");
    Mix_Music *music = Mix_LoadMUS("./assets/music.mp3");
    Mix_PlayMusic(music, -1); Mix_VolumeMusic(5);
    TTF_Font *font = TTF_OpenFont("./assets/font.ttf", 24);

    SDL_Rect rect = {50, 20, 400, 208}; // Ajustado para o logo
    SDL_Rect rect2 = {350, 350, 50, 50};

    SDL_Color textColor = {255, 0, 0};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "JOAO BURRO", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(baseRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect textRect = {500, 500, 200, 50};

    bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false;
    const int moveSpeed = 5; // Define a velocidade de movimento

    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) exit(0);
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: upPressed = true; break;
                case SDLK_DOWN: downPressed = true; break;
                case SDLK_LEFT: leftPressed = true; break;
                case SDLK_RIGHT: rightPressed = true; break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP: upPressed = false; break;
                case SDLK_DOWN: downPressed = false; break;
                case SDLK_LEFT: leftPressed = false; break;
                case SDLK_RIGHT: rightPressed = false; break;
                }
            }
        }

        // Atualiza posição com base nas teclas
        if (upPressed && rect2.y > 0) rect2.y -= moveSpeed;
        if (downPressed && rect2.y < WINDOW_HEIGHT - rect2.h) rect2.y += moveSpeed;
        if (leftPressed && rect2.x > 0) rect2.x -= moveSpeed;
        if (rightPressed && rect2.x < WINDOW_WIDHT - rect2.w) rect2.x += moveSpeed;

        SDL_SetRenderDrawColor(baseRenderer, 9, 20, 33, 255);
        SDL_RenderClear(baseRenderer);
        SDL_SetRenderDrawColor(baseRenderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(baseRenderer, &rect2);
        SDL_RenderFillRect(baseRenderer, &rect2);
        SDL_RenderCopy(baseRenderer, textTexture, NULL, &textRect);
        SDL_RenderCopy(baseRenderer, logo, NULL, &rect);
        SDL_RenderPresent(baseRenderer);

        SDL_Delay(8); // Adiciona um atraso de ~16ms para rodar a ~60 FPS
    }

    // Liberação de recursos
    SDL_DestroyTexture(textTexture); SDL_DestroyTexture(logo); Mix_FreeMusic(music); TTF_CloseFont(font);
    SDL_DestroyRenderer(baseRenderer); SDL_DestroyWindow(window); Mix_CloseAudio(); TTF_Quit(); IMG_Quit(); SDL_Quit();
    return 0;
}
