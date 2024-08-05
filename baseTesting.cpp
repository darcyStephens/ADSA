#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> n2 = {1,2,3};
    vector<int> n1 = {2,3,4};
    vector<int> res;
    int current;
    int currSum = 0;
    int carry = 0;
    int base = 5;
    
    for(int i = n2.size() -1; i >= 0; i-- )
    {
        cout<< "carry is " << carry << endl;
        currSum = (n1[i] + n2[i] + carry);
        cout<< "current sum is " << currSum << endl;
        carry = (currSum/base);
        cout<< "new carry is " << carry << endl;
        res.push_back((currSum) % base);
        cout<< "pushing into vector " << (currSum) % base << endl;
        cout<< "  "<< endl;
        
    }
    if (carry > 0)
    {
        res.push_back(carry);
    }
    reverse(res.begin(), res.end());

    for (int num : res)
    {
        cout << num;
    }

    return 0;
}