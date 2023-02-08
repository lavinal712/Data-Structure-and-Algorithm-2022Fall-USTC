#include <bits/stdc++.h>

using namespace std;

typedef int ElemType;
typedef struct ListNode {
    ElemType data;
    ListNode* next;
}* LinkList;

void ListInsert(LinkList& L, ElemType x);
ListNode* ListInit(ElemType a, ElemType b, int n);
void ListPrint(LinkList& L);
ListNode* ListSort(LinkList& L);

void ListInsert(LinkList& L, ElemType x) {
    ListNode* p = L;
    while (p->next && p->next->data < x) {
        p = p->next;
    }
    ListNode* s = new ListNode;
    s->data = x;
    s->next = p->next;
    p->next = s;
}

ListNode* ListInit(ElemType a, ElemType b, int n) {
    LinkList head = new ListNode;
    ListNode* p = head;
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        ListNode* s = new ListNode;
        ElemType x = rand() % (b - a) + a;
        s->data = x;
        p->next = s;
        p = p->next;
    }
    p->next = NULL;
    head = ListSort(head);
    return head;
}

void ListPrint(LinkList& L) {
    ListNode* p = L->next;
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

ListNode* ListSort(LinkList& L) {
    ListNode* p = L->next;
    int n = 0;
    while (p) {
        if (p->next) {
            n++;
            p = p->next;
        } else {
            n++;
            break;
        }
    }
    p = L->next;
    ElemType dataset[n];
    for (int i = 0; i < n; i++) {
        dataset[i] = p->data;
        p = p->next;
    }
    p = L->next;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (dataset[i] < dataset[j]) {
                ElemType temp;
                temp = dataset[i];
                dataset[i] = dataset[j];
                dataset[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        p->data = dataset[i];
        p = p->next;
    }
    return L;
}

int main() {
    LinkList L = ListInit(1, 101, 10);
    ListPrint(L);
    ElemType x;
    cout << "Please enter data to insert" << endl;
    cin >> x;
    ListInsert(L, x);
    ListPrint(L);
    return 0;
}