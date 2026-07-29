#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <vector>
#include <limits>
#include "graph.hpp"

template<typename T>
class BellmanFord {
private:
    int vertices;
    std::vector<SimpleEdge<T>> edges;

public:
    explicit BellmanFord(int vertices)
        : vertices(vertices) {}

    void addEdge(T from, T to, int weight) {
        edges.emplace_back(from, to, weight);
    }

    std::vector<int> shortestPaths(T source) const {
        const int INF = std::numeric_limits<int>::max();
        std::vector<int> distance(vertices, INF);
        distance[source] = 0;
        for (int i = 0; i < vertices - 1; ++i) {
            bool updated = false;
            for (const auto& edge : edges) {
                if (distance[edge.from] == INF) continue;
                if (distance[edge.from] + edge.weight < distance[edge.to]) {
                    distance[edge.to] = distance[edge.from] + edge.weight;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        return distance;
    }

    bool hasNegativeCycle(T source) const {
        const int INF = std::numeric_limits<int>::max();
        std::vector<int> distance(vertices, INF);
        distance[source] = 0;
        for (int i = 0; i < vertices - 1; ++i) {
            for (const auto& edge : edges) {
                if (distance[edge.from] == INF) continue;
                if (distance[edge.from] + edge.weight < distance[edge.to]) {
                    distance[edge.to] = distance[edge.from] + edge.weight;
                }
            }
        }

        for (const auto& edge : edges) {
            if (distance[edge.from] == INF) continue;
            if (distance[edge.from] + edge.weight < distance[edge.to]) {
                return true;
            }
        }

        return false;
    }
};

#endif