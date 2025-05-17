#include <bits/stdc++.h>
using namespace std;


// Function to create the Columnar Matrix for encryption
vector<vector<char>> initMatrix(const string &plain, string &keyword)
{
   int index = 0;
   int p = plain.size();
   int k = keyword.size();
   int n = (p + k - 1) / k;


   vector<vector<char>> v(n, vector<char>(k, '_'));


   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < k; ++j)
      {
         if (index < p)
            v[i][j] = plain[index++];
      }
   }
   return v;
}


vector<pair<char, int>> indices(string &keyword, bool decrypt)
{
   vector<pair<char, int>> v;
   for (int i = 0; i < keyword.size(); ++i)
   {


      v.push_back({keyword[i], i});
   }


   sort(v.begin(), v.end(), [](const pair<char, int> &a, const pair<char, int> &b)
        { return a.first < b.first; });


   return v;
}


vector<vector<char>> rearrange(const vector<pair<char, int>> &indx, vector<vector<char>> &matrix, bool decrypt)
{
   int row = matrix.size();
   int col = matrix[0].size();


   vector<vector<char>> rearranged(row, vector<char>(col, '_'));


   for (int c = 0; c < col; ++c)
   {
      int sortedIndex = indx[c].second;
      for (int r = 0; r < row; ++r)
      {
         if (!decrypt)
         {
            rearranged[r][c] = matrix[r][sortedIndex];
         }
         else
         {
            rearranged[r][sortedIndex] = matrix[r][c];
         }
      }
   }


   return rearranged;
}


string encryptedText(vector<vector<char>> &matrix)
{
   string cipherText = "";


   for (auto &i : matrix)
   {
      for (auto &j : i)
      {
         cipherText += j;
      }
   }


   return cipherText;
}


vector<vector<char>> cipherTextToDmatrix(string &cipherText, string &keyword)
{
   int index = 0;
   int k = keyword.size();
   int c = cipherText.size();
   int n = (c + k - 1) / k;


   vector<vector<char>> v(n, vector<char>(k, '_'));


   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < k; ++j)
      {
         if (index < c)
            v[i][j] = cipherText[index++];
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


   string keyword;
   cout << "Enter the keyword: ";
   cin >> keyword;


   // Encryption
   vector<vector<char>> matrix = initMatrix(plain, keyword);


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


   bool decrypt = false;
   vector<pair<char, int>> indx = indices(keyword, decrypt);


   matrix = rearrange(indx, matrix, decrypt);


   cout << endl
        << "Rearranged encryption matrix: " << endl;


   for (auto &i : matrix)
   {
      for (auto &j : i)
      {
         cout << j << " ";
      }
      cout << endl;
   }


   string cipherText = encryptedText(matrix);


   cout << endl
        << "Cipher Text: " << cipherText << endl;
   cout << endl
        << "-----------------------------------------------------" << endl;
   // Decryption
   vector<vector<char>> decryptionMatrix = cipherTextToDmatrix(cipherText, keyword);


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


   decrypt = true;
   decryptionMatrix = rearrange(indx, decryptionMatrix, decrypt);


   cout << endl
        << "Rearranged decryption matrix: " << endl;
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
