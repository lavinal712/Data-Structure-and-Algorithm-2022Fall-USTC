#include <stdio.h>

void main() {
    int i = 1, j = 0, k = 0, n;
    scanf("%d", &n);
    while (i + j <= n) {
        if (i < j) {
            i++;
            k++;
        } else
            j++;
    }
    printf("%d\n", k);
}