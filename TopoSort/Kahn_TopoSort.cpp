#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;
using std::queue;

vector<int> Kahn_TopoSort (const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<int> in_degree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            in_degree[v]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> topo_order;
    while (!q.empty()) {
        int cur_node = q.front();
        q.pop();
        topo_order.push_back(cur_node);
        for (int node : adj[cur_node]) {
            in_degree[node]--;
            if (in_degree[node] == 0) {
                q.push(node);
            }
        }
    }
    if (topo_order.size() != V) {
        cout << "Graph has a cycle, topological sort not possible." << endl;
        return {};
    }
    return topo_order;
}
