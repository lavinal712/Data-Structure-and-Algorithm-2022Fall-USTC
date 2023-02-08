#include <stdio.h>

void main() {
    int i = 1, j = 0, k = 0, n;
    scanf("%d", &n);
    while (i <= n - 1) {
        k += 10 * i;
        j++;
        i++;
    }
    printf("%d\n", j);
}