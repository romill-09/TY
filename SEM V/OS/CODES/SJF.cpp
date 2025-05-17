#include <bits/stdc++.h>

using namespace std;

void sjf(vector<pair<int, int>> &processes, vector<int> &arrival)
{
   int completion = 0;
   int n = processes.size();

   vector<int> turnAround(n), waitingTime(n);
   vector<bool> isCompleted(n, false);

   cout << "Process Completion time:" << endl;

   for (int i = 0; i < n; ++i)
   {
      int idx = -1;
      int minBurst = INT_MAX;

      // Find the process with the shortest burst time that has arrived
      for (int j = 0; j < n; ++j)
      {
         if (!isCompleted[j] && arrival[j] <= completion && processes[j].second < minBurst)
         {
            minBurst = processes[j].second;
            idx = j;
         }
      }

      // If no process has arrived yet, move completion to the arrival time of the next process
      if (idx == -1)
      {
         int earliestArrival = INT_MAX;
         for (int j = 0; j < n; ++j)
         {
            if (!isCompleted[j] && arrival[j] < earliestArrival)
            {
               earliestArrival = arrival[j];
               idx = j;
            }
         }
         completion = arrival[idx]; // Update completion to the earliest arrival time
      }

      // Process the selected process
      completion += processes[idx].second;
      cout << "P" << processes[idx].first << ": " << completion << endl;

      turnAround[idx] = completion - arrival[idx];
      waitingTime[idx] = turnAround[idx] - processes[idx].second;
      isCompleted[idx] = true;
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
   cout << "Shortest Job First (SJF) Scheduling Algorithm" << endl;
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
      sjf(processes, arrivalTimes);
      break;

   case 1:
      cout << "Enter the arrival time for each process: " << endl;
      for (int i = 0; i < n; i++)
         cin >> arrivalTimes[i];
      cout << endl;
      sjf(processes, arrivalTimes);
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