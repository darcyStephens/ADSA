#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void printVector(vector<int> vec)
{
    for(int num : vec)
    { cout << num; }
    cout << "" << endl;
}

vector<int> schoolSubtraction(vector<int>n1, vector<int>n2, int base)
{
    
    while (n1.size() < n2.size())
        n1.insert(n1.begin(), 0);
    while (n2.size() < n1.size())
        n2.insert(n2.begin(), 0);


    vector<int> res;
    vector<int> tempN1 = n1;
    while (tempN1.size() < n2.size())
        tempN1.insert(tempN1.begin(), 0);

    int borrow = 0;
    for (int i = tempN1.size() - 1; i >= 0; i--)
    {
        int diff = tempN1[i] - (n2[i]) - borrow;
        if (diff < 0)
        {
            diff += base;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        res.push_back(diff);
    }

    while (res.size() > 1 && res.back() == 0)
        res.pop_back();
    reverse(res.begin(), res.end());
    printVector(res);
    return res;
}

int main()
{
    vector<int> n1  = {1,2,3};
    vector<int> n2 = {1,0};
    vector<int> result = schoolSubtraction(n1, n2, 10);
    printVector(result);

}