#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// utility function for testing
void printVector(vector<int> vec)
{
    for (int num : vec)
    {
        cout << num;
    }
}

// function to call
vector<int> schoolAddition(vector<int> n1, vector<int> n2, int base)
{
    vector<int> res;
    // have n1 be the longer of the two digits
    if (n1.size() < n2.size())
    {
        swap(n1, n2);
    }
    // fill smaller one with zeros
    while (n2.size() < n1.size())
    {
        n2.insert(n2.begin(), 0);
    }
    //make variables
    int carry = 0;
    int currSum = 0;

    //iterate from LSB to MSB
    for (int i = n1.size() - 1; i >= 0; i--)
    {
       // cout << "carry is " << carry << endl;
        currSum = (n1[i] + n2[i] + carry);
       // cout << "current sum is " << currSum << endl;
        carry = (currSum/base);
       // cout << "new carry is " << carry << endl;
        res.push_back((currSum) % base);
       // cout << "pushing into vector " << (currSum) % base << endl;
       // cout << "  " << endl;
    }

    //pushing in carry after summation if it is greater than zero
    if (carry > 0)
    {
        res.push_back(carry);
    }

    //reversing the result vector so it works
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    // read input, store in string input, inlcuding spaces
    string input;
    getline(cin, input);

    // set up 3 vectors
    vector<int> n1;
    vector<int> n2;
    int base;

    // break into seperate numbers
    int count = 0;
    while (input.length() != 0)
    {
        if (input[0] == ' ')
        {
            input.erase(input.begin());
            count++;
        }
        else
        {
            // convert to int
            int num = input[0] - '0';
            if (count == 0)
            {
                n1.push_back(num);
            }
            else if (count == 1)
            {
                n2.push_back(num);
            }
            else{
                base = num;
            }

            input.erase(input.begin());
        }
    }

    vector<int> result = schoolAddition(n1, n2, base);
    for (int num : result)
    {
        cout << num;
    }

    return 0;
}
