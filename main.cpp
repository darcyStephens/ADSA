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
        currSum = (n1[i] + n2[i] + carry);
        carry = (currSum/base);
        res.push_back((currSum) % base);
       
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
    // Read input, store in string input, including spaces
    string input;
    getline(cin, input);

    // Set up vectors for the two numbers and an integer for base
    vector<int> n1;
    vector<int> n2;
    int base;

    // Split input into parts
    size_t pos = input.find(' ');
    string str1 = input.substr(0, pos);
    input.erase(0, pos + 1);

    pos = input.find(' ');
    string str2 = input.substr(0, pos);
    input.erase(0, pos + 1);

    string strBase = input;

    // Convert string parts to respective integers
    for (char digit : str1)
    {
        n1.push_back(digit - '0');
    }

    for (char digit : str2)
    {
        n2.push_back(digit - '0');
    }

    base = stoi(strBase);

    // Perform the addition
    vector<int> result = schoolAddition(n1, n2, base);

    // Print the result
    printVector(result);

    return 0;
}
