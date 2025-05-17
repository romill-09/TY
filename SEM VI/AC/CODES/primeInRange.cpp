#include<bits/stdc++.h>
using namespace std;

bool checkPrime(int n)
{
    if(n == 1)return true;
    
    int cnt = 0;
    for(int i = 1; i <= sqrt(n); i++)
    {
        if(n % i == 0)
        {
            cnt++;

            if(n / i != i)
            {
                cnt++;
            }
        }
    }

    if(cnt == 2)return true;
    else return false;
}

int main()
{

    int a, b;
    cout << "Enter the numbers a & b: ";
    cin >> a >> b;
    
    cout << "Prime number between " << a << " & " << b << ": " << endl; 
    for(int i = a; i <= b; ++i)
    {
        if(checkPrime(i))
        {
            cout << i << " ";
        }
    }
    

    return 0;
}

