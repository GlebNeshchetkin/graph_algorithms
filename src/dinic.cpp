#include <iostream>
#include "include/dinic.hpp"

int main() {
    Dinic<int> graph(6);

    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 2, 13);

    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 12);

    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 14);

    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 5, 20);

    graph.addEdge(4, 3, 7);
    graph.addEdge(4, 5, 4);

    int source = 0;
    int sink = 5;

    std::cout << "Maximum flow: "
              << graph.maxFlow(source, sink)
              << '\n';

    return 0;
}