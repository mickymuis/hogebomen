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
        node_t* insert( const INFO_T& info ) {
            node_t* node = new node_t;
            if( S::find( this->root( ), info ) )
                return node;
            node =static_cast<node_t* >( S::pushBack( info ) );
            rebalance( node );
            return node;
        }

       /**
        * @function     rebalance( )
        * @abstract     The tree is rebalanced. We do the necessary rotations
        *               from the bottom up to make sure the AVL properties are
        *               still intact.
        * @param        node - the node we're going to rebalance
        * @post         The tree is now perfectly balanced.
        **/
        void rebalance( node_t* node ) {
            // this is only necessary because the node that we just made isn't 
            // an AVLNODE and doesn't have a height yet :(.
            node->updateHeight( );

            node_t* temp = node;
            while( temp->parent( ) ) {
                temp =static_cast<node_t*>( temp->parent( ) );
                temp->updateHeight( );
                // right subtree too deep
                if( temp->balanceFactor( ) == 2 ) {
                    if( temp->rightChild( ) ) {
                        if( static_cast<node_t*>( temp->rightChild( ) )
                            ->balanceFactor( ) < 0 )
                            this->rotateRight(
                            static_cast<node_t*>( temp->rightChild( ) ) );
                    }
                    this->rotateLeft( temp );    
                }
                // left subtree too deep
                else if( temp->balanceFactor( ) == -2 ) {
                    if( temp->leftChild( ) ) {
                        if( static_cast<node_t*>( temp->leftChild( ) )->
                            balanceFactor( ) > 0 )
                            this->rotateLeft(
                            static_cast<node_t*>( temp->leftChild( ) ) );
                    }
                    this->rotateRight( temp );             
                }
            }
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
        node_t* rotateLeft( node_t* node ) {
            node_t *temp = static_cast<node_t*>( S::rotateLeft( node ) );
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
        node_t* rotateRight( node_t* node ) {
            node_t* temp = static_cast<node_t*>( S::rotateRight( node ) );
            temp->updateHeight( );
            if( temp->rightChild( ) )
                static_cast<node_t*>( temp->rightChild( ) )->updateHeight( );
            return temp;
        }

       /**
        * @function     remove( )
        * @abstract     A node is removed in such a way that the properties of
        *               an AVL tree remain intact.
        * @param        node - the node we're going to remove
        * @post         The node has breen removed, but the remaining tree still
        *               contains all of its other nodes and still has all the
        *               AVL properties.
        **/
        void remove( node_t* node ) {
            // if it's a leaf
            if( !node->leftChild( ) && !node->rightChild( ) )
                S::remove( node );
            // internal node with kids
            else {
                if( node->rightChild( ) ) {
                    node =static_cast<node_t*>( S::replace( S::min(  static_cast<node_t*>( node->rightChild( ) ) )->info( ), node ) );
                    removeMin( static_cast<node_t*>( node->rightChild( ) ) );
                    node->setRightChild( node->rightChild( ));
                }
                else
                    // just delete the node and replace it with its leftChild
                    node->replace( node->leftChild( ) );
            }
        }

    private:

       /**
        * @function     removeMin( )
        * @abstract     Recursively we go through the tree to find the node with
        *               the smallest value in the subtree with root node. Then we
        *               restore the balance factors of all its parents.
        * @param        node - the root of the subtree we're looking in
        * @return       At the end of the recursion we return the parent of the
        *               node with the smallest value. Then we go up the tree and
        *               rebalance every parent from this upwards.
        * @post         The node with the smallest value is deleted and every
        *               node still has the correct balance factor.
        **/
        node_t* removeMin( node_t* node ) {
            node_t* temp;
            if( node->leftChild( ) )
                temp =removeMin( static_cast<node_t*>( node->leftChild( ) ) );
            else {
                temp =static_cast<node_t*>( node->parent( ) );
                S::remove( node );
            }
            rebalance( temp );
            return temp;
        }

       /**
        * @function     removeMax( )
        * @abstract     Recursively we go through the tree to find the node with
        *               the highest value in the subtree with root node. Then we
        *               restore the balance factors of all its parents.
        * @param        node - the root of the subtree we're looking in
        * @return       At the end of the recursion we return the parent of the
        *               node with the highest value. Then we go up the tree and
        *               rebalance every parent from this upwards.
        * @post         The node with the highest value is deleted and every
        *               node still has the correct balance factor.
        **/
        node_t* removeMax( node_t* node ) {
            node_t* temp;
            if( node->rightChild( ) )
                temp =removeMin( static_cast<node_t*>( node->rightChild( ) ) );
            else {
                temp =static_cast<node_t*>( node->parent( ) );
                S::remove( node );
            }
            rebalance( temp );
            return temp;
        }

};

#endif
