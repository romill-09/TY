#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> graph;
set<string> visited;
unordered_map<string, string> parent;

vector<string> cities = {"Arad", "Zerind", "Oradea", "Sibiu", "Timisoara", "Lugoj", "Mehadia", "Drobeta", "Craiova", "Rimnicu Vilcea", "Fagaras", "Pitesti", "Bucharest", "Giurgiu", "Urziceni", "Hirsova", "Eforie", "Vaslui", "Lasi", "Neamt"};

void addEdge(const string &city1, const string &city2)
{
    graph[city1].push_back(city2);
    graph[city2].push_back(city1);
}

void printPath(const string &start, const string &goal)
{
    vector<string> path;
    string current = goal;

    while (current != start && parent.find(current) != parent.end())
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
    cout << endl;
}

bool dfs(const string &current, const string &start, const string &goal)
{
    cout << "Visiting: " << current << endl;

    if (current == goal)
    {
        cout << endl << "Goal found!" << endl << "Path: " ;
        printPath(start, goal);
        return true;
    }

    visited.insert(current);

    for (const string &neighbor : graph[current])
    {
        if (visited.find(neighbor) == visited.end())
        {
            parent[neighbor] = current;
            if (dfs(neighbor, start, goal))
                return true;
        }
    }

    return false;
}

int main()
{
    addEdge("Arad", "Zerind");
    addEdge("Arad", "Timisoara");
    addEdge("Arad", "Sibiu");
    addEdge("Zerind", "Oradea");
    addEdge("Oradea", "Sibiu");
    addEdge("Sibiu", "Fagaras");
    addEdge("Sibiu", "Rimnicu Vilcea");
    addEdge("Rimnicu Vilcea", "Pitesti");
    addEdge("Rimnicu Vilcea", "Craiova");
    addEdge("Craiova", "Drobeta");
    addEdge("Drobeta", "Mehadia");
    addEdge("Mehadia", "Lugoj");
    addEdge("Lugoj", "Timisoara");
    addEdge("Fagaras", "Bucharest");
    addEdge("Pitesti", "Bucharest");
    addEdge("Bucharest", "Giurgiu");
    addEdge("Bucharest", "Urziceni");
    addEdge("Urziceni", "Vaslui");
    addEdge("Urziceni", "Hirsova");
    addEdge("Hirsova", "Eforie");
    addEdge("Vaslui", "Lasi");
    addEdge("Lasi", "Neamt");

    cout << "Edges in the Map of Romania: " << endl << endl;
    for (auto &city : graph)
    {
        cout << city.first << " -> ";
        for (string &neighbour : city.second)
        {
            cout << neighbour << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Enter the start state: ";
    string start;
    cin >> start;

    cout << "Enter the goal state: ";
    string goal;
    cin >> goal;

    cout << endl;
    int exists = -1;
    for (int i = 0; i < cities.size(); ++i)
    {
        if (cities[i] == start)
            exists++;
        if (cities[i] == goal)
            exists++;
    }

    if (!exists)
    {
        cout << "Start or Goal state not found!";
        return 0;
    }

    vector<bool> visited(30, false);

    if (!dfs(start, start, goal))
    {
        cout << "Goal not reachable from start." << endl;
    }

    return 0;
}
