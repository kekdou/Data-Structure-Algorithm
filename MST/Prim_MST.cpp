#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::vector;

const int INF = std::numeric_limits<int>::max();

void Prim_MST(const vector<vector<pair<int, int>>> &adj, int n) {
    int V = adj.size();
    vector<int> key(V, INF);
    vector<bool> in_MST(V, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
    int total = 0;
    pq.push({n, 0});
    while (!pq.empty()) {
        int cur_node = pq.top().first;
        int cur_node_weight = pq.top().second;
        pq.pop();
        if (in_MST[cur_node]) {
            continue;
        }
        in_MST[cur_node] = 1;
        total += cur_node_weight;
        for (const auto &node : adj[cur_node]) {
            int u = node.first;
            int u_weight = node.second;
            if (!in_MST[u] && u_weight < key[u]) {
                key[u] = u_weight;
                pq.push({u, key[u]});
            }
        }
    }
    cout << "total weight is" << total << endl;
}

