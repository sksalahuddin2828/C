#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool is_palindrome(char *s) {
    int length = strlen(s);
    char filtered[length];
    int index = 0;
    for (int i = 0; i < length; i++) {
        if (isalnum(s[i])) {
            filtered[index++] = tolower(s[i]);
        }
    }
    for (int i = 0, j = index - 1; i < j; i++, j--) {
        if (filtered[i] != filtered[j]) {
            return false;
        }
    }
    return true;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    if (is_palindrome(str)) {
        printf("'%s' is a palindrome.\n", str);
    } else {
        printf("'%s' is not a palindrome.\n", str);
    }
    return 0;
}
