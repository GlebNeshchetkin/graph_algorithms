#ifndef PRIM_HPP
#define PRIM_HPP

#include <vector>
#include <unordered_map>
#include <limits>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "graph.hpp"
#include "heap.hpp"

template<typename T>
class PrimMST {
private:
    std::unordered_map<T, std::vector<SimpleEdge<T>>> adjList;
    
public:
    void addEdges(const std::vector<SimpleEdge<T>>& edges) {
        for (const auto& SimpleEdge : edges) {
            addEdge(SimpleEdge.from, SimpleEdge.to, SimpleEdge.weight);
        }
    }
    
    void addEdge(T from, T to, int weight) {
        adjList[from].push_back(SimpleEdge<T>(from, to, weight));
        adjList[to].push_back(SimpleEdge<T>(to, from, weight));
    }
    
    std::vector<SimpleEdge<T>> findMST(T start) {
        std::unordered_map<T, int> key;
        std::unordered_map<T, T> parent;
        std::unordered_map<T, bool> inMST;
        Heap<SimpleNode<T>> pq;
        
        for (auto& pair : adjList) {
            key[pair.first] = std::numeric_limits<int>::max();
            parent[pair.first] = T();
            inMST[pair.first] = false;
        }
        
        key[start] = 0;
        pq.push({start, 0, T()});
        
        while (!pq.empty()) {
            SimpleNode<T> current = pq.top();
            pq.pop();
            
            T u = current.vertex;
            if (inMST[u]) continue;
            
            inMST[u] = true;
            
            for (const SimpleEdge<T>& SimpleEdge : adjList[u]) {
                T v = SimpleEdge.to;
                int weight = SimpleEdge.weight;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({v, weight, u});
                }
            }
        }
        
        std::vector<SimpleEdge<T>> mst;
        for (auto& pair : parent) {
            if (pair.second != T()) {
                mst.push_back(SimpleEdge<T>(pair.second, pair.first, key[pair.first]));
            }
        }
        return mst;
    }
    
    std::vector<T> getVertices() {
        std::vector<T> vertices;
        for (auto& pair : adjList) {
            vertices.push_back(pair.first);
        }
        std::sort(vertices.begin(), vertices.end());
        return vertices;
    }
};

#endif