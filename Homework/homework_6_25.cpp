#include <bits/stdc++.h>

using namespace std;

typedef int TElemType;
typedef struct BiTNode {
    TElemType data;
    BiTNode* lchild;
    BiTNode* rchild;
} BiTNode, *BiTree;

BiTNode* LowestCommonAncestor(BiTree X, BiTree Y, BiTree T) {
    if (X == T || Y == T || T == NULL) {
        return T;
    }
    BiTree PL = LowestCommonAncestor(X, Y, T->lchild),
           PR = LowestCommonAncestor(X, Y, T->rchild);
    return PL ? (PR ? T : PL) : PR;
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

void PreOrder(BiTree T) {
    if (T == NULL) {
        return;
    } else {
        printf("%d\n", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

BiTNode* RandomChild(BiTree T, int n) {
    if (T == NULL || n <= 0) {
        return T;
    }
    if (rand() % 2) {
        return RandomChild(T->lchild, n - 1);
    } else {
        return RandomChild(T->rchild, n - 1);
    }
}

int main() {
    srand((unsigned)time(NULL));
    BiTree T = InitBiTree(1, 100, 5);
    PreOrder(T);
    BiTNode* X = RandomChild(T, rand() % 5);
    BiTNode* Y = RandomChild(T, rand() % 5);
    BiTNode* A = LowestCommonAncestor(X, Y, T);
    if (A) {
        printf("Lowest Common Ancestor of X(%d) and Y(%d) is %d\n", X->data,
               Y->data, A->data);
    } else {
        printf("X and Y have no Lowest Common Ancestor");
    }
    return 0;
}