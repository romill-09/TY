#include<bits/stdc++.h>
using namespace std;

bool checkPrime(int n)
{
    int count = 0;

    for(int i = 1; i <= sqrt(n); ++i)
    {
        if(n % i == 0)
        {
            count++;

            if(n / i != i)
            {
                count++;
            }
        }
    }

    if(count == 2)return true;
    else return false;
}

vector<int> getPrimeFactors(int n, vector<int> &primeFactors)
{
    for(int i = 2; i <= n; ++i)
    {
        if(n % i == 0)
        {
            if(checkPrime(i))
            {
                primeFactors.push_back(i);
            }
        }
    }

    return primeFactors;
}

int main()
{
    int n;
    cout << "Enter the number: ";
    cin >> n;

    vector<int> primeFactors = getPrimeFactors(n, primeFactors);

    cout << "Prime Factors for the given number are: " << endl;
    for(auto i : primeFactors)cout << i << " ";

    return 0;
}




