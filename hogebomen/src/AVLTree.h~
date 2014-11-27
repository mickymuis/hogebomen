/**
 * AVLTree - AVL-SelfOrganizingTree that inherits from SelfOrganizingTree
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    AVLTree.h
 * @date    9-12-2014
 **/

#ifndef AVLTREE_H
#define AVLTREE_H

#include "SelfOrganizingTree.h"
#include "AVLNode.h"

template <class INFO_T> class AVLTree : public SelfOrganizingTree<INFO_T> {
    public:
        typedef AVLNode<INFO_T> node_t;
        typedef SelfOrganizingTree<INFO_T> S; // super class

       /**
        * @function     AVLTree( )
        * @abstract     constructor
        * @post         An AVLTree is created
        **/
        AVLTree( ) : S( ) { }

       /**
        * @function     AVLTree( )
        * @abstract     constructor
        * @param        cpy
        * @post         An AVLTree is created
        **/
        AVLTree( const AVLTree& cpy ) : S( cpy ) { }

       /**
        * @function     insert( )
        * @abstract     A node with label 'info' is inserted into the tree and
        *               put in the right place. A label may not appear twice in
        *               a tree.
        * @param        info - the label of the node
        * @return       the node we inserted
        * @post         The tree now contains a node with 'info'
        **/
        node_t *insert( const INFO_T& info ) {
            node_t *node = new node_t;
            if( S::find( this->root( ), info ) )
                return node;
            node =static_cast<node_t *>( S::pushBack( info ) );
            rebalance( node );
            return node;
        }

       /**
        * @function     rebalance( )
        * @abstract     The tree is rebalanced. We do the necessary rotations
        *               from the bottom up to make sure the AVL properties are
        *               still intact.
        * @param        node - the node we're going to rebalance
        * @return       the node we just rebalanced (or not, depending on the
        *               balancefactor)
        * @post         The tree is now perfectly balanced.
        **/
        node_t *rebalance( node_t * node ) {
            // this is only necessary because the node that we just made isn't 
            // an AVLNODE and doesn't have a height yet :(.
            node->updateHeight( );
            node_t *temp = node;
            while( temp->parent( ) ) {
                temp =static_cast<node_t *>( temp->parent( ) );
                temp->updateHeight( );

                // right subtree too deep
                if( temp->balanceFactor( ) == 2 ) {
                    if( temp->rightChild( ) ) {
                        if( static_cast<node_t *>( temp->rightChild( ) )
                            ->balanceFactor( ) < 0 )
                            this->rotateRight(
                            static_cast<node_t *>( temp->rightChild( ) ) );
                    }
                    temp =this->rotateLeft( temp );    
                }
                // left subtree too deep
                else if( temp->balanceFactor( ) == -2 ) {
                    if( temp->leftChild( ) ) {
                        if( static_cast<node_t *>( temp->leftChild( ) )->
                            balanceFactor( ) > 0 )
                            this->rotateLeft(
                            static_cast<node_t *>( temp->leftChild( ) ) );
                    }
                    temp =this->rotateRight( temp );             
                }
            }
            return temp;
        }

       /**
        * @function     rotateLeft( )
        * @abstract     We rotate a node left and make sure all the internal
        *               heights of the nodes are up to date.
        * @param        node - the node we're going to rotate left
        * @return       we return the node that is now at the top of this
        *               particular subtree.
        * @post         The node is rotated to the left and the heights are up
        *               to date.
        **/        
        node_t *rotateLeft( node_t * node ){
            node_t *temp = static_cast<node_t *>( S::rotateLeft( node ) );
            temp->updateHeight( );
            if( temp->leftChild( ) )
                static_cast<node_t *>( temp->leftChild( ) )->updateHeight( );
            return temp;
        }

       /**
        * @function     rotateRight( )
        * @abstract     We rotate a node right and make sure all the internal
        *               heights of the nodes are up to date.
        * @param        node - the node we're going to rotate right
        * @return       we return the node that is now at the top of this
        *               particular subtree.
        * @post         The node is rotated to the right and the heights are up
        *               to date.
        **/  
        node_t *rotateRight( node_t * node ){
            node_t *temp = static_cast<node_t *>( S::rotateRight( node ) );
            temp->updateHeight( );
            if( temp->rightChild( ) )
                static_cast<node_t *>( temp->rightChild( ) )->updateHeight( );
            return temp;
        }

    private:

};

#endif
