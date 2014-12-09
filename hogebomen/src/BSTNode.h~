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
        
            if( !this->rightChild( ) ) // Cannot rotate
                return this;
  
            bool isLeftChild =this->parent( ) && this == this->parent( )->leftChild( );
            
            // new root of tree
            BSTNode *newTop =static_cast<BSTNode *>(this->rightChild( ));
            // new rightchild of the node that is rotated
            BSTNode *newRight =static_cast<BSTNode *>(newTop->leftChild( ));
            // the parent under which all of the magic is happening
            BSTNode *topParent =static_cast<BSTNode *>(this->parent( ));
            
            // We become left-child of our right-child
            // newTop takes our place with our parent
            newTop->setParent( topParent );
            if( isLeftChild && topParent )
                topParent->setLeftChild( newTop );
            else if( topParent )
                topParent->setRightChild( newTop );

            newTop->setLeftChild( this );
            this->setParent( newTop );
 
            // We take the left-child of newTop as our right-child         
            this->setRightChild( newRight );
            if( newRight )
                newRight->setParent( this );
            
            return newTop;
        }
        
        // Idea: rotate this node right and return the node that comes in its place
        BSTNode *rotateRight( ) {
            if( !this->leftChild( ) ) // Cannot rotate
                return this;
  
            bool isRightChild =this->parent( ) && this == this->parent( )->rightChild( );
            
            // new root of tree
            BSTNode *newTop =static_cast<BSTNode *>(this->leftChild( ));
            // new leftchild of the node that is rotated
            BSTNode *newLeft =static_cast<BSTNode *>(newTop->rightChild( ));
            // the parent under which all of the magic is happening
            BSTNode *topParent =static_cast<BSTNode *>(this->parent( ));
            
            // We become left-child of our right-child
            // newTop takes our place with our parent
            newTop->setParent( topParent );
            if( isRightChild && topParent )
                topParent->setRightChild( newTop );
            else if( topParent )
                topParent->setLeftChild( newTop );

            newTop->setRightChild( this );
            this->setParent( newTop );
 
            // We take the left-child of newTop as our right-child         
            this->setLeftChild( newLeft );
            if( newLeft )
                newLeft->setParent( this );
            
            return newTop;
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
