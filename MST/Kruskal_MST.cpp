#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

struct Edge {
    int u, v, weight;
};

bool Compare_Edges(const Edge &u, const Edge &v) { return u.weight < v.weight; }

struct DSU {
    vector<int> parents;
    DSU(int n) {
        parents.resize(n);
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
    }
    int Find(int i) {
        if (parents[i] == i) {
            return i;
        }
        return parents[i] = Find(parents[i]);
    }
    void Union(int u, int v) {
        int u_parent = Find(u);
        int v_parent = Find(v);
        if (u_parent != v_parent) {
            parents[u_parent] = v_parent;
        }
    }
};

void Kruskal_MST(const vector<Edge> &edges) {
    int V = 0;
    for (const auto &edge : edges) {
        V = std::max(V, std::max(edge.u, edge.v));
    }
    V++;
    vector<Edge> sort_edges = edges;
    std::sort(sort_edges.begin(), sort_edges.end(), Compare_Edges);
    DSU dsu(V);
    vector<Edge> mst;
    int total = 0;
    for (const auto &edge : sort_edges) {
        if (mst.size() == V - 1) {
            break;
        }
        if (dsu.Find(edge.u) != dsu.Find(edge.v)) {
            dsu.Union(edge.u, edge.v);
            mst.push_back(edge);
            total += edge.weight;
        }
    }
    cout << "total weight: " << total << endl;
    for (const auto &edge : mst) {
        cout << edge.u << " -- " << edge.v << " : " << edge.weight << endl;
    }
}
