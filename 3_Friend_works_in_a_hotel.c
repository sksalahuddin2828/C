#include <stdio.h>

int main() {
    int friend_one[136];
    int friend_two[28];
    int friend_three[18];
    int i, j;
    int calculate_together_works[5];
    int calculate_together_count = 0;

    for (i = 15; i < 150; i++) {
        if (i % 3 == 0) {
            friend_one[i / 3 - 5] = i;
        }
        if (i % 5 == 0) {
            friend_two[i / 5 - 3] = i;
        }
        if (i % 8 == 0) {
            friend_three[i / 8 - 2] = i;
        }
    }

    printf("1st friend I are working: ");
    for (i = 0; i < 136; i++) {
        printf("%d ", friend_one[i]);
    }
    printf("\n");

    printf("2nd Friend II are working: ");
    for (i = 0; i < 28; i++) {
        printf("%d ", friend_two[i]);
    }
    printf("\n");

    printf("3rd Friend III are working: ");
    for (i = 0; i < 18; i++) {
        printf("%d ", friend_three[i]);
    }
    printf("\n");

    for (i = 0; i < 136; i++) {
        for (j = 0; j < 28; j++) {
            if (friend_one[i] == friend_two[j]) {
                int k;
                for (k = 0; k < 18; k++) {
                    if (friend_one[i] == friend_three[k]) {
                        calculate_together_works[calculate_together_count++] = friend_one[i];
                        break;
                    }
                }
                break;
            }
        }
    }

    printf("All friends are working: ");
    for (i = 0; i < calculate_together_count; i++) {
        printf("%d ", calculate_together_works[i]);
    }
    printf("\n");

    return 0;
}
