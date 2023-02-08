#include <bits/stdc++.h>

using namespace std;

void SortDutchFlag(string& flag) {
    int n = flag.length();
    int p0 = 0, p1 = 0;
    for (int i = 0; i < n; i++) {
        if (flag[i] == 'W') {
            swap(flag[i], flag[p1]);
            p1++;
        } else if (flag[i] == 'R') {
            swap(flag[i], flag[p0]);
            if (p0 < p1) {
                swap(flag[i], flag[p1]);
            }
            p0++;
            p1++;
        }
    }
}

string InitDutchFlag(int n) {
    string flag = "";
    for (int i = 0; i < n; i++) {
        int color = rand() % 3;
        if (color == 0) {
            flag += "R";
        } else if (color == 1) {
            flag += "W";
        } else if (color == 2) {
            flag += "B";
        }
    }
    return flag;
}

int main() {
    srand((unsigned)time(NULL));
    string dutch_flag = InitDutchFlag(1000);
    cout << dutch_flag << endl;
    SortDutchFlag(dutch_flag);
    cout << dutch_flag << endl;
}