#include<bits/stdc++.h>
using namespace std;

int main()
{

    int a, b;
    cout << "Enter the numbers a & b: ";
    cin >> a >> b;

    int q = 0, r = 0, s = 0, t = 0, r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;

    while(r2 > 0)
    {
        q = r1 / r2;

        r = r1 % r2;

        s = s1 - (s2 * q);
        t = t1 - (t2 * q);

        r1 = r2;
        r2 = r;
        s1 = s2;
        s2 = s;
        t1 = t2;
        t2 = t;
    }

    cout << "gcd: " << r1 << " s: " << s1 << " t: " << t1 << endl;

    return 0;
}
