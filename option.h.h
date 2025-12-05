#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED
#include <vector>
#include <iostream>
#include <iomanip>

template<typename T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    explicit BinaryTree(int depth = 0);
    void setDepth(int depth);
    void setNode(int n, int i, const T& value);
    T getNode(int n, int i) const;
    void display() const;
    int depth() const;
};


#endif // PARTIE_2_H_INCLUDED
