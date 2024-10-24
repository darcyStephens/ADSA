#include <bits/stdc++.h>
using namespace std;

// Helper function to convert a character to its respective build/destroy cost
int convertCost(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';  // 0-25
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;  // 26-51
    return INT_MAX;  // In case of an invalid character
}

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n, -1);
        rank.resize(n, 1);
    }

    int find(int x) {
        if (parent[x] == -1) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Graph {
public:
    int n;  // Number of cities
    vector<vector<int>> edges;  // Edges in the format {cost, source, target}

    Graph(int size) : n(size) {}

    // Add edges from build and destroy matrices
    void addEdges(vector<string>& country, vector<string>& build, vector<string>& destroy) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                
                if (country[i][j] == '1') {
                    // There's an existing road, consider the destroy cost
                    int destroyCost = convertCost(destroy[i][j]);
                    edges.push_back({destroyCost, i, j});
                } else {
                    // No existing road, consider the build cost
                    int buildCost = convertCost(build[i][j]);
                    edges.push_back({buildCost, i, j});
                }
            }
        }
    }

    // Kruskal's algorithm to build the MST
    int buildMST() {
        sort(edges.begin(), edges.end());  // Sort edges by cost

        DSU dsu(n);
        int totalCost = 0;
        for (auto& edge : edges) {
            int cost = edge[0];
            int u = edge[1];
            int v = edge[2];

            if (dsu.find(u) != dsu.find(v)) {
                dsu.unite(u, v);
                totalCost += cost;
            }
        }
        return totalCost;
    }
};

int main() {
    // Example input: 3 cities
    vector<string> country = {"011", "101", "110"};
    vector<string> build = {"ABD", "BAC", "DCA"};
    vector<string> destroy = {"ABD", "BAC", "DCA"};

    int n = country.size();  // Number of cities

    Graph g(n);
    g.addEdges(country, build, destroy);

    int minCost = g.buildMST();

    cout << "Minimum cost for reconstruction: " << minCost << endl;
    return 0;
}
