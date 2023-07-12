#include <stdio.h>

int main() {
    int incomeList[10];

    printf("Enter the income of 10 people:\n");
    for (int person = 0; person < 10; person++) {
        printf("Enter income: ");
        scanf("%d", &incomeList[person]);
    }

    for (int firstIndex = 0; firstIndex < 9; firstIndex++) {
        int swapCount = 0;
        int minIncome = incomeList[firstIndex];
        int minIndex = firstIndex;

        for (int secondIndex = firstIndex + 1; secondIndex < 10; secondIndex++) {
            if (minIncome > incomeList[secondIndex]) {
                minIncome = incomeList[secondIndex];
                swapCount++;
                minIndex = secondIndex;
            }
        }

        if (swapCount != 0) {
            int temp = incomeList[firstIndex];
            incomeList[firstIndex] = minIncome;
            incomeList[minIndex] = temp;
        }
    }

    printf("Sorted income list:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\n", incomeList[i]);
    }

    return 0;
}
