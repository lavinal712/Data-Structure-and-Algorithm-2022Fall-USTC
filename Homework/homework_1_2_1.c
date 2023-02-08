#include <stdio.h>

void main() {
    int i;
    char str[5];
    for (i = 0; i < 5; i++)
        scanf("%c", &str[i]);
    for (i = 0; i < 5; i++)
        printf("%c\n", str[i]);
}