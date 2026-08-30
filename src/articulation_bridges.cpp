#include <iostream>
#include "include/articulation_bridges.hpp"

int main() {
    ArticulationBridges graph(7);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    graph.addEdge(1, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 3);

    graph.addEdge(3, 6);

    graph.find();

    std::cout << "Articulation points:\n";

    for (int v : graph.getArticulationPoints()) {
        std::cout << v << ' ';
    }

    std::cout << "\n\nBridges:\n";

    for (const auto& [u, v] : graph.getBridges()) {
        std::cout << u << " - " << v << '\n';
    }

    return 0;
}