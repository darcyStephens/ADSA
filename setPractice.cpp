#include <bits/stdc++.h>

class Disjset
{

public:
    int *rank;
    int *parent, n;
    Disjset(int n)
    {
        rank = new int[n];
        parent = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // recursive traversing of parent array until we hit a node that is the parent of itself
    // O(log n) average case
    int find(int target)
    {
        // if target is parent of itselft
        if (parent[target] == target)
        {
            return target;
        }
        else
        {
            // target is not parent of itself, is not the representatve of its set
            // find on target parent
            int result = find(parent[target]);
            std::cout<<result<<std::endl;

            // caching
            parent[target] = result;
            return result;
        }
    }

    // find the representatives of the inputs sets
    // O(n)
    void Union(int i, int j)
    {
        // find representatives of input sets
        int irep = find(i);
        int jrep = find(j);

        if (irep == jrep)
        {
            return;
        }
        if (rank[irep] < rank[jrep])
        {
            // set i parent to j parent
            // moving all of i's set into j's set
            parent[irep] = jrep;
        }
        else if (rank[irep] > rank[jrep])
        {
            parent[jrep] = irep;
        }
        else
        {
            // ranks are equal. increment rank
            parent[jrep] = irep;
            rank[irep] = rank[irep] + 1;
        }
    }

    void print(int *list, int size)
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << list[i];
        }
        std::cout <<std::endl;
    }
};

// if 2 elements are in the same tree
// they are in the same disjoint set
// root node of the tree is the representative set

int main()
{
    Disjset DJ(5);
    DJ.print(DJ.parent, 5);
    DJ.print(DJ.rank, 5);
    DJ.Union(2, 0);
    DJ.Union(4, 2);
    DJ.Union(3, 1);
    DJ.print(DJ.parent, 5);
    DJ.print(DJ.rank, 5);
    DJ.find(4);
    std::cout<<std::endl;
    DJ.find(3);
    std::cout<<std::endl;
    DJ.find(2);
    std::cout<<std::endl;
    DJ.find(1);
    std::cout<<std::endl;
    DJ.find(0);
    
    // if (DJ.find(4) == DJ.find(0)) 
    //     std::cout << "Yes\n"; 
    // else
    //     std::cout << "No\n"; 
    // if (DJ.find(1) == DJ.find(0)) 
    //     std::cout << "Yes\n"; 
    // else
    //     std::cout << "No\n"; 
}