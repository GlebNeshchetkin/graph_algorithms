#include <iostream>
#include "include/kruskal.hpp"

int main() {
    std::vector<SimpleEdge<std::string>> edges = {
        {"A", "B", 4},
        {"A", "H", 8},
        {"B", "C", 8},
        {"B", "H", 11},
        {"C", "D", 7},
        {"C", "F", 4},
        {"C", "I", 2},
        {"D", "E", 9},
        {"D", "F", 14},
        {"E", "F", 10},
        {"F", "G", 2},
        {"G", "H", 1},
        {"G", "I", 6},
        {"H", "I", 7}
    };

    KruskalMST<std::string> kruskal;
    std::vector<SimpleEdge<std::string>> mst = kruskal.findMST(edges);
    
    int totalWeight = 0;
    int edgeNumber = 1;
    
    for (const SimpleEdge<std::string>& SimpleEdge : mst) {
        std::cout << edgeNumber << ". " << SimpleEdge.from << " --- " << SimpleEdge.to << " : " << SimpleEdge.weight << std::endl;
        totalWeight += SimpleEdge.weight;
        edgeNumber++;
    }
    
    std::cout << "MST Weight: " << totalWeight << std::endl;
    
    return 0;
}