#ifndef ARTICULATION_BRIDGES_HPP
#define ARTICULATION_BRIDGES_HPP

#include <vector>
#include <utility>
#include <algorithm>

class ArticulationBridges {
private:
    int n;
    int timer;

    std::vector<std::vector<std::pair<int, int>>> graph;

    std::vector<int> tin;
    std::vector<int> low;
    std::vector<bool> visited;
    std::vector<bool> articulationPoints;

    std::vector<std::pair<int, int>> bridges;

    void dfs(int u, int parentEdge) {
        visited[u] = true;

        tin[u] = low[u] = timer++;

        int children = 0;

        for (const auto& [v, edgeId] : graph[u]) {
            if (edgeId == parentEdge)
                continue;

            if (visited[v]) {
                low[u] = std::min(
                    low[u],
                    tin[v]
                );
            }
            else {
                dfs(v, edgeId);

                low[u] = std::min(
                    low[u],
                    low[v]
                );

                // Bridge
                if (low[v] > tin[u]) {
                    bridges.push_back({u, v});
                }

                // Articulation point
                if (parentEdge != -1 &&
                    low[v] >= tin[u]) {
                    articulationPoints[u] = true;
                }

                ++children;
            }
        }

        // Root is an articulation point
        // if it has more than one DFS child.
        if (parentEdge == -1 && children > 1) {
            articulationPoints[u] = true;
        }
    }

public:
    explicit ArticulationBridges(int vertices)
        : n(vertices),
          timer(0),
          graph(vertices),
          tin(vertices, -1),
          low(vertices, -1),
          visited(vertices, false),
          articulationPoints(vertices, false) {}

    void addEdge(int u, int v) {
        int edgeId = 0;

        for (const auto& edges : graph) {
            edgeId += static_cast<int>(edges.size());
        }

        graph[u].push_back({v, edgeId});
        graph[v].push_back({u, edgeId});
    }

    void find() {
        timer = 0;

        std::fill(
            visited.begin(),
            visited.end(),
            false
        );

        std::fill(
            articulationPoints.begin(),
            articulationPoints.end(),
            false
        );

        bridges.clear();

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, -1);
            }
        }
    }

    std::vector<int> getArticulationPoints() const {
        std::vector<int> result;

        for (int i = 0; i < n; ++i) {
            if (articulationPoints[i]) {
                result.push_back(i);
            }
        }

        return result;
    }

    const std::vector<std::pair<int, int>>&
    getBridges() const {
        return bridges;
    }
};

#endif
