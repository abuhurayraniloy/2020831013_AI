#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Depth-Limited Search
bool DLS(const vector<vector<int>> &graph, int start, int target, int depth)
{
    if (start == target)
        return true;

    if (depth <= 0) // modification in dfs (adding limit)
        return false;

    for (int neighbor : graph[start])
    {
        if (DLS(graph, neighbor, target, depth - 1))
            return true;
    }

    return false;
}

// Main function for testing
int main()
{
    // Example graph represented as an adjacency list
    vector<vector<int>> graph = {
        {1, 2},    // Node 0 is connected to nodes 1 and 2
        {3},       // Node 1 is connected to node 3
        {1, 3, 4}, // Node 2 is connected to nodes 1, 3, and 4
        {4},       // Node 3 is connected to node 4
        {}         // Node 4 has no outgoing edges
    };

    int start = 0;      // Starting node
    int target = 4;     // Target node
    int depthLimit = 1; // Depth limit

    if (DLS(graph, start, target, depthLimit))
        cout << "Target is reachable within depth limit." << endl;
    else
        cout << "Target is not reachable within depth limit." << endl;

    return 0;
}
