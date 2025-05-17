#include <bits/stdc++.h>

using namespace std;

void fcfs(vector<pair<int, int>> &processes, vector<int> &arrival)
{
   int completion = 0;
   int n = processes.size();

   vector<int> turnAround(n), waitingTime(n);

   cout << "Process Completion time:" << endl;
   for (int i = 0; i < n; ++i)
   {
      if (completion < arrival[i])
      {
         completion = arrival[i];
      }

      completion += processes[i].second;
      cout << "P" << processes[i].first << ": " << completion << endl;

      turnAround[i] = completion - arrival[i];
      waitingTime[i] = turnAround[i] - processes[i].second;
   }

   cout << endl
        << "Turn Around Time: " << endl;
   for (int i = 0; i < n; ++i)
   {
      cout << "P" << processes[i].first << ": " << turnAround[i] << endl;
   }

   cout << endl
        << "Waiting Time: " << endl;
   for (int i = 0; i < n; ++i)
   {
      cout << "P" << processes[i].first << ": " << waitingTime[i] << endl;
   }

   cout << endl;

   cout << "Average turn around time = " << (float)accumulate(turnAround.begin(), turnAround.end(), 0) / n << " ms" << endl;
   cout << "Average waiting time = " << (float)accumulate(waitingTime.begin(), waitingTime.end(), 0) / n << " ms" << endl;
}

void input()
{
   cout << "First Come First Serve (FCFS) Scheduling Algorithm" << endl;
   cout << "Enter the number of processes: ";
   int n;
   cin >> n;

   vector<pair<int, int>> processes(n); // Process ID and Burst
   cout << "Enter process ID and Burst time for each process: " << endl;

   for (int i = 0; i < n; i++)
   {
      cin >> processes[i].first >> processes[i].second;
   }

   cout << endl;
   
   int choice;
   cout << "Does all the processes arrive at same time (enter 0) else (enter 1)" << endl;
   cin >> choice;
   cout << endl;

   vector<int> arrivalTimes(n);

   switch (choice)
   {
   case 0:
      cout << "Enter the arrival time processes: " << endl;
      int x;
      cin >> x;
      for (int i = 0; i < n; ++i)
         arrivalTimes[i] = x;
      fcfs(processes, arrivalTimes);
      break;

   case 1:
      cout << "Enter the arrival time for each process: " << endl;
      for (int i = 0; i < n; i++)
         cin >> arrivalTimes[i];
      cout << endl;
      fcfs(processes, arrivalTimes);
      break;

   default:
      cout << "Invalid choice. Please try again." << endl;
      return;
   }
}

int main()
{
   input();
   return 0;
}