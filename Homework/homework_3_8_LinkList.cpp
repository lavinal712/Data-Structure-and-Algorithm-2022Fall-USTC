#include <bits/stdc++.h>

using namespace std;

typedef int ElemType;
typedef struct ListNode {
    ElemType data;
    ListNode* next;
}* LinkList;

ListNode* ListDivOddEven(LinkList& L);
ListNode* ListInit(ElemType a, ElemType b, int n);
ListNode* ListSort(LinkList& L);

ListNode* ListDivOddEven(LinkList& L) {
    ListNode *p = L, *q = L->next;
    while (q->next) {
        if (p->data % 2 == 0) {
            while (q->data % 2 == 0 && q->next) {
                q = q->next;
            }
            if (q->data % 2 == 1) {
                swap(p->data, q->data);
            }
        }
        p = p->next;
        if (q->next) {
            q = q->next;
        }
    }
    return L;
}

ListNode* ListInit(ElemType a, ElemType b, int n) {
    LinkList head = new ListNode;
    ListNode* p = head;
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        ElemType x = rand() % (b - a) + a;
        p->data = x;
        if (i != n - 1) {
            p->next = new ListNode;
            p = p->next;
        }
    }
    p->next = NULL;
    return head;
}

void ListPrint(LinkList& L) {
    ListNode* p = L;
    cout << "L: ";
    while (p) {
        if (p->next) {
            cout << p->data << "->";
            p = p->next;
        } else {
            cout << p->data << endl;
            break;
        }
    }
}

int main() {
    LinkList L = ListInit(1, 101, 10);
    ListPrint(L);
    L = ListDivOddEven(L);
    ListPrint(L);
    return 0;
}