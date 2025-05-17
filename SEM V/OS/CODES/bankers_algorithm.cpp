#include <iostream>
#include <vector>
using namespace std;

int numProcesses, numResources;
vector<vector<int>> maxResources, allocation, need;
vector<int> available;

void inputMatrix(vector<vector<int>>& matrix, const string& name) {
    cout << "Enter the " << name << " matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> matrix[i][j];
        }
    }
}

void calculateNeedMatrix() {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maxResources[i][j] - allocation[i][j];
        }
    }
}

void printNeedMatrix() {
    cout << "Need Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
}

void printAllocationMatrix() {
    cout << "Allocation Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cout << allocation[i][j] << " ";
        }
        cout << endl;
    }
}

void printAvailableResources() {
    cout << "Available Resources:\n";
    for (int i = 0; i < numResources; i++) {
        cout << available[i] << " ";
    }
    cout << endl;
}

bool canAllocate(int process) {
    for (int j = 0; j < numResources; j++) {
        if (need[process][j] > available[j]) {
            return false;
        }
    }
    return true;
}

void requestResources(int process, const vector<int>& request) {
    for (int j = 0; j < numResources; j++) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }
}

// void releaseResources(int process) {
//     for (int j = 0; j < numResources; j++) {
//         available[j] += allocation[process][j];
//     }
// }

bool isSafeState() {
    vector<bool> completed(numProcesses, false);
    int count = 0;

    while (count < numProcesses) {
        bool foundProcess = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!completed[i] && canAllocate(i)) {
                releaseResources(i);
                completed[i] = true;
                count++;
                foundProcess = true;
            }
        }
        if (!foundProcess) {
            return false;
        }
    }
    return true;
}

void handleResourceRequest() {
    int processID;
    cout << "Enter process ID to request resources (or -1 to skip): ";
    cin >> processID;

    if (processID != -1) {
        vector<int> request(numResources);
        cout << "Enter request vector:\n";
        for (int i = 0; i < numResources; i++) {
            cin >> request[i];
        }

        bool validRequest = true;
        for (int i = 0; i < numResources; i++) {
            if (request[i] > need[processID][i] || request[i] > available[i]) {
                validRequest = false;
                break;
            }
        }

        if (validRequest) {
            requestResources(processID, request);
            if (isSafeState()) {
                cout << "Request granted, system is in a safe state.\n";
                printNeedMatrix();
                printAllocationMatrix();
                printAvailableResources();
            } else {
                cout << "Request denied, leads to unsafe state.\n";
            }
        } else {
            cout << "Invalid request, exceeds available or needed resources.\n";
        }
    }
}

int main() {
    cout << "Enter number of processes: ";
    cin >> numProcesses;
    cout << "Enter number of resources: ";
    cin >> numResources;

    maxResources.resize(numProcesses, vector<int>(numResources));
    allocation.resize(numProcesses, vector<int>(numResources));
    need.resize(numProcesses, vector<int>(numResources));
    available.resize(numResources);

    inputMatrix(maxResources, "Maximum Resources");
    inputMatrix(allocation, "Allocation");

    calculateNeedMatrix();
    printNeedMatrix();

    cout << "Enter available resources:\n";
    for (int i = 0; i < numResources; i++) {
        cin >> available[i];
    }

    handleResourceRequest();

    if (isSafeState()) {
        cout << "System is in a safe state.\n";
    } else {
        cout << "System is in an unsafe state.\n";
    }

    return 0;
}
