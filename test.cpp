#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> connected_graph(vector<vector<int>> roads) {
    vector<vector<int>> new_roads(roads.size(), vector<int>(roads[0].size(), 0));

    for (int i = 0; i < roads.size(); i++) {
        for (int j = 0; j < roads[i].size(); j++) {
            if (roads[i][j] == 0) {
                new_roads[i][j] = 1;
                roads[i][j] = 1;
            } else {
                new_roads[i][j] = 0;
            }
        }
    }
    return new_roads;
}

int main() {
    // Initialize 3x3 vectors with different combinations of 1s and 0s
    vector<vector<int>> roads = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };

    vector<vector<int>> build_cost = {
        {5, 2, 6},
        {3, 4, 7},
        {8, 1, 9}
    };

    vector<vector<int>> destroy_cost = {
        {3, 7, 1},
        {6, 2, 5},
        {4, 8, 0}
    };

    // Call the connected_graph function to calculate new roads
    vector<vector<int>> new_roads = connected_graph(roads);

    // Print the new roads matrix
    cout << "New Roads:" << endl;
    for (int i = 0; i < new_roads.size(); i++) {
        for (int j = 0; j < new_roads[i].size(); j++) {
            cout << new_roads[i][j] << " ";
        }
        cout << endl;
    }
    cout << "connected graph:" << endl;
    for (int i = 0; i < roads.size(); i++) {
        for (int j = 0; j < roads[i].size(); j++) {
            cout << roads[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
