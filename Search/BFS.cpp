#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::vector;

void BFS(const vector<vector<int>> &adj, int n) {
    vector<bool> visited(adj.size(), 0);
    queue<int> q;
    visited[n] = 1;
    q.push(n);
    while (!q.empty()) {
        int cur_node = q.front();
        q.pop();
        cout << cur_node << " ";
        for (int node : adj[cur_node]) {
            if (!visited[node]) {
                visited[node] = 1;
                q.push(node);
            }
        }
    }
    cout << endl;
}

