#include <iostream>
using namespace std;
#include <bits/stdc++.h>
#include <vector> 

template <typename T>
void printVectorOfVectors(const std::vector<std::vector<T>>& vec) {
    for (const auto& row : vec) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;  // Newline after each row
    }
}

vector<vector<int>> get_new_roads(vector<vector<int>> roads, vector<vector<int>> build_cost, int rows, int cols)
{
    vector<vector<int>> new_roads(rows, vector<int>(cols,0));
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(roads[i][j] == 0)
            {
                new_roads[i][j] = build_cost[i][j];
            }
            else
            {
                new_roads[i][j] = 0;

            }

        }
    }
    return new_roads;


}

int minKey(vector<int> key, bool mstSet[], int size)
{
    int min = INT_MAX, min_index;
    for(int v = 0; v < size; v++)
    {
        if(mstSet[v] == false && key[v] < min)
        {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

void primMST(vector<vector<int>> Build_Graph)

int main() {
    // Initialize roads, build_cost, and destroy_cost
    vector<vector<int>> roads = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    vector<vector<int>> build_cost = {
        {0, 2, 4},
        {2, 0, 3},
        {4, 3, 0}
    };

        vector<vector<int>> destroy_cost = {
        {0, 3, 1},
        {3, 0, 3},
        {1, 3, 0}
    };

    // Call get_new_roads
    vector<vector<int>> new_roads = get_new_roads(roads, build_cost, 3, 3);

    // Print the result using printVectorOfVectors
    cout << "New Roads Cost Matrix:" << endl;
    printVectorOfVectors(new_roads);

    return 0;
}
