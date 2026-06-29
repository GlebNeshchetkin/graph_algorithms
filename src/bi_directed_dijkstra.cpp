#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "include/heap.hpp"

using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<pair<int,int>>> build_reverse(
    int n,
    const vector<vector<pair<int,int>>>& graph
) {
    vector<vector<pair<int,int>>> rgraph(n);

    for (int u = 0; u < n; u++) {
        for (auto [v, w] : graph[u]) {
            rgraph[v].push_back({u, w});
        }
    }

    return rgraph;
}

int bidirectional_dijkstra(
    int n,
    const vector<vector<pair<int,int>>>& graph,
    const vector<vector<pair<int,int>>>& rgraph,
    int s,
    int t
) {
    vector<int> dist_f(n, INF), dist_b(n, INF);
    vector<bool> vis_f(n, false), vis_b(n, false);

    Heap<pair<int,int>> pq_f, pq_b;

    dist_f[s] = 0;
    dist_b[t] = 0;

    pq_f.push({0, s});
    pq_b.push({0, t});

    int best = INF;

    while (!pq_f.empty() || !pq_b.empty()) {
        if (!pq_f.empty()) {
            auto [d, u] = pq_f.top();
            pq_f.pop();

            if (d == dist_f[u] && !vis_f[u]) {
                vis_f[u] = true;

                if (vis_b[u])
                    best = min(best, dist_f[u] + dist_b[u]);

                for (auto [v, w] : graph[u]) {
                    if (dist_f[v] > d + w) {
                        dist_f[v] = d + w;
                        pq_f.push({dist_f[v], v});
                    }
                }
            }
        }

        if (!pq_b.empty()) {
            auto [d, u] = pq_b.top();
            pq_b.pop();

            if (d == dist_b[u] && !vis_b[u]) {
                vis_b[u] = true;

                if (vis_f[u])
                    best = min(best, dist_f[u] + dist_b[u]);

                for (auto [v, w] : rgraph[u]) {
                    if (dist_b[v] > d + w) {
                        dist_b[v] = d + w;
                        pq_b.push({dist_b[v], v});
                    }
                }
            }
        }

        if (best != INF) {
            int top_f = pq_f.empty() ? INF : pq_f.top().first;
            int top_b = pq_b.empty() ? INF : pq_b.top().first;

            if (top_f + top_b >= best)
                break;
        }
    }

    return (best == INF ? -1 : best);
}

int main() {
    int n = 5;

    vector<vector<pair<int,int>>> graph(n);

    graph[0].push_back({1, 10});
    graph[0].push_back({2, 3});
    graph[2].push_back({1, 4});
    graph[1].push_back({3, 2});
    graph[2].push_back({3, 8});

    auto rgraph = build_reverse(n, graph);

    int s = 0, t = 3;

    std::cout << bidirectional_dijkstra(n, graph, rgraph, s, t) << "\n";

    return 0;
}