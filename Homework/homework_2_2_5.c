#include <stdio.h>

void main() {
    int n;
    scanf("%d", &n);
    int x = n, y = 0, z = 0;
    while (x >= (y + 1) * (y + 1)) {
        y++;
        z++;
    }
    printf("%d\n", z);
}