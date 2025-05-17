#include <bits/stdc++.h>
using namespace std;

void priority(int n, vector<int> arrival_times, vector<int> burst_times)
{
    priority_queue<pair<int, int>> pq;
    vector<int> completion_times(n), gantt;
    int time = 0, completed = 0;

    vector<int> priority(n);
    cout << "Enter the priority of the processes (Largest Number First): ";
    for (auto &i : priority) 
        cin >> i;

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
            if (arrival_times[i] == time)
                pq.push({priority[i], i});

        auto x = pq.top();
        pq.pop();
        burst_times[x.second]--;
        gantt.push_back(x.second);

        if (burst_times[x.second] == 0)
        {
            completion_times[x.second] = time + 1;
            completed++;
        }
        else
            pq.push(x);

        time++;
    }

    vector<int> turnaround_times(n), waiting_times(n);
    for (int i = 0; i < n; i++)
    {
        turnaround_times[i] = completion_times[i] - arrival_times[i];
        waiting_times[i] = turnaround_times[i] - burst_times[i];
    }

    int avt = accumulate(turnaround_times.begin(), turnaround_times.end(), 0);
    int avw = accumulate(waiting_times.begin(), waiting_times.end(), 0);

    vector<int> p, t;
    for (int i = 0; i < gantt.size(); i++)
    {
        if (i == 0 || gantt[i] != gantt[i - 1])
        {
            p.push_back(gantt[i]);
            t.push_back(i);
        }
    }
    t.push_back(time);

    cout << "Completion Times: ";
    for (auto &i : completion_times)
        cout << i << " ";
    cout << "\nTurnaround Times: ";
    for (auto &i : turnaround_times)
        cout << i << " ";
    cout << "\nWaiting Times: ";
    for (auto &i : waiting_times)
        cout << i << " ";

    cout << "\nAvg. Turnaround Time: " << (float)avt / n;
    cout << "\nAvg. Waiting Time: " << (float)avw / n;

    cout << "\nGantt Chart\n";
    for (auto &i : p)
        cout << " P" << i + 1;
    cout << "\n";
    for (auto &i : t)
        cout << i << "  ";
    cout << "\n";
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<int> burst_times(n);
    vector<int> arrival_times(n);

    cout << "Enter the arrival times: ";
    for (auto &i : arrival_times)
        cin >> i;

    cout << "Enter the burst times: ";
    for (auto &i : burst_times)
        cin >> i;

    priority(n, arrival_times, burst_times);
}
