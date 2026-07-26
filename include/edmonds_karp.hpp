#ifndef EDMONDS_KARP_HPP
#define EDMONDS_KARP_HPP

#include <bits/stdc++.h>
#include <vector>

class EdmondsKarp {
    int n;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> adj;

public:
    EdmondsKarp(int n) : n(n) {
        capacity.assign(n, std::vector<int>(n, 0));
        adj.resize(n);
    }

    void addEdge(int u, int v, int cap) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += cap;
    }

    int bfs(int s, int t, std::vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;

        std::queue<std::pair<int,int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            auto [cur, flow] = q.front();
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = std::min(flow, capacity[cur][next]);
                    if (next == t) return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        std::vector<int> parent(n);

        int new_flow;
        while ((new_flow = bfs(s, t, parent))) {
            flow += new_flow;

            int cur = t;
            while (cur != s) {
                int prev = parent[cur];

                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;

                cur = prev;
            }
        }

        return flow;
    }
};

#endif