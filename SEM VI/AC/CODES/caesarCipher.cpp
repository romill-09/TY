#include<bits/stdc++.h>
using namespace std;


int main()
{
    cout << "Enter the mode, Encrypt - 0, Decrypt - 1" << endl;
    int mode;
    cin >> mode;

    if(mode == 0)
    {
        cout << "Enter the Plain Text: ";
        string plain;
        cin >> plain;

        for(int key = 1; key <= 25; ++key)
        {
            for(auto &c : plain)
            {
                int index = c - 'a';
                index = (index + key) % 26;
                cout << (char)('a' + index);
            }
            cout << endl;
        }
    }
    else if(mode == 1){
        cout << "Enter the Cipher Text: ";
        string cipher;
        cin >> cipher;

        for(int key = 1; key <= 25; ++key)
        {
            for(auto &c : cipher)
            {
                int index = c - 'a';
                index = (index - key);
                if(index < 0)index += 26;

                cout << (char)('a' + index);
            }
            cout << endl;
        }
    }


    return 0;
}
