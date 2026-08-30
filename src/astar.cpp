#include <iostream>
#include "include/astar.hpp"

int main() {
    AStar<int> graph(6);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 4, 3);
    graph.addEdge(4, 3, 2);
    graph.addEdge(3, 5, 1);

    std::vector<int> h = {
        6, 5, 4, 1, 2, 0
    };

    int start = 0;
    int goal = 5;

    int distance = graph.shortestPath(
        start,
        goal,
        [&h](int v) {
            return h[v];
        }
    );

    std::cout << "Shortest path: "
              << distance << '\n';

    return 0;
}