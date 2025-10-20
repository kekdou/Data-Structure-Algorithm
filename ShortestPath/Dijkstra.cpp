#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

const int INF = std::numeric_limits<int>::max();

using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::vector;

void Dijkstra(const vector<vector<pair<int, int>>> &adj, int n) {
    vector<int> dist(adj.size(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
    pq.push({n, 0});
    dist[n] = 0;
    while (!pq.empty()) {
        int cur_node = pq.top().first;
        int cur_node_dist = pq.top().second;
        pq.pop();
        if (cur_node_dist > dist[cur_node]) {
            continue;
        }
        for (const auto &edge : adj[cur_node]) {
            int node = edge.first;
            int weight = edge.second;
            if (dist[cur_node] + weight < dist[node]) {
                dist[node] = dist[cur_node] + weight;
                pq.push({node, dist[node]});
            }
        }
    }
    cout << "from node:" << n
         << " to other nodes 's shortest path is: " << endl;
    for (int i = 0; i < adj.size(); i++) {
        if (dist[i] == INF) {
            cout << "node " << i << "can't reach" << endl;
        } else {
            cout << "node " << i << ": " << dist[i] << endl;
        }
    }
}
