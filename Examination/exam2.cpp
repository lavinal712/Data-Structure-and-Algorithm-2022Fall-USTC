// 给定一个前缀表达式，其中只会出现26个小写英文字母以及+-*/四种运算符号，每个字母代表一个特定的运算数字
// 定义层序遍历线索三叉树如下：每个结点配三个指针，分别指向该结点的左孩子、右孩子、以及层序遍历情况下的下一个结点
// (1) 由前缀表达式构造一棵表达式二叉树
// (2) 根据表达式二叉树创建一棵层序遍历线索三叉树

// 下面给出了数据结构的定义，以及一些辅助函数和测试函数，答题仅需要完成相应的函数
// 编写完成后，可以使用main函数测试

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef char ElemType;
typedef struct BiNode {
    ElemType data;
    BiNode* lchild;
    BiNode* rchild;
}* BiTree;
typedef struct TriNode {
    ElemType data;
    TriNode* lchild;
    TriNode* rchild;
    TriNode* next;
}* ThreadTriTree;
typedef struct {
    TriNode* elem[100];
    int front;
    int rear;
} Queue;

// 下面是一个辅助函数，功能是判断一个字符是不是小写英文字母
bool isLowercase(char c) {
    return (c >= 'a' && c <= 'z');
}

// 下面是一个辅助函数，功能是判断一个字符是不是四种规定的运算符号之一
bool isValidOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 下面是一个辅助函数，功能是建立一个空队列
void InitQueue(Queue& Q) {
    Q.front = Q.rear = 0;
}

// 下面是一个辅助函数，功能是入队一个元素
bool EnQueue(Queue& Q, TriNode* e) {
    if (Q.rear + 1 == Q.front)
        return false;
    Q.elem[Q.rear++] = e;
    return true;
}

// 下面是一个辅助函数，功能是出队一个元素
bool DeQueue(Queue& Q, TriNode*& e) {
    if (Q.front == Q.rear)
        return false;
    e = Q.elem[Q.front++];
    return true;
}

// 需要完成的函数
BiTree BuildTreeFromExpression(const char*& expression) {
    if (*expression == '\0') {
        return NULL;
    }
    BiTree T = (BiTree)malloc(sizeof(BiNode));
    if (isLowercase(*expression) || isValidOperator(*expression)) {
        T->data = *expression;
        if (isLowercase(*expression)) {
            T->lchild = T->rchild = NULL;
            return T;
        }
        T->lchild = BuildTreeFromExpression(++expression);
        T->rchild = BuildTreeFromExpression(++expression);
        return T;
    } else {
        return NULL;
    }
}

// 前序遍历二叉树
void Preorder(BiTree bitree) {
    if (bitree == NULL) {
        return;
    }
    printf("%c", bitree->data);
    Preorder(bitree->lchild);
    Preorder(bitree->rchild);
}

// 需要完成的函数
ThreadTriTree CopyTriTreeFromBiTree(BiTree bitree) {
    if (bitree == NULL) {
        return NULL;
    }
    TriNode* T = (TriNode*)malloc(sizeof(TriNode));
    T->data = bitree->data;
    T->lchild = CopyTriTreeFromBiTree(bitree->lchild);
    T->rchild = CopyTriTreeFromBiTree(bitree->rchild);
    T->next = NULL;
    return T;
}

// 需要完成的函数
ThreadTriTree BuildThreadTriTreeFromBiTree(BiTree bitree) {
    TriNode* tritree = CopyTriTreeFromBiTree(bitree);
    TriNode* PT = tritree;
    Queue Q;
    InitQueue(Q);
    EnQueue(Q, tritree);
    while (Q.rear - Q.front != 0) {
        int level = Q.rear - Q.front;
        for (int i = 1; i <= level; i++) {
            TriNode* T;
            DeQueue(Q, T);
            PT->next = T;
            PT = T;
            if (T->lchild) {
                EnQueue(Q, T->lchild);
            }
            if (T->rchild) {
                EnQueue(Q, T->rchild);
            }
        }
    }
    return tritree;
}

// 下面是一个辅助函数，功能是打印一棵层序遍历线索三叉树
void PrintThreadTriTree(ThreadTriTree tritree) {
    ThreadTriTree p = tritree;
    while (p != NULL) {
        printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}

// 下面是主函数，用于测试
int main() {
    const char* expression = "-+a*b-cd/ef";
    BiTree bitree = BuildTreeFromExpression(expression);
    ThreadTriTree tritree = BuildThreadTriTreeFromBiTree(bitree);
    PrintThreadTriTree(tritree);
    return EXIT_SUCCESS;
}
