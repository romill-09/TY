#include <bits/stdc++.h>
using namespace std;


// Function to create the Columnar Matrix for encryption
vector<vector<char>> initMatrix(const string &plain, int n)
{
   int p = plain.size();


   vector<vector<char>> v(n, vector<char>(n, '_'));


   for (int i = 0, j = 0, k = 0; k < p; ++j)
   {
      if (j == n)
      {
         j = 0;
         i++;
      }
      v[i][j] = plain[k++];
   }


   return v;
}


string encryptedText(vector<vector<char>> &matrix, int n)
{
   string cipherText = "";


   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < n; ++j)
      {
         cipherText += matrix[j][i];
      }
   }


   return cipherText;
}


vector<vector<char>> cipherTextToDmatrix(string &cipherText, int n)
{
   int c = cipherText.size();


   vector<vector<char>> v(5, vector<char>(5, '_'));


   for (int i = 0, k = 0; i < n; ++i)
   {
      for(int j = 0; j < n && k < cipherText.size(); ++j)
      {
         v[j][i] = cipherText[k++];
      }
   }


   return v;
}


string decryptionText(vector<vector<char>> &decryptionMatrix)
{
   string decryptedText = "";


   for (auto &i : decryptionMatrix)
   {
      for (auto j : i)
      {
         if (j != '_')
            decryptedText += j;
      }
   }


   return decryptedText;
}


int main()
{
   string plain;
   cout << "Enter the plain text: ";
   cin >> plain;


   int n = 5;
   // Encryption
   vector<vector<char>> matrix = initMatrix(plain, n);


   cout << endl
        << "Encryption:" << endl
        << endl
        << "Plain text to encryption matrix: " << endl;


   for (auto &i : matrix)
   {
      for (auto &j : i)
      {
         cout << j << " ";
      }
      cout << endl;
   }


   string cipherText = encryptedText(matrix, n);


   cout << endl
        << "Cipher Text: " << cipherText << endl;
   cout << endl
        << "-----------------------------------------------------" << endl;


   // Decryption
   vector<vector<char>> decryptionMatrix = cipherTextToDmatrix(cipherText, n);


   cout << endl
        << "Decryption:" << endl;
   cout << endl
        << "Cipher text to decryption matrix: " << endl;


   for (auto &i : decryptionMatrix)
   {
      for (auto &j : i)
      {
         cout << j << " ";
      }
      cout << endl;
   }


   string decryptedText = decryptionText(decryptionMatrix);


   cout << endl
        << "Decrypted Text: " << decryptedText << endl;


   return 0;
}
