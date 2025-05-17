#include <bits/stdc++.h>
using namespace std;

// Function to create the Rail Fence Matrix for encryption
vector<vector<char>> initMatrix(const string& plain, int n) {
    int m = plain.size();
    vector<vector<char>> matrix(n, vector<char>(m, '-'));

    int r = 0, c = 0;
    bool down = true;

    for (char ch : plain) {
        matrix[r][c++] = ch;

        if (down) {
            if (r == n - 1) {
                down = false;
                r--;
            } else {
                r++;
            }
        } else {
            if (r == 0) {
                down = true;
                r++;
            } else {
                r--;
            }
        }
    }
    return matrix;
}

// Function to extract the cipher text from the Rail Fence Matrix
string cipherText(const vector<vector<char>>& matrix) {
    string cipher = "";
    for (const auto& row : matrix) {
        for (char ch : row) {
            if (ch != '-') {
                cipher += ch;
            }
        }
    }
    return cipher;
}

// Function to create Rail Matrix for decryption
void decryptionMatrix(vector<vector<char>>& matrix, int n, int m) {
    int r = 0, c = 0;
    bool down = true;

    for (int i = 0; i < m; ++i) {
        matrix[r][c++] = '*';

        if (down) {
            if (r == n - 1) {
                down = false;
                r--;
            } else {
                r++;
            }
        } else {
            if (r == 0) {
                down = true;
                r++;
            } else {
                r--;
            }
        }
    }
}

// Function to fill the Rail Matrix with the cipher text for decryption
void fillDecryptionMatrix(vector<vector<char>>& matrix, const string& cipher) {
    int k = 0;
    for (auto& row : matrix) {
        for (char& ch : row) {
            if (ch == '*') {
                ch = cipher[k++];
            }
        }
    }
}

// Function to decrypt the text from the Rail Matrix
string decryptionText(const vector<vector<char>>& matrix, int n, int m) {
    string decryptedText = "";
    int r = 0, c = 0;
    bool down = true;

    for (int i = 0; i < m; ++i) {
        decryptedText += matrix[r][c++];

        if (down) {
            if (r == n - 1) {
                down = false;
                r--;
            } else {
                r++;
            }
        } else {
            if (r == 0) {
                down = true;
                r++;
            } else {
                r--;
            }
        }
    }
    return decryptedText;
}

int main() {
    string plain;
    cout << "Enter the plain text: ";
    cin >> plain;

    int n;
    cout << "Enter the key: ";
    cin >> n;

    // Encryption
    vector<vector<char>> matrix = initMatrix(plain, n);

    cout << "\nRail Fence Matrix (Encryption):\n";
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch;
        }
        cout << endl;
    }

    string cipher = cipherText(matrix);
    cout << "\nCipher Text: " << cipher << endl;

    // Decryption
    int m = plain.size();

    decryptionMatrix(matrix, n, m);

    cout << "\nRail Fence Matrix (Marked for Decryption):\n";
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch;
        }
        cout << endl;
    }

    fillDecryptionMatrix(matrix, cipher);

    cout << "\nRail Fence Matrix (Filled with Cipher Text):\n";
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch;
        }
        cout << endl;
    }

    string decryptedText = decryptionText(matrix, n, m);
    cout << "\nDecrypted Text: " << decryptedText << endl;

    return 0;
}
