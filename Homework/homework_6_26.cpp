#include <bits/stdc++.h>

using namespace std;

typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    BiTNode* lchild;
    BiTNode* rchild;
}* BiTree;

void PreOrder(BiTree T, vector<TElemType>& res) {
    if (T == NULL) {
        return;
    } else {
        res.push_back(T->data);
        PreOrder(T->lchild, res);
        PreOrder(T->rchild, res);
    }
}

TElemType PreOrderVal(BiTree T, int k) {
    vector<TElemType> res;
    PreOrder(T, res);
    return res[k - 1];
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

void PrintTree(BiTree T) {
    if (T == NULL) {
        return;
    } else {
        printf("%d\n", T->data);
        PrintTree(T->lchild);
        PrintTree(T->rchild);
    }
}

int main() {
    srand((unsigned)time(NULL));
    BiTree T = InitBiTree(1, 100, 5);
    PrintTree(T);
    int n = rand() % 32;
    printf("The %d value in PreOrder: %d", n, PreOrderVal(T, n));
    return 0;
}