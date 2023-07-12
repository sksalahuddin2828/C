#include <stdio.h>
#include <math.h>

int main() {
    double num;
    printf("Enter a number: ");
    scanf("%lf", &num);

    // Find the square root of the number
    double realPart = sqrt(fabs(num));
    double imaginaryPart = sqrt(-num);

    // Display the result
    if (imaginaryPart == 0) {
        printf("The square root of %.3f is %.3f\n", num, realPart);
    } else {
        printf("The square root of %.3f is %.3f+%.3fi\n", num, realPart, imaginaryPart);
    }

    return 0;
}
