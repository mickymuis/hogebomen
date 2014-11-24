/**
 * AVLNode - Node atom type for AVLTree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    AVLNode.h
 * @date    3-11-2014
 **/

#ifndef AVLNODE_H
#define AVLNODE_H

#include "BSTNode.h"

template <class INFO_T> class AVLTree;

template <class INFO_T> class AVLNode : public BSTNode<INFO_T>
{
    public:
        typedef BSTNode<INFO_T> S; // super class

// #? still need to make it so that you can't change this from within main.cc?

        int balanceFactor;
        
        /**
        * @function  AVLNode( )
        * @abstract  Constructor, creates a node
        * @param     info, the contents of a node
        * @param     parent, the parent of the node 
        * @post      A node has been created.
        **/   
      	AVLNode( const INFO_T& info, AVLNode<INFO_T>* parent =0 ) 
      	    : S( info, parent ) {
            balanceFactor = 0;
        }
      	
       /**
        * @function  AVLNode( )
        * @abstract  Constructor, creates a node
        * @param     parent, the parent of the node    
        * @post      A node has been created.
        **/
      	AVLNode( AVLNode<INFO_T>* parent =0 )
            : S( (S)parent ) {
            balanceFactor = 0;
        }

    protected:
        friend class AVLTree<INFO_T>;
};


#endif
