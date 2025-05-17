#include <bits/stdc++.h>
using namespace std;

vector<int> lookSeq(const vector<int> &reqSeq, int head, string direction)
{
    vector<int> seek;
    vector<int> sortedSeq = reqSeq;
    sort(sortedSeq.begin(), sortedSeq.end());
    auto it = lower_bound(sortedSeq.begin(), sortedSeq.end(), head);
    int index = distance(sortedSeq.begin(), it);

    if (direction == "right")
        {
        for (int i = index; i < sortedSeq.size(); ++i)
        {
            seek.push_back(sortedSeq[i]);
        }
        for (int i = index - 1; i >= 0; --i)
        {
            seek.push_back(sortedSeq[i]);
        }
    } else if (direction == "left")
    {
        for (int i = index - 1; i >= 0; --i)
        {
            seek.push_back(sortedSeq[i]);
        }
        for (int i = index; i < sortedSeq.size(); ++i)
        {
            seek.push_back(sortedSeq[i]);
        }
    }

    return seek;
}

vector<int> fcfsSeq(const vector<int> &reqSeq, int head)
{
    vector<int> seek;
    for (int request : reqSeq)
    {
        seek.push_back(request);
    }
    return seek;
}

int calculateSeekTime(const vector<int> &seek, int head)
{
    int seekTime = abs(seek[0] - head);
    for (int i = 1; i < seek.size(); ++i)
    {
        seekTime += abs(seek[i] - seek[i - 1]);
    }
    return seekTime;
}

void displaySeq(const vector<int> &a)
{
    for (int i : a)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    while (true)
    {
        cout << "Choose scheduling algorithm:\n";
        cout << "1. LOOK\n";
        cout << "2. FCFS\n";
        cout << "3. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 3)
        {
            break;
        }

        cout << "Enter the number of blocks: ";
        int n;
        cin >> n;

        cout << "Please enter the request sequence:\n";
        vector<int> reqSeq(n);
        for (auto &i : reqSeq) cin >> i;

        cout << "Enter the head position: ";
        int head;
        cin >> head;

        if (choice == 1)
        {
            cout << "Enter the direction in which the head should move initially (left/right): ";
            string direction;
            cin >> direction;

            vector<int> seekOrder = lookSeq(reqSeq, head, direction);
            cout << "Seek sequence: ";
            displaySeq(seekOrder);

            int totalSeekTime = calculateSeekTime(seekOrder, head);
            cout << "Total seek time: " << totalSeekTime << endl;
        }
        else if (choice == 2)
        {
            vector<int> seekOrder = fcfsSeq(reqSeq, head);
            cout << "Seek sequence: ";
            displaySeq(seekOrder);

            int totalSeekTime = calculateSeekTime(seekOrder, head);
            cout << "Total seek time: " << totalSeekTime << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
