#define inf 1000000
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int min(int a, int b) {
    return (a < b ? a : b);
}

bool isValue(int k) {
    return (k != 0 && k != inf);
}

void printGraph(vector<vector<int>> adj) {
    for (int i = 0; i < adj.size(); i++) {
        if (any_of(adj[i].begin(), adj[i].end(), [](int k) {return (k != 0 && k != inf);}))
            cout << "Вершина " << i + 1 << " связана с вершинами" << endl;
        for (int j = 0; j < adj.size(); j++) {
            if (adj[i][j] != 0 && adj[i][j] != inf)
                cout << "  Вершина " << j + 1 << " с весом " << adj[i][j] << endl;
        }
        cout << endl;
    }
}

void addEdge(vector<vector<int>>& adj, int u, int v, int weight) {
    if (u > adj.size() || v > adj.size() || u == v) {
        cout << "Некорректный ввод" << endl;
        return;
    }
    adj[u - 1][v - 1] = weight;
}

void printMatrix(vector<vector<int>> adj) {
    cout << " ";
    for (int i = 0; i < adj.size(); i++) {
        cout << setw(5) << i + 1;
    }
    cout << endl;
    for (int i = 0; i < adj.size(); i++) {
        cout << i + 1;
        for (int j = 0; j < adj.size(); j++) {
            if (adj[i][j] == inf)
                cout << setw(5) << "inf";
            else
                cout << setw(5) << adj[i][j];
        }
        cout << endl;
    }
}

vector<vector<int>> floydAlgo(vector<vector<int>> adj, vector<vector<int>> &pathsMatrix) {
    vector<vector<int>> res = adj;
    for (int k = 0; k < adj.size(); k++) {
        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj.size(); j++) {
                if (res[i][k] + res[k][j] < res[i][j]) {
                    res[i][j] = res[i][k] + res[k][j];
                    pathsMatrix[i][j] = pathsMatrix[i][k];
                }
            }
        }
    }
    return res;
}

void getShortestPath(vector<vector<int>> pathsMatrix, int u, int v) {
    cout << u + 1 << " -> ";
    int c = pathsMatrix[u][v];
    while (c != v) {
        cout << c + 1 << " -> ";
        c = pathsMatrix[c][v];
    }
    cout << v + 1<< endl;
}

// Нахождение кратчайшего пути методом Флойда
int main()
{
    setlocale(0, "Russian");

    int n;
    vector<vector<int>> adj;

    cout << "Практическая работа №5. Основные алгоритмы работы с графами. Киселёв Максим. ИКБО-08-21. Вариант №14." << endl;
    cout << "Выберите вариант работы с графом: " << endl;
    cout << "1) Граф из варианта" << endl;
    cout << "2) Произвольный граф" << endl;

    int ch;
    cin >> ch;
    if (ch == 1) {
        n = 6;
        adj =
        {
            {0, 2, 4, 5, inf, inf},
            {inf, 0, inf, 4, 3, inf},
            {inf, inf, 0, inf, inf, 7},
            {inf, inf, inf, 0, 6, 4},
            {inf, inf, inf, inf, 0, 2},
            {inf, inf, inf, inf, inf, 0}
        };
    }
    else {
        cout << "Введите количество вершин: ";
        cin >> n;
        adj.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) adj[i][j] == 0;
                else adj[i][j] = inf;
            }
        }
        cout << "Введите ребра в формате \"Вершина1 Вершина2 Вес\"" << endl;
        cout << "Для завершения ввода введите 0" << endl;
        while (true) {
            int u;
            cin >> u;
            if (u == 0) break;
            int v, weight;  
            cin >> v >> weight;
            addEdge(adj, u, v, weight);
        }
    }
    cout << endl;

    vector<vector<int>> pathsMatrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != 0 && adj[i][j] != inf)
                pathsMatrix[i][j] = j;
        }
    }

    cout << "Матрица смежности графа" << endl;
    printMatrix(adj);
    cout << endl;

    vector<vector<int>> minPaths = floydAlgo(adj, pathsMatrix);
    cout << "Матрица кратчайших путей" << endl;
    printMatrix(minPaths);
    cout << endl;
    
    cout << "Кратчайшие пути для каждой вершины" << endl;
    for (int i = 0; i < n; i++) {
        if (any_of(adj[i].begin(), adj[i].end(), [](int k) {return (k != 0 && k != inf); }))
            cout << "Из вершины " << i + 1 << endl;
        for (int j = 0; j < n; j++) {
            if (minPaths[i][j] != 0 && minPaths[i][j] != inf) {
                cout << "  До вершины " << j + 1 << ": ";
                getShortestPath(pathsMatrix, i, j);
            }
        }
    }
    return 0;
}