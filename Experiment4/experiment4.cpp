#include <bits/stdc++.h>

using namespace std;

#define MAX_VERTEX_NUM 30
#define MAX_CITY_NAME_LENGTH 15
#define LINE_SIZE 15

typedef int CityType;
typedef string CityNameType;
typedef int DistanceType;
typedef struct {
    CityType city;
    CityNameType cityName;
} VertexType;
typedef int ArcType;
typedef struct {
    VertexType city1;
    VertexType city2;
    DistanceType dist;
} RailwayType;
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    ArcType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} MGraph;

VertexType VEXNULL = {0, "\0"};
int INF = INT_MAX;
vector<CityNameType> C;
vector<RailwayType> R;

void CreateGraph(MGraph& G);
int LocateVex(MGraph G, VertexType v);
int FirstAdjVex(MGraph G, int v);
int NextAdjVex(MGraph G, int v, int w);
void RailwayInfo(const char* file1, const char* file2);
bool VexEqual(VertexType v1, VertexType v2);
void VexAssign(VertexType& v1, VertexType v2);
vector<VertexType> Dijkstra(MGraph G, VertexType v1, VertexType v2);
void PrintPath(MGraph G, vector<VertexType> P);

void CreateGraph(MGraph& G) {
    G.vexnum = C.size();
    G.arcnum = R.size();
    for (int i = 0; i < G.vexnum; i++) {
        G.vexs[i].city = i;
        G.vexs[i].cityName = C[i];
    }
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            G.arcs[i][j] = INF;
        }
    }
    for (int k = 0; k < G.arcnum; k++) {
        int i = LocateVex(G, R[k].city1);
        int j = LocateVex(G, R[k].city2);
        G.arcs[i][j] = G.arcs[j][i] = R[k].dist;
    }
}

int LocateVex(MGraph G, VertexType v) {
    for (int i = 0; i < G.vexnum; i++) {
        if (VexEqual(G.vexs[i], v)) {
            return i;
        }
    }
    return -1;
}

int FirstAdjVex(MGraph G, int v) {
    for (int j = 0; j < G.vexnum; j++) {
        if (G.arcs[v][j] != 0) {
            return j;
        }
    }
    return -1;
}

int NextAdjVex(MGraph G, int v, int w) {
    for (int j = w + 1; j < G.vexnum; j++) {
        if (G.arcs[v][j] != 0) {
            return j;
        }
    }
    return -1;
}

void RailwayInfo(const char* file1, const char* file2) {
    ifstream infile1, infile2;
    infile1.open(file1, ios::in);
    infile2.open(file2, ios::in);
    string dataline;
    vector<RailwayType> railways;
    if (!infile1.is_open()) {
        cout << "File1 Not found" << endl;
        exit(1);
    } else {
        while (getline(infile1, dataline)) {
            int pos = dataline.find(' ');
            int size = dataline.size();
            CityNameType cityName = dataline.substr(pos + 1, size);
            C.push_back(cityName);
        }
        infile1.close();
    }
    if (!infile2.is_open()) {
        cout << "File2 Not found" << endl;
        exit(1);
    } else {
        while (getline(infile2, dataline)) {
            int pos1 = dataline.find(' ');
            int size = dataline.size();
            int pos2 = dataline.substr(pos1 + 1, size).find(' ') + pos1;
            CityType city1 = atof(dataline.substr(0, pos1).c_str());
            CityType city2 = atof(dataline.substr(pos1 + 1, pos2).c_str());
            DistanceType dist = atof(dataline.substr(pos2 + 1, size).c_str());
            VertexType v1 = {city1, C[city1]};
            VertexType v2 = {city2, C[city2]};
            RailwayType r = {v1, v2, dist};
            railways.push_back(r);
        }
        infile2.close();
    }
    R = railways;
}

bool VexEqual(VertexType v1, VertexType v2) {
    return v1.city == v2.city && v1.cityName == v2.cityName;
}

void VexAssign(VertexType& v1, VertexType v2) {
    v1.city = v2.city;
    v1.cityName = v2.cityName;
}

vector<VertexType> Dijkstra(MGraph G, VertexType v1, VertexType v2) {
    DistanceType D[MAX_VERTEX_NUM];
    VertexType P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int S[MAX_VERTEX_NUM] = {0};
    vector<VertexType> ans;
    for (int i = 0; i < G.vexnum; i++) {
        D[i] = G.arcs[v1.city][i];
        if (D[i] != INF) {
            VexAssign(P[i][0], v1);
            VexAssign(P[i][1], G.vexs[i]);
            VexAssign(P[i][2], VEXNULL);
        }
    }
    S[v1.city] = 1;
    D[v1.city] = 0;
    for (int i = 0; i < G.vexnum; i++) {
        DistanceType min = INF;
        int k = i;
        for (int j = 0; j < G.vexnum; j++) {
            if (!S[j] && D[j] < min) {
                min = D[j];
                k = j;
            }
        }
        S[k] = 1;
        for (int j = 0; j < G.vexnum; j++) {
            if (G.arcs[k][j] < INF && !S[j] && D[k] + G.arcs[k][j] < D[j]) {
                D[j] = D[k] + G.arcs[k][j];
                int w;
                for (w = 0; !VexEqual(P[k][w], VEXNULL); w++) {
                    VexAssign(P[j][w], P[k][w]);
                }
                VexAssign(P[j][w], G.vexs[j]);
                VexAssign(P[j][w + 1], VEXNULL);
            }
        }
    }
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        ans.push_back(P[v2.city][i]);
    }
    if (!S[v2.city]) {
        VertexType v = {-1, "\0"};
        ans.push_back(v);
    }
    return ans;
}

void PrintPath(MGraph G, vector<VertexType> P) {
    int n = P.size();
    int dist = 0;
    VertexType v = {-1, "\0"};
    if (VexEqual(P[n - 1], v)) {
        cout << "No Path" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (P[i].cityName != "\0") {
            cout << (i == 0 ? "Path: " : "--->") << P[i].cityName;
            if (P[i + 1].cityName != "\0") {
                dist += G.arcs[P[i].city][P[i + 1].city];
            }
        } else {
            cout << endl;
            break;
        }
    }
    cout << "Distance: " << dist << endl;
}

void PrintGraph(MGraph G) {
    for (int i = 0; i < G.vexnum; i++) {
        cout << G.vexs[i].cityName << endl;
    }
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            cout << ((G.arcs[i][j] != INF) ? G.arcs[i][j] : 0) << ' ';
        }
        cout << endl;
    }
}

void PrintRailwayInfo(vector<RailwayType> R) {
    int n = R.size();
    for (int i = 0; i < n; i++) {
        cout << R[i].city1.cityName << "<------->" << R[i].city2.cityName
             << ": " << R[i].dist << endl;
    }
}

void DeleteCity(MGraph& G, CityType city) {
    G.vexs[city].cityName = "\0";
    for (int i = 0; i < G.vexnum; i++) {
        G.arcs[i][city] = G.arcs[city][i] = INF;
    }
}

int main() {
    RailwayInfo("city.txt", "dist.txt");
    MGraph G;
    CreateGraph(G);
    CityType city1, city2, city3;
    int cityNum = C.size();
    while (true) {
        cout << "Please enter departure and terminal station(city). "
                "Enter [-1 *] to exit"
             << endl;
        cin >> city1 >> city2;
        if (city1 == -1) {
            break;
        } else if (city1 < 0 || city1 >= cityNum || city2 < 0 ||
                   city2 >= cityNum) {
            cout << "Invalid input" << endl;
            continue;
        }
        VertexType v1 = G.vexs[city1], v2 = G.vexs[city2];
        PrintPath(G, Dijkstra(G, v1, v2));
        cout << "Please enter the city to delect. "
                "Enter [-1] to exit, [-2] to skip"
             << endl;
        cin >> city3;
        if (city3 == -1) {
            break;
        } else if (city3 == -2) {
            continue;
        } else if (city3 < 0 || city3 >= cityNum) {
            cout << "Invalid input" << endl;
            continue;
        }
        DeleteCity(G, city3);
        PrintPath(G, Dijkstra(G, v1, v2));
    }
    return 0;
}
