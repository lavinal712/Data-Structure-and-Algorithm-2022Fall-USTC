#include <bits/stdc++.h>

using namespace std;

typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    BiTNode* lchild;
    BiTNode* rchild;
}* BiTree;

void CopyBiTree(BiTree T, BiTree& NewT) {
    if (T == NULL) {
        NewT = NULL;
        return;
    } else {
        NewT = new BiTNode;
        NewT->data = T->data;
        CopyBiTree(T->lchild, NewT->lchild);
        CopyBiTree(T->rchild, NewT->rchild);
    }
}

BiTNode* InitBiTree(TElemType a, TElemType b, int n) {
    if (n <= 0) {
        return NULL;
    }
    BiTNode* root = new BiTNode;
    root->data = rand() % (b - a) + a;
    if (n == 1) {
        root->lchild = NULL;
        root->rchild = NULL;
    } else {
        root->lchild = InitBiTree(a, b, n - 1);
        root->rchild = InitBiTree(a, b, n - 1);
    }
    return root;
}

void PreOrderBiTree(BiTree T) {
    if (T == NULL) {
        return;
    } else {
        cout << T->data << " ";
        PreOrderBiTree(T->lchild);
        PreOrderBiTree(T->rchild);
    }
}

int main() {
    srand((unsigned)time(NULL));
    BiTree T1 = InitBiTree(1, 100, 5), T2;
    PreOrderBiTree(T1);
    cout << '\n';
    CopyBiTree(T1, T2);
    PreOrderBiTree(T2);
    cout << '\n';
    return 0;
}