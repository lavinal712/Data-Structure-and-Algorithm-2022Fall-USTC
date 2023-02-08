#include <bits/stdc++.h>

using namespace std;

typedef int ElemType;

vector<ElemType> List;

void ListInsert(vector<ElemType>& List, ElemType x);
void ListInit(ElemType a, ElemType b, int n);
void ListPrint(vector<ElemType>& List);

void ListInsert(vector<ElemType>& List, ElemType x) {
    int n = List.size();
    List.push_back(List[n - 1]);
    int i;
    for (i = List.size() - 1; List[i] >= x && i >= 0; i--) {
        List[i + 1] = List[i];
    }
    List[i + 1] = x;
}

void ListInit(ElemType a, ElemType b, int n) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        ElemType x = rand() % (b - a) + a;
        List.push_back(x);
    }
    sort(List.begin(), List.end());
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
    ElemType x;
    cout << "Please enter data to insert" << endl;
    cin >> x;
    ListInsert(List, x);
    ListPrint(List);
    return 0;
}