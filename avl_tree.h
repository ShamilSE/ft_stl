#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp, typename Allocator>
class avl_tree {
private:
    node<T1, T2>*   head;
    Comp            comparator;
public:
    avl_tree()
    {
        head = nullptr;
        std::cout << "avl constructor 1" << std::endl;
    }

    void insert(ft::pair<T1, T2>& new_pair)
    {
        bool toLeftSide = false;
        bool elInserted = false;
        if (head == nullptr) {
            head = new node<T1, T2>(new_pair);
            return;
        }

        node<T1, T2>* currentNode = head;
        while (!elInserted) {
            toLeftSide = comparator(new_pair.first, currentNode->pair->first);
            if (toLeftSide) {
                if (currentNode->l == nullptr) {
                    currentNode->l = new node<T1, T2>(new_pair);
                    currentNode->l->parent = currentNode;
                    elInserted = true;
                }
                else {
                    currentNode = currentNode->l;
                }
            }
            else {
                if (currentNode->r == nullptr) {
                    currentNode->r = new node<T1, T2>(new_pair);
                    currentNode->r->parent = currentNode;
                    elInserted = true;
                }
                else {
                    currentNode = currentNode->r;
                }
            }
        }
    }

    node<T1, T2> getHeadNode() const {return head;}
};
