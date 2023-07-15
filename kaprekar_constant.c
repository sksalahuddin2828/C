#include <stdio.h>

int kaprekar_constant(int n) {
    int count = 0;
    while (n != 6174) {
        count++;
        int digits[4];
        for (int i = 3; i >= 0; i--) {
            digits[i] = n % 10;
            n /= 10;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                if (digits[i] < digits[j]) {
                    int temp = digits[i];
                    digits[i] = digits[j];
                    digits[j] = temp;
                }
            }
        }
        int ascending = digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3];
        int descending = digits[3] * 1000 + digits[2] * 100 + digits[1] * 10 + digits[0];
        n = descending - ascending;
    }
    return count;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int steps = kaprekar_constant(num);
    printf("Number of steps to reach Kaprekar constant: %d\n", steps);
    return 0;
}
