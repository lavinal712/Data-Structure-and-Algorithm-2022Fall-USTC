#include <bits/stdc++.h>

using namespace std;

typedef char TElemType;
typedef unsigned int WeightType;
typedef struct {
    TElemType data;
    WeightType weight;
    int parent, lchild, rchild;
} HTNode, *HuffmanTree;
typedef HTNode* HuffTree;
typedef char** HuffCode;
typedef struct BiTNode {
    TElemType data;
    WeightType weight;
    BiTNode* parent;
    BiTNode* lchild;
    BiTNode* rchild;
}* BiTree;

HuffTree HT;
HuffCode HC;
unordered_map<char, int> FM;
const unsigned int MAX_WEIGHT = UINT_MAX;
const unsigned int LINE_SIZE = 1024;
const unsigned int MAX_LINE_SIZE = INT_MAX / 2;

void CreateHuffmanTree(HuffmanTree& HT, int n);
void Select(HuffmanTree HT, int s, int& l, int& r);
void HuffmanCoding(HuffTree HT, char**& HC, int n);
void PrintHuffmanCode(HuffCode HC, int n);
void PrintHuffmanTree(HuffTree HT, int n);
void ReadFrequency(const char* filename);

void CreateHuffmanTree(HuffmanTree& HT, int n) {
    if (n <= 1) {
        return;
    }
    int m = 2 * n - 1;
    int s1, s2;
    auto iter = FM.begin();
    HT = (HuffTree)malloc(sizeof(HTNode) * (m + 1));
    for (int i = 1; i <= m; i++) {
        if (i <= n) {
            HT[i].data = iter->first;
            HT[i].weight = iter->second;
            iter++;
        } else {
            HT[i].data = '\0';
            HT[i].weight = 0;
        }
        HT[i].lchild = HT[i].rchild = HT[i].parent = 0;
    }
    for (int i = n + 1; i <= m; i++) {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void Select(HuffmanTree HT, int s, int& l, int& r) {
    WeightType WL = MAX_WEIGHT, WR = MAX_WEIGHT;
    for (int i = 0; i <= s; ++i) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < WL) {
                WR = WL;
                WL = HT[i].weight;
                r = l;
                l = i;
            } else if (HT[i].weight < WR) {
                WR = HT[i].weight;
                r = i;
            }
        }
    }
}

void HuffmanCoding(HuffTree HT, HuffCode& HC, int n) {
    HC = (char**)malloc(sizeof(char*) * (n + 1));
    char* code = (char*)malloc(sizeof(char) * n);
    code[n - 1] = '\0';
    for (int i = 1; i <= n; i++) {
        int start = n - 1;
        for (int c = i, p = HT[i].parent; p != 0; c = p, p = HT[p].parent) {
            if (HT[p].lchild == c) {
                code[--start] = '0';
            } else {
                code[--start] = '1';
            }
        }
        HC[i] = (char*)malloc(sizeof(char) * (n - start));
        strcpy(HC[i], &code[start]);
    }
    free(code);
}

void PrintHuffmanCode(HuffTree HT, HuffCode HC, int n) {
    for (int i = 1; i <= n; i++) {
        if (HT[i].data == '\t') {
            cout << "\\t";
        } else if (HT[i].data == '\n') {
            cout << "\\n";
        } else {
            cout << HT[i].data;
        }
        cout << ": " << HC[i] << endl;
    }
}

void PrintHuffmanTree(HuffTree HT, int n) {
    int m = 2 * n - 1;
    cout << "data"
         << " "
         << "weight"
         << " "
         << "lchild"
         << " "
         << "rchlid"
         << " "
         << "parent" << endl;
    for (int i = 1; i <= m; i++) {
        if (HT[i].data == '\t') {
            cout << "\\t";
        } else if (HT[i].data == '\n') {
            cout << "\\n";
        } else {
            cout << HT[i].data;
        }
        cout << ": " << HT[i].weight << " " << HT[i].lchild << " "
             << HT[i].rchild << " " << HT[i].parent << endl;
    }
}

void PrintVisualTree(HuffTree HT, int p, int type, int level) {
    int i;
    if (p == 0) {
        return;
    }
    PrintVisualTree(HT, HT[p].rchild, 2, level + 1);
    switch (type) {
        case 0:
            cout << int(HT[p].data) << endl;
            break;
        case 1:
            for (i = 0; i < level; i++) {
                cout << '\t';
            }
            cout << "\\ " << int(HT[p].data) << endl;
            break;
        case 2:
            for (i = 0; i < level; i++) {
                cout << '\t';
            }
            cout << "/ " << int(HT[p].data) << endl;
            break;
    }
    PrintVisualTree(HT, HT[p].lchild, 1, level + 1);
}

void ReadFrequency(const char* filename, string& data) {
    ifstream infile;
    char* dataline = (char*)malloc(sizeof(char) * LINE_SIZE);
    infile.open(filename, ios::in);
    if (!infile.is_open()) {
        cout << "Not found" << endl;
        return;
    } else {
        int countline = 0;
        while (infile.getline(dataline, LINE_SIZE)) {
            int n = strlen(dataline);
            for (int i = 0; i < n; i++) {
                char c = dataline[i];
                if (FM.find(c) != FM.end()) {
                    ++FM[c];
                } else {
                    FM[c] = 1;
                }
            }
            countline++;
            data += dataline;
            data += '\n';
        }
        FM['\n'] = countline;
        infile.close();
    }
}

void Encryption(string data1, string& data2, HuffTree HT, HuffCode HC, int n) {
    FILE* fp = fopen("Encryption.txt", "w+");
    int len = data1.length();
    for (int i = 0; i < len; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (data1[i] == HT[j].data) {
                fprintf(fp, HC[j]);
                data2 += HC[j];
            }
        }
    }
    fclose(fp);
}

void Decryption(HuffTree HT, int n) {
    char* dataline = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
    ifstream infile;
    infile.open("Encryption.txt");
    infile.getline(dataline, MAX_LINE_SIZE);
    infile.close();
    ofstream outfile;
    outfile.open("Decryption.txt");
    int root = 2 * n - 1;
    int len = strlen(dataline);
    for (int i = 0; i < len; ++i) {
        if (dataline[i] == '0') {
            root = HT[root].lchild;
        } else if (dataline[i] == '1') {
            root = HT[root].rchild;
        }
        if (HT[root].lchild == 0 && HT[root].rchild == 0) {
            outfile << HT[root].data;
            root = 2 * n - 1;
        }
    }
    outfile.close();
}

int main() {
    string origindata;
    string encrypteddata;
    ReadFrequency("stdio.h", origindata);
    int n = FM.size();
    CreateHuffmanTree(HT, n);
    // PrintHuffmanTree(HT, n);
    PrintVisualTree(HT, 2 * n - 1, 0, 0);
    HuffmanCoding(HT, HC, n);
    // PrintHuffmanCode(HT, HC, n);
    Encryption(origindata, encrypteddata, HT, HC, n);
    cout << "Encryption rate is "
         << encrypteddata.length() / (8.0 * origindata.length()) << endl;
    Decryption(HT, n);
    return 0;
}