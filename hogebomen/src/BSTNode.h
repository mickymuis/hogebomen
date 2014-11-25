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
        
        // Idea: rotate this node left and return the node that comes in its place
        BSTNode *rotateLeft( ) {
        
            if( !rightChild( ) ) // Cannot rotate
                return this;
                
            bool isLeftChild =parent( ) && this == parent( )->leftChild( );
                
            BSTNode *newTop =rightChild( );
            BSTNode *newRight =newTop->leftChild( );
            BSTNode *topParent =parent( );
            
            // We become left-child of our right-child
            // newTop takes our place with our parent
            newTop->setParent( topParent );
            if( isLeftChild && topParent )
                topParent->setLeftChild( newTop );
            else if( topParent )
                topParent->setRightChild( newTop );
                
            newTop->setLeftChild( this );
            setParent( newTop );
            
            // We take the left-child of newTop as our right-child         
            setRightChild( newRight );
            if( newRight )
                newRight->setParent( this );
                
            // We're done?
            
            return newTop;
        }
        
        // Idea: rotate this node right and return the node that comes in its place
        BSTNode *rotateRight( ) {
        
        }

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
