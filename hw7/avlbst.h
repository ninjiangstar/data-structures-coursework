/*
* avlbst.h
*
* Date        Author    Notes
* =====================================================
* 2014-04-14  Kempe     Initial version
* 2015-04-06  Redekopp  Updated formatting and removed
*                         KeyExistsException
* 2016-03-31  Cote      Modify for AVL Trees
*/
#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

// inheriting from Node
template <class KeyType, class ValueType>
class AVLNode : public Node<KeyType, ValueType>
{
public:
    AVLNode (KeyType k, ValueType v, AVLNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { height = 0; }

    virtual ~AVLNode () {}

    int getHeight () const
    { return height; }

    void setHeight (int h)
    { height = h; }

    virtual AVLNode<KeyType, ValueType> *getParent () const
    { return (AVLNode<KeyType,ValueType>*) this->_parent; }

    virtual AVLNode<KeyType, ValueType> *getLeft () const
    { return (AVLNode<KeyType,ValueType>*) this->_left; }

    virtual AVLNode<KeyType, ValueType> *getRight () const
    { return (AVLNode<KeyType,ValueType>*) this->_right; }

protected:
    int height;
};

/* -----------------------------------------------------
* AVL Search Tree
------------------------------------------------------*/

template <class KeyType, class ValueType>
class AVLTree : public BinarySearchTree<KeyType, ValueType>
{

public:
    // unbalanced binary search tree
    virtual void insert(const std::pair<const KeyType, ValueType>& new_item)
    {
        AVLNode<KeyType, ValueType>* pseudoRoot = static_cast<AVLNode<KeyType, ValueType>*>(this->root);
        if(pseudoRoot == NULL)
        {
            AVLNode<KeyType,ValueType>* temp = new AVLNode<KeyType,ValueType>(new_item.first, new_item.second, NULL);
            this->root = temp;
        } 
        else insert(new_item, pseudoRoot);
    }

    virtual void remove(const KeyType &toRemove)
    {
        // 1. identify removal node based on key
        AVLNode<KeyType, ValueType>* toDelete = static_cast<AVLNode<KeyType, ValueType>*>(this->internalFind(toRemove));
        if(!toDelete) throw std::exception(); // couldn't find item
        AVLNode<KeyType, ValueType>* parent = toDelete->getParent();

        // both children subtrees must be accounted for
        if(toDelete->getLeft() && toDelete->getRight())
        {
            AVLNode<KeyType, ValueType>* successor = toDelete->getLeft();

            // 2. get maximum node of left subtree
            while(successor->getRight()) successor = successor->getRight();
            
            AVLNode<KeyType, ValueType>* beginBalance = successor->getParent();

            // 3. re-attach left-child of maximum node
            if(successor->getParent() != toDelete) 
            {
                successor->getParent()->setRight(successor->getLeft());
            }
            else beginBalance = successor;

            // 4. replace removed node with rightmost node
            this->replaceNodeInParent(toDelete, successor); // toDelete is now gone
            balance(beginBalance);

        }
        else if(toDelete->getLeft()) // only left child
        {
            AVLNode<KeyType, ValueType>* leftNode = toDelete->getLeft();
            this->replaceNodeInParent(toDelete, leftNode);
            balance(leftNode);
        }
        else if(toDelete->getRight()) // only right child
        {
            AVLNode<KeyType, ValueType>* rightNode = toDelete->getRight();
            this->replaceNodeInParent(toDelete, rightNode);
            balance(rightNode);
        }
        else // no child
        {
            this->replaceNodeInParent(toDelete, NULL);
            balance(parent);
        }
        
    }

    AVLNode<KeyType, ValueType> * find(const KeyType& k) const
    {
        return static_cast<AVLNode<KeyType, ValueType>*>(this->internalFind(k));
    }


protected:
    // insert recursive function
    virtual void insert(const std::pair<const KeyType, ValueType>& new_item, AVLNode<KeyType,ValueType>* root)
    {
        if(new_item.first == root->getKey())
        {
            throw std::exception();
        }
        else if(new_item.first < root->getKey())
        {
            if(root->getLeft()) insert(new_item, root->getLeft());
            else 
            {
                AVLNode<KeyType,ValueType>* temp = new AVLNode<KeyType,ValueType>(new_item.first, new_item.second, root);
                root->setLeft(temp);
                balance(temp->getParent());
            }
        }
        else if(new_item.first > root->getKey())
        {
            if(root->getRight()) insert(new_item, root->getRight());
            else 
            {
                AVLNode<KeyType,ValueType>* temp = new AVLNode<KeyType,ValueType>(new_item.first, new_item.second, root);
                root->setRight(temp);
                balance(temp->getParent());
            }
        }
    }


    // ROTATION CASES
    void rotateLeftLeftCase (AVLNode<KeyType, ValueType> * node)
    {
        rotateRight(node);
    }
    void rotateRightRightCase (AVLNode<KeyType, ValueType> * node)
    {
        rotateLeft(node);
    }
    void rotateLeftRightCase (AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return;
        if(!node->getLeft()) return;
        rotateLeft(node->getLeft());
        rotateLeftLeftCase (node);
    }
    void rotateRightLeftCase (AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return;
        if(!node->getRight()) return;
        rotateRight(node->getRight());
        rotateRightRightCase (node);
    }

    // BASIC ROTATIONS
    void rotateLeft (AVLNode<KeyType, ValueType> * nodeA)
    {
        if(!nodeA) return;
        /*
             A            B
            / \          / \
           1   B   ->   A   3
              / \      / \
             2   3    1   2
        */
        AVLNode<KeyType, ValueType> * nodeB = nodeA->getRight();
        if(!nodeB) return; // secondary node doesn't exist, can't rotate

        if(nodeA->getParent()) // set parent
        {
            if(nodeA == nodeA->getParent()->getLeft())
                nodeA->getParent()->setLeft(nodeB);
            else nodeA->getParent()->setRight(nodeB);
        }
        else // might be root?
        {
            if(nodeA == this->root)
                this->root = nodeB;
        }
        nodeB->setParent(nodeA->getParent());

        AVLNode<KeyType, ValueType> * nodeTwo = nodeB->getLeft();

        // reattach
        nodeA->setRight(nodeTwo);
        if(nodeTwo) nodeTwo->setParent(nodeA);
        nodeB->setLeft(nodeA);
        nodeA->setParent(nodeB);

        nodeA->setHeight(estHeight(nodeA));
        nodeB->setHeight(estHeight(nodeB));
    }
    void rotateRight (AVLNode<KeyType, ValueType> * nodeA)
    {
        if(!nodeA) return;
        /*
               A            B
              / \          / \
             B   3   ->   1   A
            / \              / \
           1   2            2   3
        */
        AVLNode<KeyType, ValueType> * nodeB = nodeA->getLeft();
        if(!nodeB) return; // secondary node doesn't exist, can't rotate

        if(nodeA->getParent()) // set parent
        {
            if(nodeA == nodeA->getParent()->getLeft())
                nodeA->getParent()->setLeft(nodeB);
            else nodeA->getParent()->setRight(nodeB);
        }
        else // might be root?
        {
            if(nodeA == this->root)
                this->root = nodeB;
        }
        nodeB->setParent(nodeA->getParent());

        AVLNode<KeyType, ValueType> * nodeTwo = nodeB->getRight();

        // reattach
        nodeA->setLeft(nodeTwo);
        if(nodeTwo) nodeTwo->setParent(nodeA);
        nodeB->setRight(nodeA);
        nodeA->setParent(nodeB);

        nodeA->setHeight(estHeight(nodeA));
        nodeB->setHeight(estHeight(nodeB));
    }

    // BALANCING FUNCTIONS

    void balance(AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return; // reached above root, fully balanced
        fixHeights(node);

        balanceHelper(node);
    }

    // recursive helper for balance() function
    void balanceHelper(AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return;
        node->setHeight(estHeight(node));

        if(balanceFactor(node) < -1) // left subtree increased
        {
            if(balanceFactor(node->getLeft()) > 0) // left, right
                rotateLeftRightCase(node);
            else // left, left
                rotateLeftLeftCase(node);
        }
        else if(balanceFactor(node) > 1) // right child height increased
        {
            if(balanceFactor(node->getRight()) < 0) // right, left
                rotateRightLeftCase(node);
            else // right, right
                rotateRightRightCase(node);
        }

        balanceHelper(node->getParent()); // balance the next parent node
    }

    // calculate balance factor to decide rotation
    int balanceFactor(AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return 0; // is leaf node

        int leftHeight, rightHeight;

        if(!node->getLeft()) leftHeight = 0;
        else leftHeight = node->getLeft()->getHeight();

        if(!node->getRight()) rightHeight = 0;
        else rightHeight = node->getRight()->getHeight(); 

        return rightHeight - leftHeight;
    }

    // calculate height based on child's height
    int estHeight(AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return 0;
        int leftHeight, rightHeight;

        if(!node->getLeft()) leftHeight = 0;
        else leftHeight = node->getLeft()->getHeight();

        if(!node->getRight()) rightHeight = 0;
        else rightHeight = node->getRight()->getHeight(); 

        if(leftHeight >= rightHeight)
            return leftHeight + 1;
        else return rightHeight + 1;
    }

    // regenerate heights for node and its children
    int fixHeights(AVLNode<KeyType, ValueType> * node)
    {
        if(!node) return 0;
        int leftHeight, rightHeight;

        // post-order fix heights
        leftHeight = fixHeights(node->getLeft());
        rightHeight = fixHeights(node->getRight());

        if(leftHeight <= rightHeight)
        {
            node->setHeight(rightHeight + 1);
            return rightHeight + 1;
        }
        else
        {
            node->setHeight(leftHeight + 1);
            return rightHeight + 1;
        }
    }

};

#endif