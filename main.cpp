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
vector<int> schoolAddition(vector<int> n1, vector<int> n2)
{
    vector<int> result;
    // have n1 be the longer of the two digits
    if (n1.size() < n2.size())
    {
        swap(n1, n2);
    }
    //fill smaller one with zeros
    while (n2.size() < n1.size())
    {
        n2.insert(n2.begin(), 0);
    }

    int carry = 0;

    int sum = 0;

    for (int i = n1.size() - 1; i >= 0; i--)
    {
       sum = n1[i] + n2[i] + carry;
       carry = sum / 10;
       result.push_back(sum % 10);
    }

    if (carry)
    {
        result.push_back(carry);
    }
    reverse(result.begin(), result.end());
    return result;
}

int main()
{
    // read input, store in string input, inlcuding spaces
    string input;
    getline(cin, input);

    // set up 3 vectors
    vector<int> n1;
    vector<int> n2;
    vector<int> n3;

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
            else
            {
                n3.push_back(num);
            }
            input.erase(input.begin());
        }
    }

    vector<int> res = schoolAddition(n1, n2);

    return 0;
}
