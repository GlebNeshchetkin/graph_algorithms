#include <iostream>
#include <vector>
#include <limits>

#include "include/johnson.hpp"

using namespace std;

int main() {

    int n = 5;

    Johnson<int> graph(n);

    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 8);
    graph.addEdge(0, 4, -4);

    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 7);

    graph.addEdge(2, 1, 4);

    graph.addEdge(3, 0, 2);
    graph.addEdge(3, 2, -5);

    graph.addEdge(4, 3, 6);

    vector<vector<int>> distances =
        graph.shortestPaths();

    if (distances.empty()) {
        cout << "Negative cycle detected\n";
        return 0;
    }

    const int INF =
        numeric_limits<int>::max();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            if (distances[i][j] == INF)
                cout << "INF ";
            else
                cout << distances[i][j] << " ";
        }

        cout << "\n";
    }

    return 0;
}