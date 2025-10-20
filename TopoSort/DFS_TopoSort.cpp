#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::stack;
using std::vector;

enum State { UNVISITED, VISITING, VISITED };

vector<int> DFS_TopoSort(const vector<vector<int>> &adj) {
    int V = adj.size();
    vector<State> state(V, UNVISITED);
    vector<int> topo_order;
    stack<std::pair<int, int>> s;
    for (int i = 0; i < V; i++) {
        if (state[i] == VISITED)
            continue;
        s.emplace(i, 0);
        state[i] = VISITING;
        while (!s.empty()) {
            int cur_node = s.top().first;
            int &idx = s.top().second;
            if (idx < adj[cur_node].size()) {
                int neighbor = adj[cur_node][idx];
                idx++;
                if (state[neighbor] == VISITING) {
                    cout << "Graph has a cycle, topological sort not possible."
                         << endl;
                    return {};
                }
                if (state[neighbor] == UNVISITED) {
                    s.emplace(neighbor, 0);
                    state[neighbor] = VISITING;
                }
            } else {
                s.pop();
                state[cur_node] = VISITED;
                topo_order.push_back(cur_node);
            }
        }
    }
    std::reverse(topo_order.begin(), topo_order.end());
    return topo_order;
}

bool DFS_Util(const vector<vector<int>> &adj, int n, vector<State> &state,
              vector<int> &topo_order) {
    state[n] = VISITING;
    for (int node : adj[n]) {
        if (state[node] == VISITING) {
            return 0;
        }
        if (state[node] == UNVISITED) {
            DFS_Util(adj, node, state, topo_order);
        }
    }
    state[n] = VISITED;
    topo_order.push_back(n);
    return 1;
}

vector<int> DFS_TopoSort2(const vector<vector<int>> &adj) {
    int V = adj.size();
    vector<State> state(V, UNVISITED);
    vector<int> topo_order;
    for (int i = 0; i < V; i++) {
        if (state[i] != VISITED) {
            if (!DFS_Util(adj, i, state, topo_order)) {
                cout << "Graph has a cycle, topological sort not possible."
                     << endl;
                return {};
            }
        }
    }
    std::reverse(topo_order.begin(), topo_order.end());
    return topo_order;
}

