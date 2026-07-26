#ifndef FORD_FULKERSON_HPP
#define FORD_FULKERSON_HPP

#include <bits/stdc++.h>
#include <vector>

class FordFulkerson {
    int n;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> adj;

    int dfs(int v, int t, int flow, std::vector<int>& visited) {
        if (v == t) return flow;
        visited[v] = 1;

        for (int to : adj[v]) {
            if (!visited[to] && capacity[v][to] > 0) {
                int new_flow = dfs(
                    to, t,
                    std::min(flow, capacity[v][to]),
                    visited
                );

                if (new_flow > 0) {
                    capacity[v][to] -= new_flow;
                    capacity[to][v] += new_flow;
                    return new_flow;
                }
            }
        }
        return 0;
    }

public:
    FordFulkerson(int n) : n(n) {
        capacity.assign(n, std::vector<int>(n, 0));
        adj.resize(n);
    }

    void addEdge(int u, int v, int cap) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    }

    int maxFlow(int s, int t) {
        int flow = 0;

        while (true) {
            std::vector<int> visited(n, 0);
            int pushed = dfs(s, t, INT_MAX, visited);
            if (pushed == 0) break;
            flow += pushed;
        }

        return flow;
    }
};

#endif