/**
 * BSTNode - Node atom for BinarySearchTree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    BSTNode.h
 * @date    3-11-2014
 **/

#ifndef BSTNODE_H
#define BSTNODE_H

#include "TreeNode.h"

template <class INFO_T> class BinarySearchTree;

template <class INFO_T> class BSTNode : public TreeNode<INFO_T>
{
    public:
        typedef TreeNode<INFO_T> S; // super class
        
        /**
        * @function  BSTNode( )
        * @abstract  Constructor, creates a node
        * @param     info, the contents of a node
        * @param     parent, the parent of the node 
        * @post      A node has been created.
        **/   
      	BSTNode( const INFO_T& info, BSTNode<INFO_T>* parent =0 ) 
      	    : S( info, parent ) { }
      	
       /**
        * @function  BSTNode( )
        * @abstract  Constructor, creates a node
        * @param     parent, the parent of the node    
        * @post      A node has been created.
        **/
      	BSTNode( BSTNode<INFO_T>* parent =0 )
            : S( (S)parent ) { }
        
        
        bool operator <( const BSTNode<INFO_T> &rhs ) {
            return S::info() < rhs.info();
        }
        
        bool operator <=( const BSTNode<INFO_T> &rhs ) {
            return S::info() <= rhs.info();
        }
        
        bool operator >( const BSTNode<INFO_T> &rhs ) {
            return S::info() > rhs.info();
        }
        
        bool operator >=( const BSTNode<INFO_T> &rhs ) {
            return S::info() >= rhs.info();
        }
    protected:
        friend class BinarySearchTree<INFO_T>;
};

#endif
