#include <iostream>
#include <vector>

using namespace std;

bool canAllocateResources(int process, vector<vector<int>>& needMatrix, vector<int>& availableResources) {
    for (int resource = 0; resource < needMatrix[0].size(); resource++) {
        if (needMatrix[process][resource] > availableResources[resource]) {
            return false;
        }
    }
    return true;
}

void inputMatrix(int numProcesses, int numResources, vector<vector<int>>& matrix, const string& name) {
    cout << "Enter the " << name << " matrix:\n";
    for (int process = 0; process < numProcesses; process++) {
        for (int resource = 0; resource < numResources; resource++) {
            cin >> matrix[process][resource];
        }
    }
}

void printMatrix(int numProcesses, int numResources, vector<vector<int>>& matrix, const string& name) {
    cout << name << " matrix:\n";
    for (int process = 0; process < numProcesses; process++) {
        for (int resource = 0; resource < numResources; resource++) {
            cout << matrix[process][resource] << " ";
        }
        cout << endl;
    }
}

void handleResourceRequest(int numResources, vector<vector<int>>& allocationMatrix, vector<vector<int>>& needMatrix, vector<int>& availableResources) {
    int processID;
    cout << "Enter resource request process number (0 indexed) or -1 if none: ";
    cin >> processID;

    if (processID != -1) {
        vector<int> request(numResources);
        cout << "Enter the request for resources: ";
        for (int resource = 0; resource < numResources; resource++) {
            cin >> request[resource];
        }

        for (int resource = 0; resource < numResources; resource++) {
            if (availableResources[resource] < request[resource]) {
                cout << "Resource " << resource << " is not enough" << endl;
                return;
            }
            if (needMatrix[processID][resource] < request[resource]) {
                cout << "Need for resource " << resource << " is lower than request" << endl;
                return;
            }
        }

        cout << "Request is valid and granted" << endl;
        for (int resource = 0; resource < numResources; resource++) {
            availableResources[resource] -= request[resource];
            allocationMatrix[processID][resource] += request[resource];
            needMatrix[processID][resource] -= request[resource];
        }

        printMatrix(allocationMatrix.size(), numResources, needMatrix, "Updated Need");
        printMatrix(allocationMatrix.size(), numResources, allocationMatrix, "Updated Allocation");

        cout << "Updated Available Resources: ";
        for (int resource = 0; resource < numResources; resource++) {
            cout << availableResources[resource] << " ";
        }
        cout << endl;
    }
}

bool isSafeState(int numProcesses, int numResources, vector<vector<int>>& allocationMatrix, vector<vector<int>>& needMatrix, vector<int>& availableResources) {
    vector<bool> completed(numProcesses, false);
    int completedCount = 0;

    while (completedCount != numProcesses) {
        bool found = false;
        for (int process = 0; process < numProcesses; process++) {
            if (!completed[process] && canAllocateResources(process, needMatrix, availableResources)) {
                completedCount++;
                cout << "P" << process << " ";
                for (int resource = 0; resource < numResources; resource++) {
                    availableResources[resource] += allocationMatrix[process][resource];
                }
                completed[process] = true;
                found = true;
            }
        }
        if (!found) {
            cout << "System is not in a safe state." << endl;
            return false;
        }
    }
    cout << endl << "System is in a safe state." << endl;
    return true;
}

int main() {
    int numProcesses, numResources;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> allocationMatrix(numProcesses, vector<int>(numResources));
    vector<vector<int>> maxMatrix(numProcesses, vector<int>(numResources));
    vector<vector<int>> needMatrix(numProcesses, vector<int>(numResources));
    vector<int> availableResources(numResources);

    inputMatrix(numProcesses, numResources, allocationMatrix, "Allocation");
    inputMatrix(numProcesses, numResources, maxMatrix, "Maximum");

    for (int process = 0; process < numProcesses; process++) {
        for (int resource = 0; resource < numResources; resource++) {
            needMatrix[process][resource] = maxMatrix[process][resource] - allocationMatrix[process][resource];
        }
    }

    printMatrix(numProcesses, numResources, needMatrix, "Need");

    cout << "Enter the available resources: ";
    for (int resource = 0; resource < numResources; resource++) {
        cin >> availableResources[resource];
    }

    handleResourceRequest(numResources, allocationMatrix, needMatrix, availableResources);

    isSafeState(numProcesses, numResources, allocationMatrix, needMatrix, availableResources);

    return 0;
}

