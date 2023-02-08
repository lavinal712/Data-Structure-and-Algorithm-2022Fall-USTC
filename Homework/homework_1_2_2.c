#include <stdio.h>

void main() {
    int i, r[10], sum = 0;
    for (i = 0; i < 10; i++) {
        r[i] = i + 1;
        sum += r[i];
    }
    printf("sum = %d\n", sum);
}