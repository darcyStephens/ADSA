#include <bits/stdc++.h>
using namespace std;
int convertCost(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        return c - 'A'; //0-25
    }
    if(c >= 'a' && c <='z')
    {
        return c - 'a' + 26;
    }
    return -1;
}


class DSU
{
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n)
    {
        parent.resize(n, -1);
        rank.resize(n, 1);
    }

    int find(int target)
    {
        if (parent[target] == -1)
        {
            return target;
        }
        return parent[target] = find(parent[target]);
    }

    bool unite(int x, int y)
    {
        int set1 = find(x);
        int set2 = find(y);

        if (set1 != set2)
        {
            if (rank[set1] < rank[set2])
            {
                parent[set1] = set2;
            }
            else if (rank[set1] > rank[set2])
            {
                parent[set2] = set1;
            }
            else
            {
                parent[set2] = set1;
                rank[set1] += 1;
            }
            return true; //united successfully
        }
        return false; //bum barm
    }
};

class Graph
{
public:
    //contains cost, row and cols position
    vector<tuple<int, int, int>> create; //roads that don't exist and need to be built
    vector<tuple<int, int, int>> remove; //roads that exist and can be destroyed
    int n;
    Graph(int size) : n(size) {}

    void addEdge(const vector<string>& country, const vector<string>& build, const vector<string>& destroy)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            //j = i+1 to avoid redundancy
            {
                if(country[i][j] == '1')
                {
                    //existing road, consider deletion cost
                    int destroy_cost = convertCost(destroy[i][j]);
                    remove.push_back({destroy_cost, i, j});
                }
                else
                {
                    //road doesn't exist, consider build cost
                    int build_cost = convertCost(build[i][j]);
                    create.push_back({build_cost, i, j});
                }
            }
        }
    }

    int build_MST()
    {
        int total_cost = 0;
        //sort for highest delete cost
        sort(remove.rbegin(), remove.rend());
        //sort for smallest build cost
        sort(create.begin(), create.end());
       

        DSU s(n);

        //remove redundent roads
        for (auto& [cost, source, target] : remove)
        {
            
            if (!s.unite(source, target))
            {
                total_cost += cost;
            }
        }

        //build new roads
        for (auto& [cost, source, target] : create)
        {
            
            if (s.unite(source, target))
            {
                total_cost += cost;
            }
        }

        return total_cost;
    }
};



int main()
{
    //builds an MST from both deletion and build cost, doesn't actually do it right.
    //end up with just wrong answer
    vector<string> country = {"011", "101", "110"};
    vector<string> build = {"ABD", "BAC", "DCA"};
    vector<string> destroy = {"ABD", "BAC", "DCA"};

    int n = country.size();  // Number of cities

    Graph g(n);
    g.addEdge(country, build, destroy);

    int minCost = g.build_MST();

    cout << "Minimum cost for reconstruction: " << minCost << endl;
    return 0;
}
    