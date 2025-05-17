# include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<pair<string, int>>> graph;
unordered_map<string, int> heuristic;
unordered_map<string, string> parent;
unordered_map<string, int> costSoFar;

void addEdge(const string &city1, const string &city2, int cost)
{
    graph[city1].push_back({city2, cost});
    graph[city2].push_back({city1, cost});
}

void printPath(const string &start, const string &goal, int totalCost)
{
    vector<string> path;
    string current = goal;
    while (current != start)
    {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    for (const string &city : path)
    {
        cout << city << " ";
    }
    cout << "\nTotal cost: " << totalCost << endl;
}

struct Compare
{
    bool operator()(const pair<string, int> &a, const pair<string, int> &b)
    {
        return a.second > b.second;
    }
};

void greedyBFS(const string &start, const string &goal)
{
    priority_queue<pair<string, int>, vector<pair<string, int>>, Compare> pq;
    pq.push({start, heuristic[start]});
    costSoFar[start] = 0;
    
    while (!pq.empty())
    {
        string current = pq.top().first;
        cout << "Visiting: " << current << " with heuristic: " << heuristic[current] << endl;
        pq.pop();
        
        if (current == goal)
        {
            cout << "\nPath found: ";
            printPath(start, goal, costSoFar[goal]);
            return;
        }
        
        int minCost = INT_MAX;
        string nextNode;
        for (auto &neighbor : graph[current])
        {
            string nextCity = neighbor.first;
            int newCost = costSoFar[current] + neighbor.second;
            
            if (parent.find(nextCity) == parent.end())
            {
                costSoFar[nextCity] = newCost;
                pq.push({nextCity, heuristic[nextCity]});
                parent[nextCity] = current;
                
                if (heuristic[nextCity] < minCost)
                {
                    minCost = heuristic[nextCity];
                    nextNode = nextCity;
                }
            }
        }
        if (!nextNode.empty())
            cout << "Minimum heuristic cost node chosen: " << nextNode << " with cost: " << minCost << endl;
        cout << endl;
    }
    cout << "\nGoal not reachable from start." << endl;
}

int main()
{
    addEdge("Arad", "Zerind", 75);
    addEdge("Arad", "Timisoara", 118);
    addEdge("Arad", "Sibiu", 140);
    addEdge("Zerind", "Oradea", 71);
    addEdge("Oradea", "Sibiu", 151);
    addEdge("Sibiu", "Fagaras", 99);
    addEdge("Sibiu", "Rimnicu Vilcea", 80);
    addEdge("Rimnicu Vilcea", "Pitesti", 97);
    addEdge("Rimnicu Vilcea", "Craiova", 146);
    addEdge("Craiova", "Drobeta", 120);
    addEdge("Drobeta", "Mehadia", 75);
    addEdge("Mehadia", "Lugoj", 70);
    addEdge("Lugoj", "Timisoara", 111);
    addEdge("Fagaras", "Bucharest", 211);
    addEdge("Pitesti", "Bucharest", 101);
    addEdge("Bucharest", "Giurgiu", 90);
    addEdge("Bucharest", "Urziceni", 85);
    addEdge("Urziceni", "Vaslui", 142);
    addEdge("Urziceni", "Hirsova", 98);
    addEdge("Hirsova", "Eforie", 86);
    addEdge("Vaslui", "Lasi", 92);
    addEdge("Lasi", "Neamt", 87);

    heuristic["Arad"] = 366;
    heuristic["Bucharest"] = 0;
    heuristic["Craiova"] = 160;
    heuristic["Drobeta"] = 242;
    heuristic["Eforie"] = 161;
    heuristic["Fagaras"] = 178;
    heuristic["Giurgiu"] = 77;
    heuristic["Hirsova"] = 151;
    heuristic["Lasi"] = 226;
    heuristic["Lugoj"] = 244;
    heuristic["Mehadia"] = 241;
    heuristic["Neamt"] = 234;
    heuristic["Oradea"] = 380;
    heuristic["Pitesti"] = 98;
    heuristic["Rimnicu Vilcea"] = 193;
    heuristic["Sibiu"] = 253;
    heuristic["Timisoara"] = 329;
    heuristic["Urziceni"] = 80;
    heuristic["Vaslui"] = 199;
    heuristic["Zerind"] = 374;

    cout << "Edges in the Map of Romania: " << endl << endl;
    for (auto &city : graph)
    {
        cout << city.first << " -> ";
        for (auto &neighbour : city.second)
        {
            cout << "(" << neighbour.first << ", " << neighbour.second << ") ";
        }
        cout << endl;
    }
    cout << endl;

    string start, goal;
    cout << "Enter the start city: ";
    cin >> start;
    cout << "Enter the goal city: ";
    cin >> goal;
    
    cout << endl;
    if (graph.find(start) == graph.end() || graph.find(goal) == graph.end())
    {
        cout << "Start or Goal state not found!" << endl;
        return 0;
    }
    
    cout << endl;
    greedyBFS(start, goal);
    return 0;
}
