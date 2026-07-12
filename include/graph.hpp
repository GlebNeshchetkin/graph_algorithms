#ifndef GRAPH_HPP
#define GRAPH_HPP

template<typename T>
struct SimpleEdge {
    T from;
    T to;
    int weight;
    
    SimpleEdge(T from, T to, int weight) : from(from), to(to), weight(weight) {}

    bool operator<(const SimpleEdge& other) const {
        return weight < other.weight;
    }
};

template<typename T>
struct SimpleNode {
    T vertex;
    int key;
    T parent;
    
    bool operator<(const SimpleNode& other) const {
        return key < other.key;
    }
};

#endif