#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class BinaryTree {
private:
    int _depth;
    std::vector<std::vector<T>> _tree;

public:
    // Constructeur
    BinaryTree() : _depth(0) {}

    // Définit la profondeur et redimensionne les vecteurs
    void setDepth(int depth) {
        _depth = depth;
        _tree.resize(_depth + 1);
        for (int i = 0; i <= _depth; ++i) {
            _tree[i].resize(i + 1);
        }
    }

    // Setter
    void setNode(int depth, int index, T value) {
        if (depth < 0 || depth > _depth || index < 0 || index > depth) {
            throw std::out_of_range("BinaryTree: Index out of bounds");
        }
        _tree[depth][index] = value;
    }

    // Getter
    T getNode(int depth, int index) const {
        if (depth < 0 || depth > _depth || index < 0 || index > depth) {
            throw std::out_of_range("BinaryTree: Index out of bounds");
        }
        return _tree[depth][index];
    }

    // Affichage
    void display() const {
        for (int i = 0; i <= _depth; ++i) {
            for (int j = 0; j <= i; ++j) {
                std::cout << _tree[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};
