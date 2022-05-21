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
        // decide where to search for replacement
        bool toLeftSide = nodeToDelete->r->height > nodeToDelete->r->height ;
        if (toLeftSide && nodeToDelete->l != tail)
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
            balance(node);
            node = node->parent;
        }
    }

    node<T1, T2>* createNode(const value_type& value)
    {
        node<T1, T2>* pNewNode = nodeAllocator.allocate(1);
        new(pNewNode) node<T1, T2>(value, tail);
        return pNewNode;
    }

    /*
     *  в правом поддереве находим узел min с наименьшим ключом и заменяем удаляемый узел p на найденный узел min.
     */
    bool erase(node<T1, T2>* nodeToDelete)
    {
        if (nodeToDelete == tail) { return false; }

        if (nodeToDelete->r == tail && nodeToDelete == tail) {

            if (nodeToDelete->parent != tail)
            {
                if (
                        nodeToDelete->parent->l != tail &&
                        isKeysEqual(nodeToDelete->parent->l->pair.first, nodeToDelete->pair.first)
                        )
                {
                    nodeToDelete->parent->l = tail;
                }
                else
                {
                    nodeToDelete->parent->r = tail;
                }
            }
            if (nodeToDelete == head) {
                head = tail;
            }
            eraseNode(nodeToDelete);
            return true;
        }

        node<T1, T2>* replacement = findReplacement(nodeToDelete);
        if (nodeToDelete->parent != tail)
        {
            // if nodeToDelete is right (position) child
            if (isKeysEqual(nodeToDelete->parent->r->pair.first, nodeToDelete->pair.first))
            {
                nodeToDelete->parent->r = replacement;
                replacement->parent = nodeToDelete->parent;
            }
            else
            {
                nodeToDelete->parent->l = replacement;
                replacement->parent = nodeToDelete->parent;
            }
            eraseNode(nodeToDelete);
            calculateHeight(replacement);
            return true;
        }
        else // deleting head
        {
            node<T1, T2>* tmpHead = head;
            head = replacement;
            if (head != tmpHead->r) {
                head->r = tmpHead->r;
            }
            if (head != tmpHead->l) {
                head->l = tmpHead->l;
            }
            head->parent = tail;
            eraseNode(tmpHead);
            balance(head);
            return true;
        }
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
        return node == tail ? node->height : 0;
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

    node<T1, T2>* balance(node<T1, T2>* p) // балансировка узла p
    {
        fixheight(p);
        if( bfactor(p)==2 )
        {
            if( bfactor(p->r) < 0 )
                p->r = rotateright(p->r);
            return rotateleft(p);
        }
        if( bfactor(p)==-2 )
        {
            if( bfactor(p->l) > 0  )
                p->l = rotateleft(p->l);
            return rotateright(p);
        }
        return p; // балансировка не нужна
    }

    node<T1, T2>* rotateright(node<T1, T2>* p) // правый поворот вокруг p
    {
        node<T1, T2>* q = p->l;
        if (p == head) {
            head = q;
            head->parent = tail;
        }
        else {
            p->parent->l = q;
            q->parent = p->parent;
        }
        p->l = q->r;
        q->r = p;
        p->parent = q;
        fixheight(p);
        fixheight(q);
        return q;
    }

    node<T1, T2>* rotateleft(node<T1, T2>* q) // левый поворот вокруг q
    {
        node<T1, T2>* p = q->r;
        if (q == head) {
            head = p;
            head->parent = tail;
        }
        else {
            q->parent->r = p;
            p->parent = q->parent;
        }
        q->r = p->l;
        p->l = q;
        q->parent = p;
        fixheight(q);
        fixheight(p);
        return p;
    }

    node<T1, T2>* getHeadNode() { return head; }
    node<T1, T2>* getTailNode() { return tail; }
    void setHeadNode(node<T1, T2>* newHeadNode) {head = newHeadNode;}
};
