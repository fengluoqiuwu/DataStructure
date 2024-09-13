//
// Created by Eden_ on 2024/9/13.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"

template <typename T>
class AVL_tree : protected binary_search_tree<T,size_t> {

};

#include "AVL_tree.tpp"

#endif //AVL_TREE_H
