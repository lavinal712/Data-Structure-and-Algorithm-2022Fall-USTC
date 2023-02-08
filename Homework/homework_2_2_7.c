#include <stdio.h>

void main() {
    int i, j, k;
    int n, x = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            for (k = j; k < n; k++) {
                x += 2;
            }
        }
    }
    printf("%d\n", x / 2);
}