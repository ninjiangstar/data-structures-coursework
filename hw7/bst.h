// bst.h
// Implements a(n unbalanced) BST storing Key,Value pairs

#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/* -----------------------------------------------------
* Regular Binary Tree Nodes
------------------------------------------------------*/

template <class KeyType, class ValueType>
class Node {
public:
    Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p) // construct node
    : _item(k, v)
    { _parent = p; _left = _right = NULL; } // the default is to create new nodes as leaves

    virtual ~Node() // virtual destructor: destruct inherited class first
    { }

    std::pair<const KeyType, ValueType> const & getItem () const // return reference to pair-value of node
    { return _item; }

    std::pair<const KeyType, ValueType> & getItem () // just in case the previous didn't work?
    { return _item; }

    const KeyType & getKey () const // get key of node
    { return _item.first; }

    const ValueType & getValue () const // get value of node
    { return _item.second; }

    
    // the next three functions are virtual because for AVL-Trees
    
    // VIRTUAL GETTERS
    virtual Node<KeyType, ValueType> *getParent () const // get parent pointer
    { return _parent; }

    virtual Node<KeyType, ValueType> *getLeft () const // get left pointer
    { return _left; }

    virtual Node<KeyType, ValueType> *getRight () const // get right pointer
    { return _right; }

    // SETTERS
    void setParent (Node<KeyType, ValueType> *p)
    { _parent = p; }

    void setLeft (Node<KeyType, ValueType> *l)
    { _left = l; }

    void setRight (Node<KeyType, ValueType> *r)
    { _right = r; }

    void setValue (const ValueType &v)
    { _item.second = v; }

protected:
    std::pair<const KeyType, ValueType> _item;
    Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
* Regular Binary Search Tree
------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
protected:
    Node<KeyType, ValueType> *root; // Main data member of the class

public:
    BinarySearchTree () { root = NULL; } // constructor
    ~BinarySearchTree () { deleteAll (root); } // destructor

/*
Prints the entire tree structure in a nice format.
It will denote subtrees in [] brackets.
This could be helpful if you want to debug your functions. */

    void print () const
    { 
        printRoot (root);
        std::cout << "\n";
    }

    // unbalanced binary search tree
    virtual void insert(const std::pair<const KeyType, ValueType>& new_item)
    {
        if(root == NULL)
        {
            Node<KeyType,ValueType>* temp = new Node<KeyType,ValueType>(new_item.first, new_item.second, NULL);
            root = temp;
        } 
        else insert(new_item, root);
    }

    virtual void remove(const KeyType &toRemove)
    {
        // 1. identify removal node based on key
        Node<KeyType, ValueType>* toDelete = this->internalFind(toRemove);
        if(!toDelete) return; // couldn't find item
        Node<KeyType, ValueType>* successor = toDelete->getLeft();

        if(toDelete->getLeft() && toDelete->getRight())
        {
            // 2. get maximum node of left subtree
            while(successor->getRight())
            {
                successor = successor->getRight();
            }

            // 3. re-attach left-child of rightmost node
            if(successor->getParent() != toDelete)
            {
                successor->getParent()->setRight(successor->getLeft());
                successor->getLeft()->setParent(successor->getParent());
            }

            // 4. replace removed node with rightmost node
            replaceNodeInParent(toDelete, successor); // toDelete is now gone

        }
        else if(toDelete->getLeft()) // only left child
        {
            replaceNodeInParent(toDelete, toDelete->getLeft());
        }
        else if(toDelete->getRight()) // only right child
        {
            replaceNodeInParent(toDelete, toDelete->getRight());
        }
        else // no child
        {
            replaceNodeInParent(toDelete, NULL);
        }
        
    }


    // An In-Order iterator:
    class iterator {
    public:
        friend class BinarySearchTree<KeyType, ValueType>;

        std::pair<const KeyType,ValueType>& operator*()
        { return curr->getItem();  }

        std::pair<const KeyType,ValueType>* operator->() 
        { return &(curr->getItem()); }

        // OPERATOR OVERLOAD
        bool operator==(const iterator& rhs) const // checks if this has same value as rhs
        { return curr == rhs.curr; }

        bool operator!=(const iterator& rhs) const // checks if this has different value than rhs
        { return curr != rhs.curr; }

        iterator& operator++() // advances the iterator's location using in-order sequencing
        {
            if(curr == NULL) return *this; // if curr == NULL
            if(curr->getRight() != NULL)
            { // if right side exists, traverse right
                curr = curr->getRight(); // set current to the right side
                while(curr->getLeft() != NULL)
                { // traverse all the way to the left
                    curr = curr->getLeft();
                }
                return *this;
            }

            while(true)
            {
                if(curr->getParent() == NULL)
                { // check if traversal ended
                    curr = NULL;
                    return *this;
                }

                if(curr->getParent()->getLeft() == curr)
                { // coming from the left
                    curr = curr->getParent();
                    return *this;
                }

                curr = curr->getParent(); // traverse upwards, left side complete.
            }
        }

    protected:
        iterator(Node<KeyType,ValueType>* ptr) : curr(ptr) {}; // initialize internal members of iterator
        Node<KeyType, ValueType>* curr;
    };

    iterator begin() const // return iterator to "smallest" item in the tree
    {
        Node<KeyType, ValueType>* curr = root;
        if(curr)
        {
            while(curr->getLeft())
            {
                curr = curr->getLeft();
            }
        }

        iterator lli(curr);
        return lli;
    }
    
    iterator end() const // returns an iterator whose value means INVALID (NULL)
    {
        iterator lle(NULL);
        return lle;
    }

    // END of iterator implementation

protected:
    // insert recursive function
    virtual void insert(const std::pair<const KeyType, ValueType>& new_item, Node<KeyType,ValueType>* root)
    {
        if(new_item.first <= root->getKey())
        {
            if(root->getLeft()) insert(new_item, root->getLeft());
            else 
            {
                Node<KeyType,ValueType>* temp = new Node<KeyType,ValueType>(new_item.first, new_item.second, root);
                root->setLeft(temp);
            }
        }
        else if(new_item.first > root->getKey())
        {
            if(root->getRight()) insert(new_item, root->getRight());
            else 
            {
                Node<KeyType,ValueType>* temp = new Node<KeyType,ValueType>(new_item.first, new_item.second, root);
                root->setRight(temp);
            }
        }
    }

    void replaceNodeInParent(Node<KeyType, ValueType>* self, Node<KeyType, ValueType>* successor)
    {
        // 1. attach parent branch
        if (self->getParent())
        {
            if(self == self->getParent()->getLeft())
                self->getParent()->setLeft(successor);
            else if(self == self->getParent()->getRight())
                self->getParent()->setRight(successor);
        }
        else // is potentially the root?
        {
            if(self == this->root) this->root = successor;
        }

        if (successor)
        {
            // 2. re-attach children
            if (successor->getParent() != self)
            {
                if(self->getLeft()) self->getLeft()->setParent(successor);
                successor->setLeft(self->getLeft());
            }
            if(self->getLeft()) // left side exists
            {
               if(self->getRight()) self->getRight()->setParent(successor);
               successor->setRight(self->getRight());
            }
            
            // 3. set successor's parent
            successor->setParent(self->getParent());
        }

        delete self; // hard delete
    }

    virtual Node<KeyType, ValueType>* internalFind(const KeyType& k) const
    { // helper function to find node with given key, k, and return pointer of node
        Node<KeyType, ValueType> *curr = root;
        while (curr) 
        {
            if (curr->getKey() == k) 
            {
                return curr;
            } 
            else if (k < curr->getKey()) 
            {
                curr = curr->getLeft();
            } 
            else 
            {
                curr = curr->getRight();
            }
        }
        return NULL;
    }

    void printRoot (Node<KeyType, ValueType> *r) const // helper function to print tree's contents
    {
        if (r != NULL)
        {
            std::cout << "[";
            printRoot (r->getLeft());
            std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
            printRoot (r->getRight());
            std::cout << "]";
        }
    }

    void deleteAll (Node<KeyType, ValueType> *r) // helper function to delete all items
    {
        if (r != NULL)
        {
            deleteAll (r->getLeft());
            deleteAll (r->getRight());
            delete r;
        }
    }
};

#endif
