#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

const int INF = std::numeric_limits<int>::max();

void Folyd_Warshall(const vector<vector<int>> &adj) {
    int V = adj.size();
    vector<vector<int>> dist = adj;
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    for (int i = 0; i < V; i++) {
        cout << "node:" << i << "to other nodes's shortest path is:" << endl;
        for (int j = 0; j < V; j++) {
            if (dist[i][j] != INF) {
                cout << "node: " << j << ": " << dist[i][j] << endl;
            } else {
                cout << "node: " << j << "can't be reached" << endl;
            }
        }
    }
}

