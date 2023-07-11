#include <stdio.h>

int areArraysEqual(int arr1[], int arr2[], int n, int m) {
    // If lengths of arrays are not equal, they are not equal
    if (n != m) {
        return 0;
    }

    // Sort both arrays
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                int temp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = temp;
            }
            if (arr2[j] > arr2[j + 1]) {
                int temp = arr2[j];
                arr2[j] = arr2[j + 1];
                arr2[j + 1] = temp;
            }
        }
    }

    // Linearly compare elements
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }

    // If all elements are the same
    return 1;
}

int main() {
    int arr1[] = {3, 5, 2, 5, 2};
    int arr2[] = {2, 3, 5, 5, 2};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);

    if (areArraysEqual(arr1, arr2, n, m)) {
        printf("The arrays are equal\n");
    } else {
        printf("The arrays are not equal\n");
    }

    return 0;
}
