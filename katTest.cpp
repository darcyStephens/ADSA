#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// helper functions
void printVector(vector<int> vec)
{
    for (int num : vec)
    {
        cout << num;
    }
}

vector<int> add(const std::vector<int> &num1, const std::vector<int> &num2, int base)
{
    vector<int> res;
    // have A be the longer of the two digits
    int maxSize = max(num1.size(), num2.size());
    // make variables
    int carry = 0;
    int currSum = 0;

    // iterate from LSB to MSB
    for (int i = 0; i < maxSize; i++)
    {
        currSum = (num1[i] + num2[i] + carry);
        carry = (currSum / base);
        res.push_back((currSum) % base);
    }

    // pushing in carry after summation if it is greater than zero
    if (carry > 0)
    {
        res.push_back(carry);
    }

    printVector(res);
    cout << "" << endl;

    return res;
}

vector<int> subtract(const std::vector<int> &num1, const std::vector<int> &num2, int base)
{
    vector<int> subRes;
    int borrow;

    for (int i = 0; i < num1.size(); i++)
    {
        int diff = num1[i] - num2[i] - borrow;
        if (diff < 0)
        {
            diff += base;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        subRes.push_back(diff);
    }

    while (subRes.size() > 1 && subRes.back() == 0)
    {
        subRes.pop_back();
    }

    printVector(subRes);
    cout << "" << endl;

    return subRes;
}

vector<int> shift(const std::vector<int> &num, int shift)
{
    std::vector<int> result = num;
    result.insert(result.begin(), shift, 0);
    return result;
}

// the alg chat gpt wrote
vector<int> Katsuba(const vector<int> &A, const vector<int> &B, int base)
{
    int n = max(A.size(), B.size());
    if (n == 1)
    {
        int product = A[0] * B[0];
        return {product % base, product / base};
    }

    int halfSize = n / 2;

    vector<int> aLow(A.begin(), A.begin() + halfSize);
    vector<int> aHigh(A.begin() + halfSize, A.end());
    vector<int> bLow(B.begin(), B.begin() + halfSize);
    vector<int> bHigh(B.begin() + halfSize, B.end());

    vector<int> z0 = Katsuba(aLow, bLow, base);
    vector<int> z1 = Katsuba(add(aLow, aHigh, base), add(bLow, bHigh, base), base);
    vector<int> z2 = Katsuba(aHigh, bHigh, base);

    vector<int> result = add(shift(z2, 2 * halfSize), shift(subtract(subtract(z1, z2, base), z0, base), halfSize), base);
    result = add(result, z0, base);
    return result;
}

int main()
{
    const vector<int> A = {1, 5};
    const vector<int> B = {2, 1};
    int first_sum = 0;
    int second_sum = 0;
    int mult_sum = 0;
    int total_sum = 0;
    vector<int> result;
    Katsuba(A, B, 10);
    for (int num : result)
    {
        cout << num;
    }
    return 0;
}
