#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> convertToBinary(int a, int b, int c, int d)
{
   vector<int> binIp;
   int octets[4] = {a, b, c, d};
   for (int i = 0; i < 4; ++i)
   {
      for (int j = 7; j >= 0; --j)
         binIp.push_back((octets[i] >> j) & 1);
   }
   return binIp;
}

void displayClassfulAddress(int a, int b, int c, int d)
{
   string ip = to_string(a) + "." + to_string(b) + "." + to_string(c) + "." + to_string(d);
   int firstOctet = a;
   string ipClass, defaultMask;

   if (firstOctet >= 1 && firstOctet <= 126)
   {
      ipClass = "A";
      defaultMask = "Default Mask: 255.0.0.0";
   }
   else if (firstOctet >= 128 && firstOctet <= 191)
   {
      ipClass = "B";
      defaultMask = "Default Mask: 255.255.0.0";
   }
   else if (firstOctet >= 192 && firstOctet <= 223)
   {
      ipClass = "C";
      defaultMask = "Default Mask: 255.255.255.0";
   }
   else if (firstOctet >= 224 && firstOctet <= 239)
   {
      ipClass = "D";
      defaultMask = "Reserved for Multicasting (Class D)";
   }
   else if (firstOctet >= 240 && firstOctet <= 255)
   {
      ipClass = "E";
      defaultMask = "Reserved for Research (Class E)";
   }
   else
   {
      ipClass = "Invalid";
      defaultMask = "Invalid";
   }

   cout << "IP: " << ip << "\nIP Class: " << ipClass << "\n"
        << defaultMask << endl;
}

void classlessAddressing(int a, int b, int c, int d, int cidrMask)
{
   string ip = to_string(a) + "." + to_string(b) + "." + to_string(c) + "." + to_string(d);
   int hostBits = 32 - cidrMask;
   int totalHosts = pow(2, hostBits) - 2;

   cout << "\nClassless Addressing\nIP: " << ip << "\nCIDR Mask: /" << cidrMask << endl;
   cout << "Total Hosts: " << totalHosts << endl;
}

void calculateNetworkAddress(int ip[], int mask, vector<int> &network)
{
   for (int i = 0; i < 4; ++i)
   {
      network[i] = ip[i] & (mask >> (i * 8) & 0xFF);
   }
}

void displaySubnetsWithLogic(int ip[], int n, int setBits)
{
   int num = 1;
   while (num < n)
      num *= 2;

   int bits = log2(num);
   int tot = (setBits + bits);
   int copy = 32 - tot;

   vector<int> subnet_mask(4);
   vector<int> network(4);

   for (int i = 0; i < 4; i++)
   {
      int a = 0;
      for (int j = 7; j >= 0; j--)
      {
         if (tot > 0)
         {
            a = (a | (1 << j));
            tot--;
         }
      }
      subnet_mask[i] = a;
   }

   calculateNetworkAddress(ip, subnet_mask[0] | (subnet_mask[1] << 8) | (subnet_mask[2] << 16) | (subnet_mask[3] << 24), network);

   cout << "The IP is: " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << endl;
   cout << "The Subnet Mask is: " << subnet_mask[0] << "." << subnet_mask[1] << "." << subnet_mask[2] << "." << subnet_mask[3] << endl;
   cout << "Network Address: " << network[0] << "." << network[1] << "." << network[2] << "." << network[3] << endl;

   int amount = pow(2, copy);
   cout << "\n";
   cout << "The number of addresses per subnet: " << amount << endl;

   cout << "The IP Addresses are: " << endl;

   for (int i = 0; i < num; i++)
   {
      cout << "\n";
      cout << "Block " << i + 1 << endl;
      cout << "Start: " << network[0] << "." << network[1] << "." << network[2] << "." << network[3] << endl;

      network[3] += amount - 1;

      for (int j = 3; j >= 1; j--)
      {
         while (network[j] > 255)
         {
            network[j] -= 256;
            network[j - 1] += 1;
         }
      }
      cout << "End: " << network[0] << "." << network[1] << "." << network[2] << "." << network[3] << endl;

      network[3]++;
      for (int j = 3; j >= 1; j--)
      {
         while (network[j] > 255)
         {
            network[j] -= 256;
            network[j - 1] += 1;
         }
      }
   }
}

int main()
{
   int choice, a, b, c, d, subnetCount, setBits;
   int ip[4];

   cout << "Enter the first octet (a): ";
   cin >> a;
   cout << "Enter the second octet (b): ";
   cin >> b;
   cout << "Enter the third octet (c): ";
   cin >> c;
   cout << "Enter the fourth octet (d): ";
   cin >> d;

   ip[0] = a;
   ip[1] = b;
   ip[2] = c;
   ip[3] = d;

   while (true)
   {
      cout << "Choose addressing method:\n";
      cout << "1. Classful Addressing\n";
      cout << "2. Classless Addressing (CIDR)\n";
      cout << "3. Subnetting\n";
      cout << "4. Exit\n";
      cout << "Enter your choice: ";
      cout << "\n";
      cin >> choice;

      switch (choice)
      {
      case 1:
         displayClassfulAddress(a, b, c, d);
         cout << "\n";
         break;
      case 2:
         cout << "Enter CIDR mask: ";
         cin >> setBits;
         classlessAddressing(a, b, c, d, setBits);
         cout << "\n";
         break;
      case 3:
         cout << "\n";
         cout << "Enter number of subnets: ";
         cin >> subnetCount;
         cout << "Enter number of set bits for subnet mask: ";
         cin >> setBits;
         cout << "\n";
         displaySubnetsWithLogic(ip, subnetCount, setBits);
         cout << "\n";
         break;
      case 4:
         cout << "Exiting program." << endl;
         return 0;
      default:
         cout << "Invalid choice." << endl;
         break;
      }
   }

   return 0;
}
