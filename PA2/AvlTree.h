#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector>
#include <algorithm> // For max() function
using namespace std;

#define ALLOWED_IMBALANCE 1

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root( NULL )
      { }

    AvlTree( const AvlTree & rhs ) : root( NULL )
    {
        *this = rhs;
    }

    ~AvlTree( )
    {
       cout << " [!] Destructor called." << endl;
       makeEmpty( );
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException( );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     *  TODO: Implement
     */
    bool isEmpty( ) const
    {
      return (root == nullptr);
    }

    /**
     * Return number of elements in tree.
     */
    int size( )
    {
      return size( root );
    }

    /**
     * Return height of tree.
     *  Null nodes are height -1
     */
    int height( )
    {
      return height( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printInOrder( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printInOrder( ) const
    {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
        } else {
            //cout << "  [!] Printing In Order";
            printInOrder( root );
        }
    }

    /**
     * Print the tree contents in pre order.
     */
    void printPreOrder( ) const
    {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
        } else {
            //cout << "   [!] Printing Pre order";
            printPreOrder( root );
        }
    }

    /**
     * Print the tree contents in post order.
     */
    void printPostOrder( ) const
    {
        if( isEmpty( ) ) {
            cout << "Empty tree" << endl;
        } else {
            //cout << "  [!] Printing post order";
            printPostOrder( root );
        }
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
        root = nullptr;     // ensure root is now null
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert vector of x's into the tree; duplicates are ignored.
     */
    void insert( vector<Comparable> vals)
    {
      for( auto x : vals ) {
        insert( x, root );
      }
    }
     

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     *  TODO: Implement
     */
    void remove( const Comparable & x )
    {
      remove(x, root);  // call internal method to remove; will automatically check if x is in tree
    }


    /**
     * Deep copy. - or copy assignment operator
     *  Will be in part II
     */
    const AvlTree & operator=( const AvlTree & rhs )
    {
      cout << " [!] Copy *assignment* operator called." << endl;
      return *this;
    }


/*****************************************************************************/
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & theElement, AvlNode *lt,
                                                AvlNode *rt, int h = 0 )
          : element( theElement ), left( lt ), right( rt ), height( h ) { }
    };

    AvlNode *root;

    /**
     * Internal method to count nodes in tree
     *  TODO: Implement
     */
    int size( AvlNode * & t )
    {
      if (t == nullptr)
	return 0;  // null node counts zero
      else
	return (size(t->left) + size(t->right) + 1);  // +1 accounts for current node
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     *  TODO: Implement
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
      if (t == nullptr) 
	t = new AvlNode{x, nullptr, nullptr};
      else if (x < t->element)
	insert(x, t->left);
      else if (x > t->element)
	insert(x, t->right);

      balance(t);
    }

    /**
     * Internal method to remove x from the tree
     * Done recursively, so as to rebalance on the way back up
     * It is assumed that x is in the tree
     */
    void remove (const Comparable & x, AvlNode * & t) {
      if (t == nullptr) { return; }   // necessary for case where removing root with no right subtree; also simply returns if x is not found
      else if (x < t->element) { remove(x, t->left); }
      else if (x > t->element) { remove(x, t->right); }
      else if (t->right != nullptr && t->left != nullptr) {
	// If we make it to this point, x has been found and has two children
	t->element = findMin(t->right)->element;  // replace data with data of smallest node in right subtree
	remove(t->element, t->right);  // remove the stolen node since we're guaranteed it has at most one child (right child)
      } else { // methods for removing x with one or zero children are same 
	AvlNode * toDelete = t;
	t = (t->right == nullptr) ? t->left : t->right;  // set t to point at whichever is not nullptr
	delete toDelete;
      }

      balance(t);
    }

    /**
     * Internal method to balance a tree t
     * If height magnitude of difference between left and right subtrees of t is greater than 1,
     * then a rotation is necessary.   
     * Note that when checking to see if insertion was *-left or *-right, it's unnecessary to also check
     * for equality in heights; if there were equality in heights after an insertion, then there would have been
     * an imbalance already. If using balance after a deletion, then this actually saves some work by only doing
     * a single rotation when the heights on the heavier side are equal (or within the allowed imbalance).
    */
    void balance(AvlNode * & t) {
      if (t == nullptr) { return; }
      
      if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {   // i.e. left side is heavier (implies left has at least height 2), so left is not null
	if (height(t->left->left) < height(t->left->right))  // left-right case
	  doubleWithLeftChild(t);
	else  // left-left insertion
	  rotateWithLeftChild(t);
      } else {
        if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)  // i.e. right side is heavier (implies right has at least height 2), so right is not null
	  if (height(t->right->right) < height(t->right->left)) // right-left case
	    doubleWithRightChild(t);
	  else
	    rotateWithRightChild(t);
      }
      t->height = height(t);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     *  You'll need this for deletes
     *  TODO: Implement
     */
    AvlNode * findMin( AvlNode *t ) const
    {
      while (t->left != nullptr) { t = t->left; }     // go all the way left 
      return t; // t is now the smallest node
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     *  TODO: Implement
     */
    AvlNode * findMax( AvlNode *t ) const
    {
      while (t->right != nullptr) { t = t->right; }    // go all the way right
      return t;  // t is now the max node
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     *  TODO: Implement
     */
    bool contains( const Comparable & x, AvlNode *t ) const
    {
      while (t != nullptr) {
	if (x == t->element)
	  return true;
	else
	  t = (x < t->element) ? t->left : t->right;
      }
      return false;    // Lolz
    }

/******************************************************/

    /**
     * Internal method to make subtree empty.
     *  TODO: implement for destructor
     * 
     */
    void makeEmpty( AvlNode * & t )
    {
      if (t != nullptr) {
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;    // deleting last ensures t has no children; we are safe to remove
      }
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     *  TODO: Implement
     */
    void printInOrder( AvlNode *t ) const
    {
      if (t != nullptr) {
	printInOrder(t->left);
	cout << t->element << " ";
	printInOrder(t->right);
      }
    }

    /**
     * Internal method to print a subtree rooted at t in pre order.
     *  TODO: Implement
     */
    void printPreOrder( AvlNode *t ) const
    {
      if (t != nullptr) {
	cout << t->element << " ";
	printPreOrder(t->left);
	printPreOrder(t->right);
      }
    }

    /**
     * Internal method to print a subtree rooted at t in post order.
     *  TODO: Implement
     */
    void printPostOrder( AvlNode *t ) const
    {
      if (t != nullptr) {
	printPostOrder(t->left);
	printPostOrder(t->right);
	cout << t->element << " ";
      }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
    }


    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     *  TODO: Implement
     */
    int height( AvlNode *t ) const
    {
      if (t == nullptr)
	return -1;
      else
	return (max(height(t->left), height(t->right)) + 1);       // take max height of children, add one for the current node
    }


    int max( int lhs, int rhs ) const
    {
      return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
      // Perform rotation
      AvlNode * leftChild = k2->left;
      k2->left = leftChild->right;
      leftChild->right = k2;
      // Update heights; note that there is no need to update leftChild's right child's height (if it exists)
      k2->height = height(k2);
      leftChild->height = height(leftChild);
      // Set new root
      k2 = leftChild;    // since passing by ref, will update root if rotation occurs there
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {   // same logic as rotateWithLeftChild
      AvlNode * rightChild = k1->right;   // get right child
      k1->right = rightChild->left;       // new right of parent  is right's left
      rightChild->left = k1;              // new left of right is k1
      k1->height = height(k1);            // update height
      rightChild->height = height(rightChild);   // update height
      k1 = rightChild;   // update root
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
      rotateWithRightChild(k3->left);
      rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     *  TODO: Implement
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
      rotateWithLeftChild(k1->right);
      rotateWithRightChild(k1);
    }
};

#endif
