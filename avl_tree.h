#pragma once

#include "node.h"

template<typename T1, typename T2, typename Comp, typename Allocator>
class avl_tree {
private:
    node<T1, T2>*   head;
    node<T1, T2>*   tail;
    Comp            comparator;
    typename Allocator::template rebind<node<T1, T2> >::other nodeAllocator;
    Allocator pairAllocator;

    typedef ft::pair<const T1, T2> value_type;

    // TODO: resolve providing tailNode to each new one
    // TODO: tail node height is 0
    node<T1, T2>* createTailNode()
    {
        node<T1, T2>* tailNode = nodeAllocator.allocate(1);
        new(tailNode) node<T1, T2>(tail, true);
        return tailNode;
    }

public:
    avl_tree()
    {
        head = createTailNode();
        tail = head;
    }

    size_t max_size() { return nodeAllocator.max_size(); }

    void eraseNode(node<T2, T2>* nodeToErase)
    {
        //pairAllocator.destroy(nodeToErase->pair);
        nodeAllocator.destroy(nodeToErase);
        //pairAllocator.deallocate(nodeToErase->pair, 1);
        nodeAllocator.deallocate(nodeToErase, 1);
    }

    node<T1, T2>* findReplacement(node<T1, T2>* nodeToDelete)
    {
        node<T1, T2>* currentNode = tail;
        if (nodeToDelete->l != tail)
        {
            currentNode = nodeToDelete->l;
            while (currentNode->r != tail)
            {
                currentNode = currentNode->r;
            }
        }
        else if (nodeToDelete->r != tail)
        {
            currentNode = nodeToDelete->r;
            while (currentNode->l != tail)
            {
                currentNode = currentNode->l;
            }
        }

        return currentNode;
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

    void calculateHeight(node<T1, T2>* node)
    {
        while (!node->isTail)
        {
            fixheight(node);
            node = node->parent;
        }
    }

    node<T1, T2>* createNode(const value_type& value)
    {
        node<T1, T2>* pNewNode = nodeAllocator.allocate(1);
        new(pNewNode) node<T1, T2>(value, tail);
        return pNewNode;
    }

    bool insert(node<T1, T2>* nodeToInsert) // TODO: make correct exit status
    {
        bool elInserted = false;
        if (head == tail) {
            head = nodeToInsert;
            return true;
        }

        node<T1, T2>* currentNode = head;
        while (!elInserted)
        {
            bool toLeftSide = comparator(nodeToInsert->pair.first, currentNode->pair.first);
            if (toLeftSide)
            {
                if (currentNode->l == tail)
                {
                    currentNode->l = nodeToInsert;
                    currentNode->l->parent = currentNode;
                    calculateHeight(currentNode->l);
                    elInserted = true;
                }
                else
                {
                    currentNode = currentNode->l;
                }
            }
            else
            {
                if (currentNode->r == tail)
                {
                    currentNode->r = nodeToInsert;
                    currentNode->r->parent = currentNode;
                    calculateHeight(currentNode->r);
                    elInserted = true;
                }
                else
                {
                    currentNode = currentNode->r;
                }
            }
        }
        //calculateHeight(currentNode->parent, currentNode);
        return true;
    }

    node<T1, T2>* prevEl(node<T1, T2>* comparable)
    {
        node<T1, T2>* currentNode = comparable;
        bool madeStepLeft = false;

        if (currentNode == tail) {
            return tail;
        }

        while (true)
        {
            if (currentNode->l != tail && !madeStepLeft) {
                if (!comparator(currentNode->pair.first, currentNode->l->pair.first)) {
                    currentNode = currentNode->l;
                    madeStepLeft = true;
                    if (currentNode->r == tail) {
                        return currentNode;
                    }
                }
            }
            else if (currentNode->r != tail && madeStepLeft) {
                if (comparator(currentNode->pair.first, currentNode->r->pair.first)) {
                    currentNode = currentNode->r;
                }
                else return currentNode;
            }
            else if (!madeStepLeft) {
                if (
                        currentNode->parent != tail &&
                        !comparator(currentNode->pair.first, currentNode->parent->pair.first)
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

        if (currentNode == tail) {
            return tail;
        }

        while (true)
        {
            if (currentNode->r != tail && !madeStepRight) {
                if (comparator(currentNode->pair.first, currentNode->r->pair.first)) {
                    currentNode = currentNode->r;
                    madeStepRight = true;
                    if (currentNode->l == tail) {
                        return currentNode;
                    }
                }
            }
            else if (currentNode->l != tail && madeStepRight) {
                if (!comparator(currentNode->pair.first, currentNode->l->pair.first)) {
                    currentNode = currentNode->l;
                }
                else return currentNode;
            }
            else if (!madeStepRight) {
                if (
                        currentNode->parent != tail &&
                        comparator(currentNode->pair.first, currentNode->parent->pair.first)
                    )
                {
                        return currentNode->parent;
                }
                else return tail;
            } else return currentNode;
        }
    }

    bool isKeysEqual(const T1& firstKey, const T2& secondKey) const
    {
        return !comparator(firstKey, secondKey)
               && !comparator(secondKey, firstKey);
    }

    size_t height(node<T1, T2>* node)
    {
        return node?node->height:0;
    }

    int bfactor(node<T1, T2>* node)
    {
        return height(node->r)-height(node->l);
    }

    void fixheight(node<T1, T2>* p)
    {
        unsigned char hl = height(p->l);
        unsigned char hr = height(p->r);
        p->height = (hl>hr?hl:hr)+1;
    }

    node<T1, T2>* getHeadNode() { return head; }
    node<T1, T2>* getTailNode() { return tail; }
    void setHeadNode(node<T1, T2>* newHeadNode) {head = newHeadNode;}
};
