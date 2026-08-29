#ifndef TOPOLOGICAL_SORT_HPP
#define TOPOLOGICAL_SORT_HPP

#include <vector>
#include <queue>

class TopologicalSort {
private:
    int n;
    std::vector<std::vector<int>> graph;

public:
    explicit TopologicalSort(int vertices)
        : n(vertices), graph(vertices) {}

    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    std::vector<int> sort() const {
        std::vector<int> indegree(n, 0);

        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                ++indegree[v];
            }
        }

        std::queue<int> q;

        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> order;
        order.reserve(n);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            order.push_back(u);

            for (int v : graph[u]) {
                --indegree[v];

                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Cycle exists if not all vertices were processed.
        if (static_cast<int>(order.size()) != n) {
            return {};
        }

        return order;
    }
};

#endif