#ifndef DINIC_HPP
#define DINIC_HPP

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

template <typename T>
class Dinic {
private:
    struct Edge {
        int to;
        int rev;
        T capacity;
    };

    int n;
    std::vector<std::vector<Edge>> graph;
    std::vector<int> level;
    std::vector<int> ptr;

    bool bfs(int source, int sink) {
        std::fill(level.begin(), level.end(), -1);

        std::queue<int> q;
        q.push(source);
        level[source] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& edge : graph[u]) {
                if (edge.capacity > 0 &&
                    level[edge.to] == -1) {

                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }

        return level[sink] != -1;
    }

    T dfs(int u, int sink, T pushed) {
        if (pushed == 0)
            return 0;

        if (u == sink)
            return pushed;

        for (int& cid = ptr[u];
             cid < static_cast<int>(graph[u].size());
             ++cid) {

            Edge& edge = graph[u][cid];

            if (edge.capacity <= 0 ||
                level[edge.to] != level[u] + 1) {
                continue;
            }

            T flow = dfs(
                edge.to,
                sink,
                std::min(pushed, edge.capacity)
            );

            if (flow == 0)
                continue;

            edge.capacity -= flow;
            graph[edge.to][edge.rev].capacity += flow;

            return flow;
        }

        return 0;
    }

public:
    explicit Dinic(int vertices)
        : n(vertices),
          graph(vertices),
          level(vertices),
          ptr(vertices) {}

    void addEdge(int u, int v, T capacity) {
        Edge forward{
            v,
            static_cast<int>(graph[v].size()),
            capacity
        };

        Edge backward{
            u,
            static_cast<int>(graph[u].size()),
            0
        };

        graph[u].push_back(forward);
        graph[v].push_back(backward);
    }

    T maxFlow(int source, int sink) {
        T flow = 0;

        const T INF = std::numeric_limits<T>::max();

        while (bfs(source, sink)) {
            std::fill(ptr.begin(), ptr.end(), 0);

            while (T pushed = dfs(source, sink, INF)) {
                flow += pushed;
            }
        }

        return flow;
    }
};

#endif