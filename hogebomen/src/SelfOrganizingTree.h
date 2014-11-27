/**
 * SelfOrganizingTree - Abstract base type inheriting from Tree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    SelfOrganizingTree.h
 * @date    3-11-2014
 **/

#ifndef SELFORGANIZINGTREE_H
#define SELFORGANIZINGTREE_H

#include "BinarySearchTree.h"

template <class INFO_T> class SelfOrganizingTree : public BinarySearchTree<INFO_T> {
    public:
        typedef BSTNode<INFO_T> node_t;
        typedef BinarySearchTree<INFO_T> S; // super class
        
      /**
        * @function  SelfOrganizingTree( ) : S( )
        * @abstract  Constructor
        **/      	
        SelfOrganizingTree( ) : S( ) { }

        virtual node_t *rotateLeft( node_t * node ){
            if( this->root( ) == node )
                return static_cast<node_t *>( S::m_root = node->rotateLeft( ) );
            else
                return node->rotateLeft( );
        }

        virtual node_t *rotateRight( node_t * node ){
            if( this->root( ) == node )
                return static_cast<node_t *>( S::m_root = node->rotateRight( ) );
            else
                return node->rotateRight( );
        }

    private:

};


#endif
