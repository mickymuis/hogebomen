/**
 * AVLNode - Node atom type for AVLTree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    AVLNode.h
 * @date    9-11-2014
 **/

#ifndef AVLNODE_H
#define AVLNODE_H

#include "BSTNode.h"

template <class INFO_T> class AVLTree;

template <class INFO_T> class AVLNode : public BSTNode<INFO_T>
{
    public:
        typedef BSTNode<INFO_T> S; // super class

        /**
        * @function     AVLNode( )
        * @abstract     Constructor, creates a node
        * @param        info, the contents of a node
        * @param        parent, the parent of the node 
        * @post         A node has been created.
        **/   
      	AVLNode( const INFO_T& info, AVLNode<INFO_T>* parent =0 ) 
      	    : S( info, parent ) {
        }
      	
       /**
        * @function     AVLNode( )
        * @abstract     Constructor, creates a node
        * @param        parent, the parent of the node    
        * @post         A node has been created.
        **/
      	AVLNode( AVLNode<INFO_T>* parent =0 )
            : S( (S)parent ) {
        }

       /**
        * @function     balanceFactor( )
        * @abstract     we return the height of the rightchild subtracted with
        *               the height of the left child. Because of the properties
        *               of an AVLtree, this should never be less than -1 or more
        *               than 1.
        * @return       we return the difference between the height of the
        *               rightchild and the leftchild.    
        * @post         The difference between the two child nodes is returned.
        **/
        int balanceFactor( ){
            return static_cast<AVLNode *>( this->rightChild( ) )->getHeight( ) -
                   static_cast<AVLNode *>( this->leftChild( ) )->getHeight( );
        }

       /**
        * @function     updateHeight( )
        * @abstract     we update the height of the node.    
        * @pre          The children of the node need to have the correct height.
        * @post         The node now has the right height.
        **/
        void updateHeight( ) {
            int lHeight =static_cast<AVLNode *>( this->leftChild( ) )
                         ->getHeight( );
            int rHeight =static_cast<AVLNode *>( this->rightChild( ) )
                         ->getHeight( );

            this->height =( 1 + ( ( lHeight > rHeight ) ? lHeight : rHeight ) );
        }

       /**
        * @function     getHeight( )
        * @abstract     we want to know the height of the node.
        * @return       we return the height of the node.   
        * @post         The current height of the node is returned.
        **/
        int getHeight( ) {
            return (this ? this->height : 0);
        }

        bool operator <( const AVLNode<INFO_T> &rhs ) {
            return S::info() < rhs.info();
        }
        
        bool operator <=( const AVLNode<INFO_T> &rhs ) {
            return S::info() <= rhs.info();
        }
        
        bool operator >( const AVLNode<INFO_T> &rhs ) {
            return S::info() > rhs.info();
        }
        
        bool operator >=( const AVLNode<INFO_T> &rhs ) {
            return S::info() >= rhs.info();
        }

    protected:
        friend class AVLTree<INFO_T>;

    private:
        int height;
};


#endif
