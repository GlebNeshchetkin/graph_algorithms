#ifndef JOHNSON_HPP
#define JOHNSON_HPP

#include <vector>
#include <limits>
#include <functional>
#include "graph.hpp"
#include "heap.hpp"
#include "bellman_ford.hpp"

template<typename T>
class Johnson {
private:
    int vertices;

    struct Edge {
        T from;
        T to;
        int weight;
    };

    std::vector<Edge> edges;

public:
    explicit Johnson(int vertices)
        : vertices(vertices) {}

    void addEdge(T from, T to, int weight) {
        edges.push_back({from, to, weight});
    }

    std::vector<std::vector<int>> shortestPaths() const {
        const int INF = std::numeric_limits<int>::max();

        BellmanFord<T> bf(vertices + 1);

        T virtualSource = vertices;

        for (const auto& edge : edges) {
            bf.addEdge(
                edge.from,
                edge.to,
                edge.weight
            );
        }

        for (int v = 0; v < vertices; ++v) {
            bf.addEdge(virtualSource, v, 0);
        }

        // Bellman-Ford gives the potential h(v)
        std::vector<int> h =
            bf.shortestPaths(virtualSource);

        if (bf.hasNegativeCycle(virtualSource)) {
            return {};
        }

        std::vector<std::vector<std::pair<int, int>>> graph(
            vertices
        );

        for (const auto& edge : edges) {
            int newWeight =
                edge.weight +
                h[edge.from] -
                h[edge.to];

            graph[edge.from].push_back({
                edge.to,
                newWeight
            });
        }

        std::vector<std::vector<int>> distances(
            vertices,
            std::vector<int>(vertices, INF)
        );

        for (int source = 0; source < vertices; ++source) {

            std::vector<int> dist(vertices, INF);

            Heap<std::pair<int, int>> pq;

            dist[source] = 0;
            pq.push({0, source});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d != dist[u])
                    continue;

                for (auto [v, weight] : graph[u]) {
                    if (dist[v] > d + weight) {
                        dist[v] = d + weight;
                        pq.push({dist[v], v});
                    }
                }
            }

            for (int v = 0; v < vertices; ++v) {
                if (dist[v] != INF) {
                    distances[source][v] =
                        dist[v] - h[source] + h[v];
                }
            }
        }

        return distances;
    }
};

#endif