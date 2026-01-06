#pragma once
#include "EuropeanVanillaOption.h"
#include <iostream>
#include <vector>
#include <iomanip> 

template <typename T>
class BinaryTree {

    private:

        int _depth;
        std::vector<std::vector<T>> _tree;


    public:

        // Methods
        BinaryTree(int depth = 0);
        void setDepth(int depth);
        int getDepth();
        long getSize(int index);
        void setNode(int level, int index, T value);
        T getNode(int level, int index) const;
        void display();
};

