#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::stack;
using std::vector;

void DFS(const vector<vector<int>> &adj, int n) {
    vector<bool> visited(adj.size(), 0);
    stack<int> s;
    visited[n] = 1;
    s.push(n);
    while (!s.empty()) {
        int cur_node = s.top();
        s.pop();
        cout << cur_node << " ";
        for (int node : adj[cur_node]) {
            if (!visited[node]) {
                visited[node] = 1;
                s.push(node);
            }
        }
    }
    cout << endl;
}

void DFS_Util(const vector<vector<int>> &adj, int n, vector<bool> visited) {
    visited[n] = 1;
    cout << n << " ";
    for (int node : adj[n]) {
        if (!visited[node]) {
            DFS_Util(adj, node, visited);
        }
    }
}

void DFS2(const vector<vector<int>> &adj, int n) {
    vector<bool> visited(adj.size(), 0);
    DFS_Util(adj, n, visited);
    cout << endl;
}

