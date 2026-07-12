#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

template<typename T>
class DisjointSet {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;
    
public:
    void makeSet(T x) {
        parent[x] = x;
        rank[x] = 0;
    }
    
    T find(T x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unionSets(T x, T y) {
        T rootX = find(x);
        T rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

#endif