/*
    已知一个整型元素的数组A[n][n],编写函数实现:
    (1)计算对角线元素之和;
    (2)判断该二维数组表示的矩阵是否是对称矩阵;
    (3)判断该矩阵是否是稀疏矩阵.
*/

#include <bits/stdc++.h>

int trace(vector<vector<int>>& A) {
    int n = A.size();
    int trace = 0;
    for (int i = 0; i < n; i++) {
        trace += A[i][i];
    }
    return trace;
}

bool isSymmetricMatrix(vector<vector<int>>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i][j] != A[j][i]) {
                return false;
            }
        }
    }
    return true;
}

bool isSparseMartrix(vector<vector<int>>& A) {
    int n = A.size(), count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j]) {
                count++;
            }
        }
    }
    return count * 20 <= n * n;
}