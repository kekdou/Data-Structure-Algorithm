#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

const int INF = std::numeric_limits<int>::max();

struct Edge {
    int u, v, weight;
};

void Bellman_Ford(const vector<Edge> &edges, int n) {
    int V = 0;
    for (const auto &edge : edges) {
        V = std::max(V, std::max(edge.u, edge.v));
    }
    V++;
    vector<int> dist(V, INF);
    dist[n] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (const auto &edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    for (const auto &edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            cout << "exist negative weight ring!" << endl;
            return;
        }
    }
    cout << "from node:" << n << "to other nodes's shortest path is: " << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            cout << "node " << i << "can't be reached" << endl;
        } else {
            cout << "node " << i << ": " << dist[i] << endl;
        }
    }
}

