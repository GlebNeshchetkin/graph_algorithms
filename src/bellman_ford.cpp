#include <iostream>
#include <limits>
#include "include/bellman_ford.hpp"

int main() {
    BellmanFord<int> graph(5);

    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 7);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, -4);
    graph.addEdge(2, 3, -3);
    graph.addEdge(2, 4, 9);
    graph.addEdge(3, 1, -2);
    graph.addEdge(4, 0, 2);
    graph.addEdge(4, 3, 7);

    auto distances = graph.shortestPaths(0);

    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "0 -> " << i << " = ";

        if (distances[i] == std::numeric_limits<int>::max()) {
            std::cout << "INF";
        } else {
            std::cout << distances[i];
        }

        std::cout << '\n';
    }

    if (graph.hasNegativeCycle(0)) {
        std::cout << "\nNegative cycle detected\n";
    } else {
        std::cout << "\nNo negative cycle detected\n";
    }

    return 0;
}