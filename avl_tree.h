#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp, typename Allocator>
class avl_tree {
private:
    node<T1, T2>*   head;
    node<T1, T2>*   tail;
    Comp            comparator;

    node<T1, T2>* createTailNode()
    {
        node<T1, T2>* tailNode = new node<T1, T2>(tail, true);
        return tailNode;
    }

public:
    avl_tree()
    {
        head = nullptr;
        tail = createTailNode();
    }

    node<T1, T2>* getFirstNode() {
        node<T1, T2>* currentNode = head;

        if (currentNode->l == tail) {
            return head;
        }

        while (currentNode->l != tail) {
            currentNode = prevEl(currentNode);
        }
        return currentNode;
    }

    void insert(ft::pair<T1, T2>& new_pair)
    {
        bool elInserted = false;
        if (head == nullptr) {
            head = new node<T1, T2>(new_pair, tail);
            return;
        }

        node<T1, T2>* currentNode = head;
        while (!elInserted) {
            bool toLeftSide = comparator(new_pair.first, currentNode->pair->first);
            if (toLeftSide) {
                if (currentNode->l == tail) {
                    currentNode->l = new node<T1, T2>(new_pair, tail);
                    currentNode->l->parent = currentNode;
                    elInserted = true;
                }
                else {
                    currentNode = currentNode->l;
                }
            }
            else {
                if (currentNode->r == tail) {
                    currentNode->r = new node<T1, T2>(new_pair, tail);
                    currentNode->r->parent = currentNode;
                    elInserted = true;
                }
                else {
                    currentNode = currentNode->r;
                }
            }
        }
    }

    node<T1, T2>* prevEl(node<T1, T2>* comparable)
    {
        node<T1, T2>* currentNode = comparable;
        bool madeStepLeft = false;

        if (currentNode == nullptr) {
            return tail;
        }

        while (true)
        {
            if (currentNode->l != tail && !madeStepLeft) {
                if (!comparator(currentNode->pair->first, currentNode->l->pair->first)) {
                    currentNode = currentNode->l;
                    madeStepLeft = true;
                    if (currentNode->r == tail) {
                        return currentNode;
                    }
                }
            }
            else if (currentNode->r != tail && madeStepLeft) {
                if (comparator(currentNode->pair->first, currentNode->r->pair->first)) {
                    currentNode = currentNode->r;
                }
                else return currentNode;
            }
            else if (!madeStepLeft) {
                if (
                        currentNode->parent != nullptr &&
                        !comparator(currentNode->pair->first, currentNode->parent->pair->first)
                        )
                {
                    return currentNode->parent;
                }
                else return tail;
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
            if (currentNode->r != tail && !madeStepRight) {
                if (comparator(currentNode->pair->first, currentNode->r->pair->first)) {
                    currentNode = currentNode->r;
                    madeStepRight = true;
                    if (currentNode->l == tail) {
                        return currentNode;
                    }
                }
            }
            else if (currentNode->l != tail && madeStepRight) {
                if (!comparator(currentNode->pair->first, currentNode->l->pair->first)) {
                    currentNode = currentNode->l;
                }
                else return currentNode;
            }
            else if (!madeStepRight) {
                if (
                        currentNode->parent != nullptr &&
                        comparator(currentNode->pair->first, currentNode->parent->pair->first)
                    )
                {
                        return currentNode->parent;
                }
                else return tail;
            } else return currentNode;
        }
    }

    node<T1, T2>* getHeadNode() { return head; }
    node<T1, T2>* getTailNode() { return tail; }
};
