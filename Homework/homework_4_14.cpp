#include <bits/stdc++.h>

void func(int& s) {
    int x;
    scanf("%d", &x);
    if (x == 0) {
        s = 0;
        return;
    }
    func(s);
    s += x;
    printf("s = %d\n", s);
}

void func1(int& s) {
    int x;
    std::stack<int> stk;
    while (true) {
        scanf("%d", &x);
        if (x) {
            stk.push(x);
        } else {
            break;
        }
    }
    s = 0;
    while (!stk.empty()) {
        s += stk.top();
        printf("s = %d\n", s);
        stk.pop();
    }
}

int main() {
    int s = 3;
    func(s);
    return 0;
}