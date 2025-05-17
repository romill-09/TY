#include <bits/stdc++.h>
using namespace std;

vector<string> packets;

string stringToBinary(const string &dw)
{
   string binaryWord = "";
   for (char c : dw)
   {
      binaryWord += bitset<8>(c).to_string();
   }
   return binaryWord;
}

string addRedBits(string bdw)
{
   string redBits = "00000000";
   bdw += redBits;
   return bdw;
}

vector<string> formPackets(string &bdw, const string &dw)
{
   int noOfChars = dw.length();
   if (noOfChars & 1)
      bdw = addRedBits(bdw);

   int noOfPackets = ceil(bdw.length() / 16.0);
   for (int i = 0; i < noOfPackets; i++)
   {
      string packet = bdw.substr(i * 16, 16);
      packets.push_back(packet);
   }
   return packets;
}

string addingBinaryPackets(string a, string b)
{
   string ans = "";
   char carry = '0';

   for (int i = 15; i >= 0; --i)
   {
      char sum = a[i] ^ b[i] ^ carry;
      ans = sum + ans;
      carry = (a[i] & b[i]) | (a[i] & carry) | (b[i] & carry);
   }

   if (carry == '1')
      ans = carry + ans;
   return ans;
}

string addPackets(vector<string> &packets)
{
   string result = packets[0];
   for (int i = 1; i < packets.size(); i++)
   {
      result = addingBinaryPackets(result, packets[i]);
   }
   for (char &c : result)
      c = (c == '1') ? '0' : '1';
   return result;
}

string checkSum(const string &dataWord)
{
   string binaryDataWord;

   binaryDataWord = stringToBinary(dataWord);

   vector<string> packets = formPackets(binaryDataWord, dataWord);

   cout << "The transmitted data is: " + binaryDataWord << endl;

   return addPackets(packets);
}

string checkError(const string &checksum)
{
   string result = packets[0];
   for (int i = 1; i < packets.size(); i++)
   {
      result = addingBinaryPackets(result, packets[i]);
   }

   result = addingBinaryPackets(result, checksum);

   for (char &c : result)
      c = (c == '1') ? '0' : '1';

   return result;
}

int main()
{
   string dataWord;
   cout << "Enter the dataword input (text) without any spaces: " << endl;
   cin >> dataWord;

   string checksum = checkSum(dataWord);
   cout << "Checksum: " << checksum << endl;

   string errorCode = checkError(checksum);

   if (errorCode == "0000000000000000")
      cout << "No error in transmission, result after complement is " + errorCode << endl;
   else
      cout << "Error in transmission detected, erroneous code is " + errorCode << endl;

   return 0;
}
