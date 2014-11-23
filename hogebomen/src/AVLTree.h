/**
 * AVLTree - AVL-SelfOrganizingTree that inherits from SelfOrganizingTree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    AVLTree.h
 * @date    3-11-2014
 **/

#ifndef AVLTREE_H
#define AVLTREE_H

#include "SelfOrganizingTree.h"
#include "AVLNode.h"

template <class INFO_T> class AVLTree : public SelfOrganizingTree<INFO_T> {
    public:
        typedef AVLNode<INFO_T> node_t;
        typedef SelfOrganizingTree<INFO_T> S; // super class
        
        AVLTree( ) : S( ) { }
        AVLTree( const AVLTree& cpy ) : S( cpy ) { }

        bool updateBalanceFactorsInsert( AVLNode<INFO_T>* node ){
            AVLNode<INFO_T> Q( node );
            AVLNode<INFO_T> * P( static_cast<node_t *>( node->parent( ) )  );

            if( P->leftChild( ) == &Q )
                P->balanceFactor--;
            else
                P->balanceFactor++;

            while( P != this->root( ) && P->balanceFactor != 2 && P->balanceFactor != -2) {
                Q = P;
                P = static_cast<node_t *>( P->parent( ) );

                if (Q.balanceFactor == 0)
                    return false;

                if (P->leftChild( ) == &Q)
                    if( P->leftChild( ) == &Q )
                        P->balanceFactor--;
                    else
                        P->balanceFactor++;
            }
            // return if we need to rebalance (true) and if so, from which node.
            node = P;
            return (P->balanceFactor == 2 || P->balanceFactor == -2);
        }

        bool updateBalanceFactorsDelete( AVLNode<INFO_T>* node ){
            AVLNode<INFO_T> Q;
            AVLNode<INFO_T> P( node );
            while( Q != this->root( ) && Q->balanceFactor != -2) {
                Q = P;                
                Q->balanceFactor--;
                P = static_cast<node_t *>( Q->parent( ) );
            }
            // return if we need to rebalance (true) and if so, from which node.
            node = Q;
            return (Q->balanceFactor == 2 || Q->balanceFactor == -2);
        }

        virtual node_t *pushBack( const INFO_T& info ) {
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
        

    private:

};

#endif
