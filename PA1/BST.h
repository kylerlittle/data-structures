/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *
 */

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
#include <algorithm>        // std::max
using namespace std;

/*
 *  Node data structure for single tree node
 */ 
template <class T>
class Node {
    private:
        T _value;
        Node<T> * _left;
        Node<T> * _right;
    public:
        Node(T val) : _value{val} {
            _left = nullptr;
            _right = nullptr;
        }
        
        // Consider where and when I should pass T by reference
        T getValue() const {
            return _value;
        }
        
        Node<T> *& getLeft() {
            return _left;
        }
        Node<T> *& getRight() {
            return _right;
        }
};


/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {
    private:
    Node<T> *root;
    
    protected:      
        void destroyTree(Node<T> *& pTree) {
            if (pTree != nullptr) {
                destroyTree(pTree->getLeft());
                destroyTree(pTree->getRight());
                delete pTree;
            }
        }
        
        // Allocate a new Node, constructed with val, return pointer to memory
        Node<T> * createNode(T val) {
            return new Node<T>{val};
        }
        
        // Recursively add a node to BST
        void add(T val, Node<T> *& pTree) {
            if (pTree == nullptr) {
                pTree = createNode(val);        // pTree is passed by reference so that _root, _left, _or _right are set correctly
            } else {
                if (pTree->getValue() >= val)   // value is less than current node's value
                    add(val, pTree->getLeft());
                else                            // value is greater than current node's value
                    add(val, pTree->getRight());
            }
        }
        
        // Recursively print off the preorder of the BST
        // Pass pTree by reference to save some memory on the stack
        void printPreOrder(Node<T> *& pTree) {
            if (pTree != nullptr) {                     // Tells printPreOrder when to stop recursing
                cout << pTree->getValue() << " ";       // Print value to screen.
                printPreOrder(pTree->getLeft());
                printPreOrder(pTree->getRight());
            }
        }
        
        // Recursively calculates the height of the BST
        // I am defining height to be the number of edges (longest path) from
        // root to the deepest node in the tree. I will let a single node (just
        // the root have height 1).
        int height(Node<T> *& pTree) {
            if (pTree == nullptr)   // BASE CASE
                return 0;           // This tree doesn't go down any further, so it adds 0 to the height.
            else                    // Return max depth of the subtree we're currently looking at
                return max(height(pTree->getLeft()), height(pTree->getRight())) + 1;    // +1 ensures solo node has height 1
        }

    public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        this->destroyTree(root);
        root = nullptr;
    }
        
    void add(T val) {
        add(val, root);
    }

    void print() {
	this->printPreOrder();
    }

    void printPreOrder() {
        this->printPreOrder(root);
    }

    int nodesCount() {
    }

    int height() {
        return height(root);
    }
};

#endif
