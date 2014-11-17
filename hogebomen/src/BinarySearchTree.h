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
        
        virtual node_t *pushBack( const INFO_T& info ) {
            node_t *n =new node_t( info );
            
            if( !S::m_root )
                S::m_root =n;
            else {
                node_t *parent =static_cast<node_t*>( S::m_root );
                do {
                    if( n < parent ) {
                        if( !parent->leftChild( ) )
                            break;
                        if( n < static_cast<node_t*>( parent->leftChild( ) ) )
                            parent =static_cast<node_t*>( parent->leftChild( ) );
                        else { // parent->leftChild( ) has to move
                        
                        }    
                    }
                    else {
                        if( !parent->rightChild( ) )
                            break;
                        if( n > static_cast<node_t*>( parent->rightChild( ) ) )
                            parent =static_cast<node_t*>( parent->rightChild( ) );
                        else { // parent->rightChild( ) has to move
                        
                        }
                    }
                } while( parent );
                if( n < parent )
                    parent->setLeftChild( n );
                else
                    parent->setRightChild( n );
                n->setParent( parent );
            }       
            return n;
        }
        
        virtual node_t* insert( const INFO_T& info,
                            node_t* parent =0,
                            bool preferRight =false, 
                            int replaceBehavior =S::ABORT_ON_EXISTING ) {
            return pushBack( info );
            // De rest kunnen we gewoon negeren?
        }
        
        virtual node_t* replace( const INFO_T& info, 
                             node_t* node =0, 
                             bool alignRight =false, 
                             int replaceBehavior =S::DELETE_EXISTING ) {
        }
        
        virtual void remove( node_t *n ) {
        }
        
        virtual node_t* find( node_t* haystack, const INFO_T& needle ) {
        }
    private:

};

#endif

