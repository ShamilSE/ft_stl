#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp, typename Allocator>
class avl_tree {
private:
    node<T1, T2>*   head;
    node<T1, T2>*   tail;
    Comp            comparator;
public:
    avl_tree()
    {
        head = nullptr;
        tail = new node<T1, T2>;
    }

    void insert(ft::pair<T1, T2>& new_pair)
    {
        bool elInserted = false;
        if (head == nullptr) {
            head = new node<T1, T2>(new_pair);
            return;
        }

        node<T1, T2>* currentNode = head;
        while (!elInserted) {
            bool toLeftSide = comparator(new_pair.first, currentNode->pair->first);
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

    node<T1, T2>* nextEl(node<T1, T2>* comparable)
    {
        node<T1, T2>* currentNode = comparable;
        bool madeStepRight = false;

        if (currentNode == nullptr) {
            return tail;
        }

        while (true)
        {
            if (currentNode->r != nullptr && !madeStepRight) {
                if (comparator(currentNode->pair->first, currentNode->r->pair->first)) {
                    currentNode = currentNode->r;
                    madeStepRight = true;
                    if (currentNode->l == nullptr) {
                        return currentNode;
                    }
                }
            }
            else if (currentNode->l != nullptr && madeStepRight) {
                if (!comparator(currentNode->pair->first, currentNode->l->pair->first)) {
                    currentNode = currentNode->l;
                }
                else return currentNode;
            }
            else if (!madeStepRight) {
                if (
                        currentNode->parent != nullptr
                        && comparator(currentNode->pair->first, currentNode->parent->pair->first)
                    )
                {
                        return currentNode->parent;
                }
                else return tail;
            }
            else return currentNode;
        }
    }

    node<T1, T2>* getHeadNode() { return head; }
    node<T1, T2>* getTailNode() { return tail; }
};
