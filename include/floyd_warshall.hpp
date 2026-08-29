#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <vector>
#include <limits>
#include <algorithm>

template <typename T>
class FloydWarshall {
private:
    static constexpr T INF = std::numeric_limits<T>::max() / 4;

    std::vector<std::vector<T>> dist;
    int n;

public:
    explicit FloydWarshall(int vertices)
        : n(vertices),
          dist(vertices, std::vector<T>(vertices, INF)) {

        for (int i = 0; i < n; ++i)
            dist[i][i] = 0;
    }

    void addEdge(int u, int v, T weight) {
        dist[u][v] = std::min(dist[u][v], weight);
    }

    void compute() {
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                if (dist[i][k] == INF)
                    continue;

                for (int j = 0; j < n; ++j) {
                    if (dist[k][j] == INF)
                        continue;

                    dist[i][j] = std::min(
                        dist[i][j],
                        dist[i][k] + dist[k][j]
                    );
                }
            }
        }
    }

    T getDistance(int u, int v) const {
        return dist[u][v];
    }

    const std::vector<std::vector<T>>& getDistances() const {
        return dist;
    }
};

#endif