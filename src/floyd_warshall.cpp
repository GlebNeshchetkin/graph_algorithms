#include <iostream>
#include "include/floyd_warshall.hpp"

int main() {
    FloydWarshall<int> graph(4);

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 3, 10);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 1);

    graph.compute();

    std::cout << graph.getDistance(0, 3) << '\n'; // 9

    return 0;
}