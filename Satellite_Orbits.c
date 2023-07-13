#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define EARTH_RADIUS 6371
#define NUM_SATELLITES 10
#define SATELLITE_RADIUS 100
#define SATELLITE_COLOR_RED 255
#define SATELLITE_COLOR_GREEN 0
#define SATELLITE_COLOR_BLUE 0

typedef struct
{
    double semi_major_axis;
    double eccentricity;
} Satellite;

void generate_satellite_orbits(Satellite *satellites, int num_satellites)
{
    srand(time(NULL));
    for (int i = 0; i < num_satellites; i++)
    {
        satellites[i].semi_major_axis = 800 + ((double)rand() / RAND_MAX) * (1500 - 800);
        satellites[i].eccentricity = 0.1 + ((double)rand() / RAND_MAX) * (0.4 - 0.1);
    }
}

void draw_earth(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Light blue
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            double u = i * 2 * M_PI / 100.0;
            double v = j * M_PI / 50.0;
            double x = EARTH_RADIUS * cos(u) * sin(v) + SCREEN_WIDTH / 2;
            double y = EARTH_RADIUS * sin(u) * sin(v) + SCREEN_HEIGHT / 2;
            SDL_RenderDrawPoint(renderer, (int)x, (int)y);
        }
    }
}

void draw_satellite_orbit(SDL_Renderer *renderer, Satellite satellite, double *time, int num_frames)
{
    double r, x, y, z;
    for (int i = 0; i < num_frames; i++)
    {
        r = satellite.semi_major_axis * (1 - satellite.eccentricity * satellite.eccentricity) /
            (1 + satellite.eccentricity * cos(time[i]));
        x = r * cos(time[i]) + SCREEN_WIDTH / 2;
        y = r * sin(time[i]) + SCREEN_HEIGHT / 2;
        z = 0;
        SDL_RenderDrawPoint(renderer, (int)x, (int)y);
    }
}

void draw_satellite_marker(SDL_Renderer *renderer, Satellite satellite, double *time, int num_frames)
{
    double r, x, y, z;
    r = satellite.semi_major_axis * (1 - satellite.eccentricity * satellite.eccentricity) /
        (1 + satellite.eccentricity * cos(time[num_frames - 1]));
    x = r * cos(time[num_frames - 1]) + SCREEN_WIDTH / 2;
    y = r * sin(time[num_frames - 1]) + SCREEN_HEIGHT / 2;
    z = 0;
    SDL_SetRenderDrawColor(renderer, SATELLITE_COLOR_RED, SATELLITE_COLOR_GREEN, SATELLITE_COLOR_BLUE, 255);
    SDL_Rect marker = {(int)x - SATELLITE_RADIUS / 2, (int)y - SATELLITE_RADIUS / 2, SATELLITE_RADIUS, SATELLITE_RADIUS};
    SDL_RenderFillRect(renderer, &marker);
}

int main()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Satellite Orbits", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Generate satellite orbits
    Satellite satellites[NUM_SATELLITES];
    generate_satellite_orbits(satellites, NUM_SATELLITES);

    // Time array
    int num_frames = 100;
    double time[num_frames];
    double step = 2 * M_PI / num_frames;
    for (int i = 0; i < num_frames; i++)
    {
        time[i] = i * step;
    }

    // Main loop
    int quit = 0;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        SDL_RenderClear(renderer);

        // Draw Earth
        draw_earth(renderer);

        // Draw satellite orbits and markers
        for (int i = 0; i < NUM_SATELLITES; i++)
        {
            draw_satellite_orbit(renderer, satellites[i], time, num_frames);
            draw_satellite_marker(renderer, satellites[i], time, num_frames);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
