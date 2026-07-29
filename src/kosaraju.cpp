#include <iostream>
#include "include/kosaraju.hpp"

int main() {
    Kosaraju<int> graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    graph.addEdge(1, 3);
    graph.addEdge(3, 4);

    auto sccs = graph.findSCCs();

    for (size_t i = 0; i < sccs.size(); i++) {
        printf("{");
        for (size_t j = 0; j < sccs[i].size(); j++) {
            if (j < sccs[i].size() - 1) printf("%d,", sccs[i][j]);
            else printf("%d", sccs[i][j]);
        }
        printf("}\n");
    }
}