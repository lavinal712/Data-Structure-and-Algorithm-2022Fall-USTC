#include <bits/stdc++.h>

using namespace std;

typedef int ElemType;

vector<ElemType> List;

void ListDivOddEven(vector<ElemType>& List);
void ListInit(ElemType a, ElemType b, int n);
void ListPrint(vector<ElemType>& List);

void ListDivOddEven(vector<ElemType>& List) {
    for (int left = 0, right = List.size() - 1; left < right;) {
        while (List[left] % 2 == 1) {
            left++;
        }
        while (List[right] % 2 == 0) {
            right--;
        }
        if (left < right) {
            swap(List[left], List[right]);
        }
    }
}

void ListInit(ElemType a, ElemType b, int n) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        ElemType x = rand() % (b - a) + a;
        List.push_back(x);
    }
}

void ListPrint(vector<ElemType>& List) {
    cout << "List: ";
    int n = List.size();
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            cout << List[i] << " ";
        } else {
            cout << List[i] << endl;
        }
    }
}

int main() {
    ListInit(1, 100, 10);
    ListPrint(List);
    ListDivOddEven(List);
    ListPrint(List);
    return 0;
}