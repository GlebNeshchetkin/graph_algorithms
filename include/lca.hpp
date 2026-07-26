#ifndef LCA_HPP
#define LCA_HPP

#include <vector>
#include <unordered_map>
#include "disjoint_set.hpp"


template<typename T>
class TarjanLCA {

private:

    std::unordered_map<T, std::vector<T>> tree;
    std::unordered_map<T, std::vector<std::pair<T,int>>> queries;
    std::unordered_map<T,T> ancestor;
    std::unordered_map<T,bool> visited;
    std::unordered_map<int,T> answer;

    DisjointSet<T> ds;

    void dfs(T u)
    {
        ds.makeSet(u);
        ancestor[u] = u;
        for (T v : tree[u]) {
            dfs(v);
            ds.unionSets(u, v);
            ancestor[ds.find(u)] = u;
        }
        visited[u] = true;
        for (auto [v,id] : queries[u]) {
            if (visited[v]) {
                answer[id] = ancestor[ds.find(v)];
            }
        }
    }

public:

    void addEdge(T parent, T child) {
        tree[parent].push_back(child);
    }

    void addQuery(T u, T v, int id) {
        queries[u].push_back({v,id});
        queries[v].push_back({u,id});
    }

    std::unordered_map<int,T> solve(T root) {
        dfs(root);
        return answer;
    }

};


#endif