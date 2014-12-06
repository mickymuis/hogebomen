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
        Treap( ) : S( ) {
            srand( time( NULL ) );
        }

       /**
        * @function     Treap( )
        * @abstract     constructor
        * @param        cpy
        * @post         A Treap is created
        **/
        Treap( const Treap& cpy ) : S( cpy ) {
            srand( time( NULL ) );
        }

        node_t* insert( const INFO_T& info,
                        TreeNode<INFO_T>* parent =0, // Ignored
                        bool preferRight =false,     // Ignored
                        int replaceBehavior =0 ) { // Ignored
            node_t* node =new node_t;
            if( S::find( this->root( ), info ) )
                return node;
            node =static_cast<node_t* >( S::pushBack( info ) );            
            node->priority =rand( ) % 100 + 1;
            rebalance( node );
            return node;
        }

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
            else if( !temp->leftChild( ) ) {
                temp->copyPriority( static_cast<node_t*>( temp->rightChild( ) ) );
                temp->replace( static_cast<node_t*>( temp->rightChild( ) ) );
            }
            // if it only has a left child
            else if( !node->rightChild( ) ) {
                temp->copyPriority( static_cast<node_t*>( temp->leftChild( ) ) );
                temp->replace( static_cast<node_t*>( temp->leftChild( ) ) );
            }
        }

    private:

        void rebalance( node_t* node ) {
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
