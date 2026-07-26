#include <iostream>
#include "include/ford_fulkerson.hpp"

int main() {
    FordFulkerson ff(6);

    ff.addEdge(0,1,16);
    ff.addEdge(0,2,13);
    ff.addEdge(1,2,10);
    ff.addEdge(2,1,4);
    ff.addEdge(1,3,12);
    ff.addEdge(2,4,14);
    ff.addEdge(3,2,9);
    ff.addEdge(4,3,7);
    ff.addEdge(3,5,20);
    ff.addEdge(4,5,4);

    std::cout << ff.maxFlow(0,5) << std::endl;
}