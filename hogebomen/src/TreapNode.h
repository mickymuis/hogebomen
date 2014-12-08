/**
 * TreapNode - Node atom type for Treap
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    TreapNode.h
 * @date    9-11-2014
 **/

#ifndef TREAPNODE_H
#define TREAPNODE_H

#include "BSTNode.h"

template <class INFO_T> class Treap;

template <class INFO_T> class TreapNode : public BSTNode<INFO_T>
{
    public:
        typedef BSTNode<INFO_T> S; // super class

        /**
        * @function     TreapNode( )
        * @abstract     Constructor, creates a node
        * @param        info, the contents of a node
        * @param        parent, the parent of the node 
        * @post         A node has been created.
        **/   
      	TreapNode( const INFO_T& info, TreapNode<INFO_T>* parent =0 ) 
      	    : S( info, parent ), priority( 0 ) {
        }
      	
       /**
        * @function     TreapNode( )
        * @abstract     Constructor, creates a node
        * @param        parent, the parent of the node    
        * @post         A node has been created.
        **/
      	TreapNode( TreapNode<INFO_T>* parent =0 )
            : S( (S)parent ), priority( 0 ) {
        }

        /**
        * @function  replace( )
        * @abstract  Replaces the node with another node in the tree
        * @param     n, the node we replace the node with, this one gets deleted
        * @pre       both this node and n must be in the same parent tree
        * @post      The node will be replaced and n will be deleted.
        **/
        void replace( TreapNode<INFO_T>* n ) {
            priority = n->priority;
            this->S::replace( n );
        }

        bool operator <( const TreapNode<INFO_T> &rhs ) {
            return S::info() < rhs.info();
        }
        
        bool operator <=( const TreapNode<INFO_T> &rhs ) {
            return S::info() <= rhs.info();
        }
        
        bool operator >( const TreapNode<INFO_T> &rhs ) {
            return S::info() > rhs.info();
        }
        
        bool operator >=( const TreapNode<INFO_T> &rhs ) {
            return S::info() >= rhs.info();
        }

        int priority;

    protected:
        friend class Treap<INFO_T>;
};


#endif
