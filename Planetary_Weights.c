#include <stdio.h>
#include <string.h>

#define MERCURY_GRAVITY 0.376
#define VENUS_GRAVITY 0.889
#define MARS_GRAVITY 0.378
#define JUPITER_GRAVITY 2.36
#define SATURN_GRAVITY 1.081
#define URANUS_GRAVITY 0.815
#define NEPTUNE_GRAVITY 1.14

float calculate_planet_weight(float earth_weight, char *planet) {
    if (strcmp(planet, "Mercury") == 0) {
        return earth_weight * MERCURY_GRAVITY;
    } else if (strcmp(planet, "Venus") == 0) {
        return earth_weight * VENUS_GRAVITY;
    } else if (strcmp(planet, "Mars") == 0) {
        return earth_weight * MARS_GRAVITY;
    } else if (strcmp(planet, "Jupiter") == 0) {
        return earth_weight * JUPITER_GRAVITY;
    } else if (strcmp(planet, "Saturn") == 0) {
        return earth_weight * SATURN_GRAVITY;
    } else if (strcmp(planet, "Uranus") == 0) {
        return earth_weight * URANUS_GRAVITY;
    } else if (strcmp(planet, "Neptune") == 0) {
        return earth_weight * NEPTUNE_GRAVITY;
    } else {
        return 0;
    }
}

int main() {
    float earth_weight, planet_weight;
    char planet[20];

    printf("Enter a weight on Earth: ");
    scanf("%f", &earth_weight);

    printf("Enter a planet: ");
    scanf("%s", planet);

    while (strcmp(planet, "Mercury") != 0 && strcmp(planet, "Venus") != 0 &&
           strcmp(planet, "Mars") != 0 && strcmp(planet, "Jupiter") != 0 &&
           strcmp(planet, "Saturn") != 0 && strcmp(planet, "Uranus") != 0 &&
           strcmp(planet, "Neptune") != 0) {
        if (strcmp(planet, "Earth") == 0) {
            printf("Please select a planet other than Earth.\n");
        } else {
            printf("Error: %s is not a planet.\n", planet);
        }

        printf("Enter a planet: ");
        scanf("%s", planet);
    }

    planet_weight = calculate_planet_weight(earth_weight, planet);
    printf("The equivalent weight on %s: %.2f\n", planet, planet_weight);

    return 0;
}
