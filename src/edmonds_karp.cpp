#include <iostream>
#include "include/edmonds_karp.hpp"

int main() {
    EdmondsKarp ek(6);

    ek.addEdge(0,1,16);
    ek.addEdge(0,2,13);
    ek.addEdge(1,2,10);
    ek.addEdge(2,1,4);
    ek.addEdge(1,3,12);
    ek.addEdge(2,4,14);
    ek.addEdge(3,2,9);
    ek.addEdge(4,3,7);
    ek.addEdge(3,5,20);
    ek.addEdge(4,5,4);

    std::cout << ek.maxFlow(0,5) << std::endl;
}