/**
 * BinarySearchTree - BST that inherits from Tree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    BinarySearchTree.h
 * @date    3-11-2014
 **/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Tree.h"
#include "BSTNode.h"

template <class INFO_T> class BinarySearchTree : public Tree<INFO_T> {
    public:
        typedef BSTNode<INFO_T> node_t;
        typedef Tree<INFO_T> S; // super class
        
        BinarySearchTree( ) : S( ) { }
        BinarySearchTree( const BinarySearchTree& cpy ) : S( cpy ) { }
        
        virtual ~BinarySearchTree( ) { }
        
       /**
        * @function  pushBack( )
        * @abstract  reimplemented virtual function from Tree<>
        *            this function is semantically identical to insert()
        * @param     info, the contents of the new node
        **/
        virtual node_t *pushBack( const INFO_T& info ) {
            return insert( info );
        }
        
       /**
        * @function  insert( )
        * @abstract  reimplemented virtual function from Tree<>
        *            the exact location of the new node is determined
        *            by the rules of the binary search tree.
        * @param     info, the contents of the new node
        * @param     parent, ignored
        * @param     preferRight, ignored
        * @param     replaceBehavior, ignored
        * @return    returns a pointer to the inserted node
        **/
        virtual node_t* insert( const INFO_T& info,
                            TreeNode<INFO_T>* parent =0, // Ignored
                            bool preferRight =false,     // Ignored
                            int replaceBehavior =S::ABORT_ON_EXISTING ) { // Ignored
            node_t *n =new node_t( );
            n->info() =info;
            
            if( !S::m_root )
                S::m_root =n;
            else {
                node_t *parent =0;
                node_t *sub =static_cast<node_t*>( S::m_root );
                do {
                    if( *n < *sub ) {
                        parent =sub;
                        sub =static_cast<node_t*>( parent->leftChild( ) );
                    }
                    else {
                        parent =sub;
                        sub =static_cast<node_t*>( parent->rightChild( ) );
                    }
                } while( sub );
                if( *n < *parent )
                    parent->setLeftChild( n );
                else
                    parent->setRightChild( n );
                n->setParent( parent );
            }       
            return n;
        }
        
       /**
        * @function  replace( )
        * @abstract  reimplemented virtual function from Tree<>
        *            replaces a given node or the root
        *            the location of the replaced node may be different
        *            due to the consistency of the binary search tree
        * @param     info, the contents of the new node
        * @param     node, node to be replaced
        * @param     alignRight, ignored
        * @param     replaceBehavior, ignored
        * @return    returns a pointer to the new node
        * @pre       node should be in this tree
        * @post      replace() will delete and/or remove node.
        *            if node is 0, it will take the root instead
        **/
        virtual node_t* replace( const INFO_T& info, 
                             TreeNode<INFO_T>* node =0, 
                             bool alignRight =false, 
                             int replaceBehavior =S::DELETE_EXISTING ) {
            node_t *newnode;
            if( !node )
                node =S::m_root;
            if( !node )
                return pushBack( info );
            
            bool swap =false;
            // We can either just swap the new node with the old and remove
            // the old, or we can remove the old and add the new node via
            // pushBack(). This depends on the value of info
            if( !node->hasChildren( ) ) {
                swap =true; 
            }
            else if( !(node->leftChild( ) 
                    && node->leftChild( )->info( ) > info )
                    && !(node->rightChild( ) 
                    && node->rightChild( )->info( ) < info ) ) {
                swap =true;
            }
            if( swap ) {
                newnode =new node_t( info );
                if( node == S::m_root )
                    S::m_root =newnode;
                node->swapWith( newnode );
                delete node;
            } else {
                remove( node );
                newnode =pushBack( info );
                   
            }
            return newnode;
        }
        
       /**
        * @function  remove( )
        * @abstract  reimplemented virtual function from Tree<>
        *            removes a given node or the root and restores the
        *            BST properties
        * @param     node, node to be removed
        * @pre       node should be in this tree
        * @post      memory for node will be deallocated
        **/
        virtual void remove( TreeNode<INFO_T> *node ) {
            node_t *n =static_cast<node_t*>( node );
            
            while( n->isFull( ) ) {
                // the difficult case
                // we could take either left of right here
                TreeNode<INFO_T> *temp; 
                temp =n->leftChild( );
                while( temp->rightChild( ) ) {
                    temp =temp->rightChild( );
                }
                if( n == S::m_root )
                    S::m_root =temp;
                n->swapWith( temp );
            }

            
            // Assume the above is fixed
            while( n->hasChildren( ) ) {
                if( n->leftChild( ) ) {
                    if( n == S::m_root )
                        S::m_root =n->leftChild( );
                    n->swapWith( n->leftChild( ) );
                }
                else {
                    if( n == S::m_root )
                        S::m_root =n->rightChild( );
                    n->swapWith( n->rightChild( ) );
                }
            }

            if( n->parent( ) && n->parent( )->leftChild( ) == n )
                static_cast<node_t*>( n->parent( ) )->setLeftChild( 0 );
            else if( n->parent( ) && n->parent( )->rightChild( ) == n )
                static_cast<node_t*>( n->parent( ) )->setRightChild( 0 );
            delete n;
        }
        
       /**
        * @function  find( )
        * @abstract  reimplemented virtual function from Tree<>
        *            performs a binary search in a given (sub)tree
        * @param     haystack, the subtree to search. Give 0 for the entire tree
        * @param     needle, key/info-value to find
        * @return    returns a pointer to node, if found
        * @pre       haystack should be in this tree
        * @post      may return 0
        **/
        virtual TreeNode<INFO_T>* find( TreeNode<INFO_T>* haystack, 
                                        const INFO_T& needle ) {
            m_searchStepCounter =0;
            
            if( !haystack )
                haystack =S::m_root;
            while( haystack && haystack->info( ) != needle ) {
                m_searchStepCounter++;
                if( haystack->info( ) > needle )
                    haystack =haystack->leftChild( );
                else
                    haystack =haystack->rightChild( );
            }
            if( !haystack )
                m_searchStepCounter =-1;
            return haystack;
        }
        
       /**
        * @function  lastSearchStepCount( )
        * @abstract  gives the amount of steps needed to complete the most
        *            recent call to find( )
        * @return    positive amount of steps on a defined search result,
        *            -1 on no search result
        */
        virtual int lastSearchStepCount( ) const {
            return m_searchStepCounter;
        }

       /**
        * @function     min( )
        * @abstract     Returns the node with the least value in a binary search
        *               tree. This is achieved through recursion.
        * @param        node - the node from which we start looking
        * @return       Eventually, at the end of the recursion, we return the
        *               adress of the node with the smallest value.
        * @post         The node with the smallest value is returned.
        **/ 
        node_t* min( node_t* node ) const {
            return node->leftChild( ) ?
                   min(static_cast<node_t*>( node->leftChild( ) ) ) : node;
        }

       /**
        * @function     min( )
        * @abstract     We call the function mentioned above and then
        *               return the node with the least value in a binary search
        *               tree.
        * @return       We return the adress of the node with the smallest value.
        * @post         The node with the smallest value is returned.
        **/ 
        node_t* min( ) const {
            return min( static_cast<node_t*>( this->root( ) ) );
        }

       /**
        * @function     max( )
        * @abstract     Returns the node with the highest value in a binary 
        *               search tree. This is achieved through recursion.
        * @param        node - the node from which we start looking
        * @return       Eventually, at the end of the recursion, we return the
        *               adress of the node with the highest value.
        * @post         The node with the highest value is returned.
        **/ 
        node_t* max( node_t* node ) const  {
            return node->rightChild( ) ?
                   max(static_cast<node_t*>( node->rightChild( ) ) ) : node;
        }

       /**
        * @function     max( )
        * @abstract     We call the function mentioned above and then
        *               return the node with the highest value in a binary 
        *               search tree.
        * @return       We return the adress of the node with the highest value.
        * @post         The node with the highest value is returned.
        **/ 
        node_t* max( ) const {
            return max( static_cast<node_t*>( this->root( ) ) );
        }

    protected:
        int m_searchStepCounter;
};

#endif

