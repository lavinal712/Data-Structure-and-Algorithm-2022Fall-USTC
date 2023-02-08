#include <bits/stdc++.h>

using namespace std;

typedef int ElemType;
typedef struct DLNode {
    ElemType data;
    DLNode* prior;
    DLNode* next;
}* DLinkList;

DLNode* ListOddEven(DLinkList& L);
DLNode* ListInit(ElemType a, ElemType b, int n);
void ListPrint(DLinkList& L);

DLNode* ListOddEven(DLinkList& L) {
    DLNode *p = L->next, *q = L, *r = L->next;
    int i = 0;
    while (p->next != L) {
        DLNode* s = p->next;
        i++;
        if (i % 2 == 0) {
            q->prior = p;
            p->next = q;
            q = q->prior;
            p = s;
            r->next = s;
            s->prior = r;
            r = r->next;
        } else {
            p = p->next;
        }
    }
    p->next = q;
    q->prior = p;
    return L;
}

DLNode* ListInit(ElemType a, ElemType b, int n) {
    DLinkList head = new DLNode;
    head->next = new DLNode;
    DLNode* p = head->next;
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        ElemType x = rand() % (b - a) + a;
        p->data = x;
        if (i != n - 1) {
            p->next = new DLNode;
            p->next->prior = p;
            p = p->next;
        }
    }
    p->next = head;
    head->prior = p;
    return head;
}

void ListPrint(DLinkList& L) {
    DLNode* p = L->next;
    cout << "L: ";
    while (p != L) {
        if (p->next != L) {
            cout << p->data << "->";
            p = p->next;
        } else {
            cout << p->data << endl;
            break;
        }
    }
}

int main() {
    DLinkList L = ListInit(1, 101, 10);
    ListPrint(L);
    L = ListOddEven(L);
    ListPrint(L);
    return 0;
}