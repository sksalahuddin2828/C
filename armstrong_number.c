#include <stdio.h>
#include <math.h>

int is_armstrong_number(int n) {
    int num_digits = 0;
    int temp = n;
    while (temp > 0) {
        temp /= 10;
        num_digits++;
    }
    int sum_of_powers = 0;
    temp = n;
    while (temp > 0) {
        int digit = temp % 10;
        sum_of_powers += pow(digit, num_digits);
        temp /= 10;
    }
    return n == sum_of_powers;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (is_armstrong_number(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }
    return 0;
}

//------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>

int is_armstrong_number(int n) {
    int num_digits = 0;
    int temp = n;
    while (temp > 0) {
        temp /= 10;
        num_digits++;
    }
    int sum_of_powers = 0;
    temp = n;
    while (temp > 0) {
        int digit = temp % 10;
        sum_of_powers += pow(digit, num_digits);
        temp /= 10;
    }
    return n == sum_of_powers;
}

int main() {
    printf("%s\n", is_armstrong_number(153) ? "True" : "False"); 
    return 0;
}

// Output: True
