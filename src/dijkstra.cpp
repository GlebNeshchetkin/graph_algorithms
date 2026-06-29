#include <iostream>
#include <vector>
#include "include/heap.hpp"

using namespace std;

const int INF = 1e9;

vector<int> dijkstra(
    int n,
    vector<vector<pair<int,int>>>& graph,
    int source
) {
    vector<int> dist(n, INF);
    Heap<pair<int,int>> pq; // (distance, node)

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto [v, w] : graph[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n = 5;
    vector<vector<pair<int,int>>> graph(n);

    graph[0].push_back({1, 10});
    graph[0].push_back({2, 3});
    graph[2].push_back({1, 4});
    graph[1].push_back({3, 2});
    graph[2].push_back({3, 8});

    vector<int> dist = dijkstra(n, graph, 0);

    for (int i = 0; i < n; i++) {
        cout << i << " -> " << dist[i] << "\n";
    }

    return 0;
}