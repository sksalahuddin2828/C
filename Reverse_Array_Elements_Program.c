#include <stdio.h>

int main() {
    int number;
    printf("Please enter the total number you want to enter: ");
    scanf("%d", &number);

    int array[number];
    for (int i = 0; i < number; i++) {
        printf("Enter the element %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < number / 2; i++) {
        int temp = array[i];
        array[i] = array[number - 1 - i];
        array[number - 1 - i] = temp;
    }

    printf("\nReverse all elements of the array:\n");
    for (int i = 0; i < number; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
