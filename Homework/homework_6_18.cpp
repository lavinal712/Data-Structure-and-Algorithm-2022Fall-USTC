#include <bits/stdc++.h>

using namespace std;

typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    BiTNode* lchild;
    BiTNode* rchild;
}* BiTree;

bool SimilarBiTree(BiTree T1, BiTree T2) {
    if (T1 == NULL && T2 == NULL) {
        return true;
    } else {
        if (T1 == NULL || T2 == NULL) {
            return false;
        } else {
            return SimilarBiTree(T1->lchild, T2->lchild) &&
                   SimilarBiTree(T1->rchild, T2->rchild);
        }
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
        if (rand() % 2) {
            root->lchild = InitBiTree(a, b, n - 1);
            root->rchild = InitBiTree(a, b, n - 1);
        } else {
            root->lchild = NULL;
            root->rchild = NULL;
        }
    }
    return root;
}

int main() {
    srand((unsigned)time(NULL));
    BiTree T1 = InitBiTree(1, 100, 5);
    BiTree T2 = InitBiTree(1, 100, 5);
    cout << SimilarBiTree(T1, T2);
    return 0;
}