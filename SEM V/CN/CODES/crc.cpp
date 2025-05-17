#include <iostream>
#include <string>
using namespace std;

string appendRedBits(const string &data, int g_size)
{
   return data + string(g_size - 1, '0');
}

string xor1(const string &dividend, const string &g)
{
   string result;
   for (int i = 0; i < g.size(); ++i)
   {
      result += (dividend[i] == g[i]) ? '0' : '1';
   }
   return result;
}

string findSyndrome(string dividend, const string &g)
{
   int g_size = g.size();

   for (int i = 0; i <= dividend.size() - g_size; ++i)
   {
      if (dividend[i] == '1')
      {
         string part = dividend.substr(i, g_size);
         string res = xor1(part, g);
         dividend.replace(i, g_size, res);
      }
   }
   return dividend.substr(dividend.size() - g_size + 1);
}

string crc(const string &data, const string &g)
{
   int g_size = g.size();

   string dividend = appendRedBits(data, g_size);
   cout << "Initial Codeword: " << dividend << endl;

   string syndrome = findSyndrome(dividend, g);
   cout << "Remainder: " << syndrome << endl;

   return data + syndrome;
}

string introduceError(string c, int a)
{
   if (a < 1 || a > c.size())
   {
      cerr << "Index out of bounds!" << endl;
      return c;
   }

   c[a - 1] = (c[a - 1] == '1') ? '0' : '1';
   return c;
}

void checkError(const string &codeword, const string &generator)
{
   cout << "Do you want to introduce an error and check (enter 1) or not (enter -1): ";
   int input, a;
   cin >> input;
   string errorcode = codeword;
   string rem = "";

   switch (input)
   {
   case -1:
      cout << "No Error" << endl;
      cout << "Dataword: " + codeword.substr(0, codeword.size() - generator.size() + 1) << endl;
      break;

   case 1:
      cout << "Enter the index (1-based) to make the codeword erroneous: ";
      cin >> a;

      errorcode = introduceError(errorcode, a);
      rem = findSyndrome(errorcode, generator);

      if (rem.find('1') != string::npos)
      {
         cout << "Codeword with error: " << errorcode << endl;
         cout << "Remainder: " << rem << endl;
         cout << "Error Detected!" << endl;
      }
      else
      {
         cout << "No Error" << endl;
      }
      break;

   default:
      cout << "Invalid input!" << endl;
      break;
   }
}

int main()
{
   string dataWord, generator;
   cout << "Enter the dataword and generator in binary (without spaces): " << "\n";
   cin >> dataWord >> generator;

   if (generator.find_first_not_of("01") != string::npos)
   {
      cout << "Generator must be in binary format!" << endl;
      return 1;
   }

   if (dataWord.find_first_not_of("01") != string::npos)
   {
      cout << "Dataword must be in binary format!" << endl;
      return 1;
   }

   string codeword = crc(dataWord, generator);
   cout << "Sender's Codeword: " << codeword << endl;

   checkError(codeword, generator);
   return 0;
}