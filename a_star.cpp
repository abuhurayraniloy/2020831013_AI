#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string, int>>> graph; // node1 - node2 - cost
map<string, int> heuristic;

map<string, bool> vis;
map<string, int> dist;

map<string, string> parentNode;
vector<string> path;

void printPath(string node)
{
    path.push_back(node);
    if (parentNode[node] == node)
        return;
    printPath(parentNode[node]);
}

void aStarSearch(string source, string destination)
{
    multiset<pair<int, string>> st; // dist - nodeName

    st.insert(make_pair(heuristic[source], source));
    dist[source] = heuristic[source];
    parentNode[source] = source;

    while (!st.empty())
    {
        auto node = *st.begin();
        string parent = node.second;
        int cost = node.first;
        st.erase(st.begin());
        if (vis[parent])
            continue;
        vis[parent] = true;
        if (parent == destination)
            break;
        for (auto child : graph[parent])
        {
            string childName = child.first;
            int pathCost = child.second;
            int tempCost = cost - heuristic[parent] + pathCost + heuristic[childName];
            // dist[childName] = min(dist[childName],tempCost);
            if (tempCost < dist[childName])
            {
                parentNode[childName] = parent;
                dist[childName] = tempCost;
            }
            st.insert(make_pair(dist[childName], childName));
        }
    }
}

int main()
{
    int nodes, edges;
    cin >> nodes >> edges; // number of node and edges
    while (edges--)
    { // graph input
        string node1, node2;
        int cost;
        cin >> node1 >> node2 >> cost;
        graph[node1].push_back(make_pair(node2, cost));
        graph[node2].push_back(make_pair(node1, cost));
    }

    while (nodes--)
    { // huristic array
        string str;
        int hu;
        cin >> str >> hu;
        heuristic[str] = hu;
        vis[str] = false;
        dist[str] = INT_MAX;
    }

    string source, destination;
    cin >> source >> destination;
    aStarSearch(source, destination);
    cout << "The path cost is :: " << dist[destination] << endl;
    printPath(destination);
    cout << "And the path is :: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i];
        if (i != 0)
            cout << " -> ";
    }
    cout << endl;
    return 0;
}