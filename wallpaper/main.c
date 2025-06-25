#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erro ao iniciar SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *janela = SDL_CreateWindow("Exemplo SDL3", 800, 600, 0);
    if (!janela) {
        SDL_Log("Erro ao criar janela: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *render = SDL_CreateRenderer(janela, NULL);
    if (!render) {
        SDL_Log("Erro ao criar renderizador: %s", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return 1;
    }

    bool rodando = true;
    SDL_Event evento;
    float x = 0;

    while (rodando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_EVENT_QUIT) {
                rodando = false;
            }
        }

        SDL_SetRenderDrawColor(render, 0, 0, 50, 255); // fundo azul escuro
        SDL_RenderClear(render);

        SDL_FRect retangulo = { x, 250, 100, 100 };
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255); // vermelho
        SDL_RenderFillRect(render, &retangulo);

        SDL_RenderPresent(render);

        SDL_Delay(16); // ~60 FPS
        x += 2;
        if (x > 800) x = -100;
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}
