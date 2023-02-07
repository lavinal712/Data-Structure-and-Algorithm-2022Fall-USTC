#include <bits/stdc++.h>
#include <windows.h>

typedef int ElemType;

typedef struct {
    ElemType* r;
    int len;
} SqTable;

void InitList(SqTable& L, int len) {
    L.r = (ElemType*)malloc((len + 1) * sizeof(ElemType));
    L.len = len;
}

void CopyList(SqTable L, SqTable& newL) {
    newL.r = (ElemType*)malloc((L.len + 1) * sizeof(ElemType));
    newL.len = L.len;
    memcpy(newL.r, L.r, (L.len + 1) * sizeof(ElemType));
}

// 求一个整数的p次方
int intpow(int n, unsigned int p) {
    int res = 1;
    for (unsigned int i = 0; i < p; ++i) {
        res *= n;
    }
    return res;
}

int randb(int bound) {
    int r = 0;
    unsigned int power = 0;
    do {
        r *= RAND_MAX;
        r += rand();
        ++power;
    } while (intpow(RAND_MAX, power) < bound);
    return r % (bound + 1);
}

void RandomShuffle(SqTable L) {
    ElemType* array = L.r + 1;
    int n = L.len;
    for (int i = n - 1; i > 0; --i) {
        int j = randb(i);
        ElemType tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void BubbleSort(SqTable& L) {
    bool change = true;
    int n = L.len;
    for (int i = n; i >= 2 && change; --i) {
        change = false;
        for (int j = 1; j <= i - 1; ++j) {
            if (L.r[j] > L.r[j + 1]) {
                ElemType tmp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = tmp;
                change = true;
            }
        }
        if (!change) {
            break;
        }
    }
}

void SelectSort(SqTable& L) {
    for (int i = 1; i < L.len; ++i) {
        int j = i;
        for (int k = L.len; k > i; --k)
            if (L.r[k] < L.r[j])
                j = k;
        if (i != j) {
            ElemType tmp = L.r[i];
            L.r[i] = L.r[j];
            L.r[j] = tmp;
        }
    }
}

void InsertSort(SqTable& L) {
    for (int i = 2; i <= L.len; ++i)
        if (L.r[i] < L.r[i - 1]) {
            ElemType tmp = L.r[i];
            int j;
            for (j = i - 1; tmp < L.r[j] && j >= 1; --j) {
                L.r[j + 1] = L.r[j];
            }
            L.r[j + 1] = tmp;
        }
}

void Merge(ElemType* Rs, ElemType* Rt, int s, int m, int t) {
    int i, j, k;
    for (i = s, j = m + 1, k = s; i <= m && j <= t; ++k) {
        if (Rs[i] <= Rs[j])
            Rt[k] = Rs[i++];
        else
            Rt[k] = Rs[j++];
    }
    for (; i <= m; ++i, ++k) {
        Rt[k] = Rs[i];
    }
    for (; j <= t; ++j, ++k) {
        Rt[k] = Rs[j];
    }
}

void MSort(ElemType* Rs, ElemType* Rt, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MSort(Rs, Rt, low, mid);
        MSort(Rs, Rt, mid + 1, high);
        Merge(Rs, Rt, low, mid, high);
        for (int i = low; i <= high; ++i) {
            Rs[i] = Rt[i];
        }
    }
}

void MergeSort(SqTable& L) {
    ElemType* tmp = new ElemType[L.len + 1];
    MSort(L.r, tmp, 1, L.len);
    delete[] tmp;
}

int Partition(SqTable& L, int low, int high) {
    int pivotloc = low;
    ElemType tmp = L.r[pivotloc];
    while (low < high) {
        while (low < high && L.r[high] >= tmp) {
            --high;
        }
        L.r[low] = L.r[high];
        while (low < high && L.r[low] <= tmp) {
            ++low;
        }
        L.r[high] = L.r[low];
    }
    L.r[low] = tmp;
    return low;
}

void QSort(SqTable& L, int low, int high) {
    if (low < high) {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
}

void QuickSort(SqTable& L) {
    QSort(L, 1, L.len);
}

void HeapAdjust(SqTable& L, int s, int m) {
    ElemType tmp = L.r[s];
    for (int i = 2 * s; i <= m; i *= 2) {
        if (i < m && L.r[i] < L.r[i + 1]) {
            ++i;
        }
        if (tmp >= L.r[i]) {
            break;
        }
        L.r[s] = L.r[i];
        s = i;
    }
    L.r[s] = tmp;
}

void HeapSort(SqTable& L) {
    int i;
    ElemType tmp;
    for (i = L.len / 2; i > 0; --i)
        HeapAdjust(L, i, L.len);
    for (i = L.len; i > 1; --i) {
        tmp = L.r[i];
        L.r[i] = L.r[1];
        L.r[1] = tmp;
        HeapAdjust(L, 1, i - 1);
    }
}

void Print(SqTable L) {
    int n = L.len;
    for (int i = 1; i <= n; ++i) {
        std::cout << L.r[i] << std::endl;
    }
}

int main() {
    int N = 200000;
    SqTable L;
    InitList(L, N);
    for (int i = 1; i <= N; ++i) {
        L.r[i] = i;
    }
    RandomShuffle(L);
    clock_t begin, end;
    // 冒泡排序
    SqTable L1;
    CopyList(L, L1);
    begin = clock();
    BubbleSort(L1);
    end = clock();
    printf("BubbleSort time: %g seconds\n",
           (float)(end - begin) / CLOCKS_PER_SEC);
    // 选择排序
    SqTable L2;
    CopyList(L, L2);
    begin = clock();
    SelectSort(L2);
    end = clock();
    printf("SelectSort time: %g seconds\n",
           (float)(end - begin) / CLOCKS_PER_SEC);
    // 插入排序
    SqTable L3;
    CopyList(L, L3);
    begin = clock();
    InsertSort(L3);
    end = clock();
    printf("InsertSort time: %g seconds\n",
           (float)(end - begin) / CLOCKS_PER_SEC);
    // 归并排序
    SqTable L4;
    CopyList(L, L4);
    begin = clock();
    MergeSort(L4);
    end = clock();
    printf("MergeSort time: %g seconds\n",
           (float)(end - begin) / CLOCKS_PER_SEC);
    // 快速排序
    SqTable L5;
    CopyList(L, L5);
    begin = clock();
    QuickSort(L5);
    end = clock();
    printf("QuickSort time: %g seconds\n",
           (float)(end - begin) / CLOCKS_PER_SEC);
    // 堆排序
    SqTable L6;
    CopyList(L, L6);
    begin = clock();
    HeapSort(L6);
    end = clock();
    printf("HeapSort time: %g seconds\n",
           (float)(end - begin) / CLOCKS_PER_SEC);
}
