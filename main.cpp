#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> removeLeadingZeros(vector<int> vec)
{
    //find first non zero
    int Z =0;
    int len = vec.size();
    while (vec[Z] == 0)
    {
        if(Z > len)
        {
            break;
        }
        
        Z++;
    }

    //place into new vector
    vector<int> clean(vec.begin() + Z, vec.end());
    return clean;

}
vector<int> schoolAddition(vector<int> n1, vector<int> n2, int base)
{
    vector<int> res;
    if (n1.size() < n2.size())
        swap(n1, n2);
    while (n2.size() < n1.size())
        n2.insert(n2.begin(), 0);

    int carry = 0;
    for (int i = n1.size() - 1; i >= 0; i--)
    {
        int currSum = n1[i] + n2[i] + carry;
        carry = currSum / base;
        res.push_back(currSum % base);
    }

    if (carry > 0)
        res.push_back(carry);
    reverse(res.begin(), res.end());
    return res;
}

void printVector(const vector<int> &vec)
{
    for (int num : vec)
    {
        cout << num;
    }
    cout << endl;
}

vector<int> multiplySingle(int n1, int n2, int base)
{
    int product = n1 * n2;
    vector<int> res;

    // Convert the product to the given base
    while (product > 0)
    {
        res.push_back(product % base);
        product /= base;
    }

    if (res.empty())
        res.push_back(0);

    reverse(res.begin(), res.end());
    return res;
}

vector<int> multiplyByBasePower(vector<int> num, int power)
{
    vector<int> res;
    res = num;
    while (power--)
    {
        res.push_back(0);
    }
    return res;
}

vector<int> schoolSubtraction(vector<int> n1, vector<int> n2, int base)
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

vector<int> Karatsuba(vector<int> n1, vector<int> n2, int base)
{
    while (n1.size() < n2.size())
        n1.insert(n1.begin(), 0);
    while (n2.size() < n1.size())
        n2.insert(n2.begin(), 0);
    int n = n1.size();
    
    if (n == 0)
        return {0};
    if (n == 1)
    {
        return multiplySingle(n1[0], n2[0], base);
    }

    int mid = n/2;

    vector<int> X1(n1.begin(), n1.begin() + mid);
    vector<int> X2(n1.begin() + mid, n1.end());
    vector<int> Y1(n2.begin(), n2.begin() + mid);
    vector<int> Y2(n2.begin() + mid, n2.end());
    //printVector(X1);

    vector<int> P2 = Karatsuba(X1, Y1, base);
    vector<int> P0 = Karatsuba(X2, Y2, base);

    vector<int> sumX1X2 = schoolAddition(X1, X2, base);
    vector<int> sumY1Y2 = schoolAddition(Y1, Y2, base);

    vector<int> P1 = Karatsuba(sumX1X2, sumY1Y2, base);

    P1 = schoolSubtraction(P1, schoolAddition(P2, P0, base), base);

    P2 = multiplyByBasePower(P2, 2 * (n - mid));
    P1 = multiplyByBasePower(P1, n - mid);

    return schoolAddition(schoolAddition(P2, P1, base), P0, base);
}

int main()
{
    string input;
    getline(cin, input);

    vector<int> n1, n2;
    int base;

    size_t pos = input.find(' ');
    string str1 = input.substr(0, pos);
    input.erase(0, pos + 1);

    pos = input.find(' ');
    string str2 = input.substr(0, pos);
    input.erase(0, pos + 1);

    string strBase = input;

    for (char digit : str1)
        n1.push_back(digit - '0');
    for (char digit : str2)
        n2.push_back(digit - '0');
    base = stoi(strBase);

    


    vector<int> result = schoolAddition(n1, n2, base);
    //cout << "Addition: ";
    printVector(result);

    vector<int> kat = Karatsuba(n1, n2, base);
    kat = removeLeadingZeros(kat);
   // cout << "Multiplication: ";
   printVector(kat);

    return 0;
}
