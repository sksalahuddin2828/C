#include <SDL2/SDL.h>

#define FRAME_WIDTH 800
#define FRAME_HEIGHT 600
#define ROTATION_INTERVAL 20

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect destinationRect;
    SDL_Event event;
    int frame = 0;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("3D Earth Rotation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, FRAME_WIDTH, FRAME_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *surface = SDL_LoadBMP("blue_marble.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    destinationRect.x = FRAME_WIDTH / 2 - surface->w / 2;
    destinationRect.y = FRAME_HEIGHT / 2 - surface->h / 2;
    destinationRect.w = surface->w;
    destinationRect.h = surface->h;

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyTexture(texture);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
        SDL_RenderPresent(renderer);

        SDL_Delay(ROTATION_INTERVAL);

        frame += 2;
        if (frame > 360) {
            frame = 0;
        }

        SDL_Surface *rotatedSurface = rotozoomSurface(surface, frame, 1.0, 0);
        SDL_DestroyTexture(texture);
        texture = SDL_CreateTextureFromSurface(renderer, rotatedSurface);
        SDL_FreeSurface(rotatedSurface);
    }

    return 0;
}
