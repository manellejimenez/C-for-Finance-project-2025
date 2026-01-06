#include "EuropeanVanillaOption.h"
#include "BinaryTree.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>



template <typename T>
BinaryTree<T>::BinaryTree(int depth) : _depth(depth) {

    // Initialisation
    _depth = depth;
    _tree.resize(_depth + 1); 

    for (int i = 0; i < _tree.size(); i++)
    { 
        // Initialise la taille de chaque niveau
        _tree[i].resize(i + 1);
    }
        
}

template <typename T>
void BinaryTree<T>::setDepth(int depth) {

    // Ajustement : réduction de l'arbre si la nouvelle profondeur est inférieure.
    if (_depth > depth) 
    {
        _depth = depth;
        _tree.resize(_depth + 1);
    }
    else { 

        _tree.resize(depth + 1);

        for (int i = _depth; i < _tree.size(); i++)
            _tree[i].resize(i + 1);
        _depth = depth;
    }
}

template <typename T>
int BinaryTree<T>::getDepth() {

    return _depth;
}

template <typename T>
long BinaryTree<T>::getSize(int index) {

    return _tree[index].size();
}

template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {

    if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
        _tree[level][index] = value;
    }
    else {
        std::cerr << "Error: Invalid node position." << std::endl;
    }
}

template <typename T>
T BinaryTree<T>::getNode(int level, int index) const {
    if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
        return _tree[level][index];
    }
    else {
        throw std::out_of_range("Error: Invalid node position.");
    }
}



// Prints toutes les valeurs de l'arbre
template <typename T>
void BinaryTree<T>::display()
{
    for (int i = 0; i <= _depth; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::cout << _tree[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int width = 4 * (_depth + 1);
    for (int i = 0; i <= _depth; ++i) {

        // Print leading spaces
        std::cout << std::setw(width - 2 * i) << "";

        // Redimensionnement : élagage si la nouvelle profondeur est plus faible
        for (int j = 0; j <= i; ++j) {
            std::cout << std::setw(5) << _tree[i][j] << "  ";
        }
        std::cout << "\n";

        // Liaison visuelle des nœuds (sauf dernier niveau)
        if (i < _depth) {
            std::cout << std::setw(width - 2 * i) << ""; 
            std::cout << "\n";
        }
    }
}


//Template de type pour les arbres
template class BinaryTree< double >;
template class BinaryTree< bool >;
template class BinaryTree< int >;


