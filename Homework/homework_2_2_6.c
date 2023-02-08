#include <stdio.h>

void main() {
    int x = 91, y = 100, z = 0;
    while (y > 0) {
        if (x > 100) {
            x -= 10;
            y--;
            z++;
        } else
            x++;
    }
    printf("%d\n", z);
}