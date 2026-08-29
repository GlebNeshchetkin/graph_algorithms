#include <iostream>
#include "include/topological_sort.hpp"

int main() {
    TopologicalSort graph(6);

    graph.addEdge(5, 2);
    graph.addEdge(5, 0);
    graph.addEdge(4, 0);
    graph.addEdge(4, 1);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    std::vector<int> order = graph.sort();

    for (int v : order) {
        std::cout << v << ' ';
    }

    std::cout << '\n';

    return 0;
}