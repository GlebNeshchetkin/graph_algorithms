#ifndef KOSARAJU_HPP
#define KOSARAJU_HPP

#include <vector>
#include <stack>
#include <algorithm>

template<typename T = int>
class Kosaraju {
private:
    int vertices;
    std::vector<std::vector<T>> graph;
    std::vector<std::vector<T>> reversedGraph;

    void dfs1(T node, std::vector<bool>& visited, std::stack<T>& order) const {
        visited[node] = true;
        for (const auto& neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs1(neighbor, visited, order);
            }
        }
        order.push(node);
    }

    void dfs2(T node, std::vector<bool>& visited, std::vector<T>& component) const {
        visited[node] = true;
        component.push_back(node);
        for (const auto& neighbor : reversedGraph[node]) {
            if (!visited[neighbor]) {
                dfs2(neighbor, visited, component);
            }
        }
    }

public:
    explicit Kosaraju(int n)
        : vertices(n),
          graph(n),
          reversedGraph(n) {}

    void addEdge(T from, T to) {
        graph[from].push_back(to);
        reversedGraph[to].push_back(from);
    }

    std::vector<std::vector<T>> findSCCs() const {
        std::vector<bool> visited(vertices, false);
        std::stack<T> order;

        for (T vertex = 0; vertex < vertices; ++vertex) {
            if (!visited[vertex]) {
                dfs1(vertex, visited, order);
            }
        }

        std::fill(visited.begin(), visited.end(), false);
        std::vector<std::vector<T>> sccs;
        while (!order.empty()) {
            T vertex = order.top();
            order.pop();
            if (!visited[vertex]) {
                std::vector<T> component;
                dfs2(vertex, visited, component);
                sccs.push_back(std::move(component));
            }
        }

        return sccs;
    }
};

#endif