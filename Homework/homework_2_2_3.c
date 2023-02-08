#include <stdio.h>

void main() {
    int i = 1, j = 0, k = 0, n;
    scanf("%d", &n);
    do {
        k += 10 * i;
        j++;
        i++;
    } while (i == n);
    printf("%d\n", j);
}