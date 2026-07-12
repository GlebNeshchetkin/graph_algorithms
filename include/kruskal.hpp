#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include <vector>
#include <unordered_map>
#include <algorithm>
#include "graph.hpp"
#include "heap.hpp"
#include "disjoint_set.hpp"

template<typename T>
class KruskalMST {
private:
    std::vector<SimpleEdge<T>> edgeList;
    
public:
    void addEdge(T from, T to, int weight) {
        edgeList.push_back(SimpleEdge<T>(from, to, weight));
    }
    
    void addEdges(const std::vector<SimpleEdge<T>>& edges) {
        for (const auto& SimpleEdge : edges) {
            edgeList.push_back(SimpleEdge);
        }
    }
    
    std::vector<SimpleEdge<T>> findMST() {
        Heap<SimpleEdge<T>> minHeap;
        DisjointSet<T> ds;
        std::vector<SimpleEdge<T>> mst;
        
        for (const auto& SimpleEdge : edgeList) {
            minHeap.push(SimpleEdge);
            ds.makeSet(SimpleEdge.from);
            ds.makeSet(SimpleEdge.to);
        }
        
        while (!minHeap.empty() && mst.size() < edgeList.size() - 1) {
            SimpleEdge<T> SimpleEdge = minHeap.top();
            minHeap.pop();
            
            if (ds.find(SimpleEdge.from) != ds.find(SimpleEdge.to)) {
                ds.unionSets(SimpleEdge.from, SimpleEdge.to);
                mst.push_back(SimpleEdge);
            }
        }
        
        return mst;
    }
    
    std::vector<SimpleEdge<T>> findMST(const std::vector<SimpleEdge<T>>& edges) {
        edgeList = edges;
        return findMST();
    }
    
    const std::vector<SimpleEdge<T>>& getEdges() const {
        return edgeList;
    }
    
    void clear() {
        edgeList.clear();
    }
    
    size_t edgeCount() const {
        return edgeList.size();
    }
    
    bool empty() const {
        return edgeList.empty();
    }
};

#endif