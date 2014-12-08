/**
 * Treap - Treap that inherits from SelfOrganizingTree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    Treap.h
 * @date    9-12-2014
 **/

#ifndef TREAP_H
#define TREAP_H

#include "SelfOrganizingTree.h"
#include "TreapNode.h"

template <class INFO_T> class Treap : public SelfOrganizingTree<INFO_T> {
    public:
        typedef TreapNode<INFO_T> node_t;
        typedef SelfOrganizingTree<INFO_T> S; // super class

       /**
        * @function     Treap( )
        * @abstract     constructor
        * @post         A Treap is created
        **/
        Treap( int randomRange =100 ) : S( ) {
            random =randomRange;
            srand( time( NULL ) );
        }

       /**
        * @function     Treap( )
        * @abstract     constructor
        * @param        cpy
        * @post         A Treap is created
        **/
        Treap( const Treap& cpy, int randomRange =100 ) : S( cpy ) {
            random =randomRange;
            srand( time( NULL ) );
        }

       /**
        * @function     insert( )
        * @abstract     A node with label 'info' is inserted into the tree and
        *               put in the right place. A label may not appear twice in
        *               a tree.
        * @param        info - the label of the node
        * @return       the node we inserted
        * @post         The tree now contains a node with 'info'
        **/
        node_t* insert( const INFO_T& info,
                        TreeNode<INFO_T>* parent =0, // Ignored
                        bool preferRight =false,     // Ignored
                        int replaceBehavior =0 ) { // Ignored
            // Prevent duplicates

            if( S::find( this->root( ), info ) )
                return 0;
            node_t *node =new node_t( );
            S::insertInto( info, node );            
            node->priority =rand( ) % random + 1;
            rebalance( node );

            return node;
        }

       /**
        * @function     remove( )
        * @abstract     the node provided with the parameter is deleted from the
        *               tree by rotating it down until it becomes a leaf or has
        *               only one child. In the first  case it's just deleted,
        *               in the second it's replaced by its subtree.
        * @param        node - the node to be deleted
        * @post         The node is deleted from the tree which still retains
        *               the Treap properties.
        **/
        void remove( node_t* node ) {
            node_t *temp = node;
            // rotating it down until the condition no longer applies.
            while( temp->leftChild( ) && temp->rightChild( ) )
            {
                if( static_cast<node_t*>( temp->rightChild( ) )->priority >
                    static_cast<node_t*>( temp->leftChild( ) )->priority )
                    this->rotateLeft( temp );
                else
                    this->rotateRight( temp );
            }
            // if it's a leaf
            if( !temp->leftChild( ) && !temp->rightChild( ) )
                S::remove( temp );
            // if it only has a right child
            else if( !temp->leftChild( ) )
                temp->replace( static_cast<node_t*>( temp->rightChild( ) ) );
            // if it only has a left child
            else if( !node->rightChild( ) )
                temp->replace( static_cast<node_t*>( temp->leftChild( ) ) );
        }

    private:
        int random;

       /**
        * @function     rebalance( )
        * @abstract     The tree is rebalanced. We do the necessary rotations
        *               from the bottom up to make sure the Treap properties are
        *               still intact.
        * @param        info - the label of the node
        * @return       the node we inserted
        * @post         The tree is now perfectly balanced.
        **/
        void rebalance( node_t* node ) {
            if( !node )
                return;
            node_t* temp =node;
            int myPriority =node->priority;
            while( temp->parent( ) && 
                   myPriority > 
                   static_cast<node_t*>( temp->parent( ) )->priority ) {
                temp =static_cast<node_t*>( temp->parent( ) );
                if( temp->leftChild( ) == node )
                    this->rotateRight( temp );
                else
                    this->rotateLeft( temp );
            }
        }
  
};

#endif
