#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isModel(string str) {
    stack<char> stk;
    bool flag = false;
    for (char& c : str) {
        if (c != '@') {
            if (flag) {
                if (!stk.empty() && stk.top() == c) {
                    stk.pop();
                } else {
                    return false;
                }
            } else {
                stk.push(c);
            }
        } else {
            if (flag) {
                return false;
            } else {
                flag = true;
            }
        }
    }
    return stk.empty();
}

int main() {
    string str1 = "xyz@zyx";
    string str2 = "xyz@xyz";
    cout << isModel(str1) << " " << isModel(str2) << endl;
    return 0;
}