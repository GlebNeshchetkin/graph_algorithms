#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <utility>
#include <algorithm>

template <typename T>
class AStar {
private:
    struct Edge {
        int to;
        T weight;
    };

    struct Node {
        int vertex;
        T f_score;

        bool operator>(const Node& other) const {
            return f_score > other.f_score;
        }
    };

    int n;
    std::vector<std::vector<Edge>> graph;

public:
    explicit AStar(int vertices)
        : n(vertices), graph(vertices) {}

    void addEdge(int u, int v, T weight) {
        graph[u].push_back({v, weight});
    }

    T shortestPath(
        int start,
        int goal,
        const std::function<T(int)>& heuristic
    ) const {
        const T INF = std::numeric_limits<T>::max();

        std::vector<T> g_score(n, INF);
        std::vector<bool> closed(n, false);

        std::priority_queue<
            Node,
            std::vector<Node>,
            std::greater<Node>
        > open_set;

        g_score[start] = 0;

        open_set.push({
            start,
            heuristic(start)
        });

        while (!open_set.empty()) {
            Node current = open_set.top();
            open_set.pop();

            int u = current.vertex;

            if (closed[u])
                continue;

            if (u == goal)
                return g_score[u];

            closed[u] = true;

            for (const Edge& edge : graph[u]) {
                int v = edge.to;

                if (closed[v])
                    continue;

                T new_g_score = g_score[u] + edge.weight;

                if (new_g_score < g_score[v]) {
                    g_score[v] = new_g_score;

                    T f_score =
                        g_score[v] + heuristic(v);

                    open_set.push({v, f_score});
                }
            }
        }

        return INF;
    }
};

#endif