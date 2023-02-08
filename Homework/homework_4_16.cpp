#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ElemType;
typedef struct ListNode {
    ElemType data;
    ListNode* next;
}* LinkList;

ListNode* ListReverseRecursion(LinkList& L);
ListNode* ListReverseIteration(LinkList& L);
ListNode* ListInit(ElemType a, ElemType b, int n);
ListNode* ListSort(LinkList& L);

ListNode* ListReverseRecursion(LinkList& L) {
    if (!L || !L->next) {
        return L;
    }
    LinkList newL = ListReverseRecursion(L->next);
    L->next->next = L;
    L->next = NULL;
    return newL;
}

ListNode* ListReverseIteration(LinkList& L) {
    LinkList prev = NULL, curr = L;
    while (curr) {
        LinkList next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
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
    LinkList L = ListInit(1, 10000, 10);
    ListPrint(L);
    L = ListReverseRecursion(L);
    ListPrint(L);
    L = ListReverseIteration(L);
    ListPrint(L);
    return 0;
}