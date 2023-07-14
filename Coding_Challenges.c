//-----------------------------------------------------------------C Coding Challenges----------------------------------------------------------

// C Coding Challenges on Numbers 
// Write a program in C to -

// 1. Convert decimal numbers to octal numbers.
// 2. Reverse an integer.
// 3. Print the Fibonacci series using the recursive method.
// 4. Return the Nth value from the Fibonacci sequence.
// 5. Find the average of numbers (with explanations).
// 6. Convert Celsius to Fahrenheit.

//----------------------------------------------------------------Solution of Problem:----------------------------------------------------------

// 1. Converting Decimal Numbers to Octal Numbers:

#include <stdio.h>

int main() {
    int decimal_number = 25;
    int octal_number[100];
    int i = 0;
    
    while (decimal_number > 0) {
        octal_number[i] = decimal_number % 8;
        decimal_number = decimal_number / 8;
        i++;
    }
    
    printf("Octal number: ");
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", octal_number[j]);
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

// 2. Reversing an Integer:

#include <stdio.h>

int main() {
    int number = 12345;
    int reversed_number = 0;

    while (number != 0) {
        reversed_number = reversed_number * 10 + number % 10;
        number = number / 10;
    }

    printf("%d", reversed_number);
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

// 3. Printing the Fibonacci Series using Recursion:

#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n = 10;
    printf("Fibonacci series: ");
    
    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci(i));
    }
    
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

// 4. Returning the Nth Value from the Fibonacci Sequence:

#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n = 10;
    int fibonacci_number = fibonacci(n);
    printf("%d", fibonacci_number);
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

// 5. 
