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

       /**
        * @function  SelfOrganizingTree() : S () 
        * @abstract  Constructor
        * @param     cpy, ...?
        **/      	
        SelfOrganizingTree( const SelfOrganizingTree& cpy ) : S( cpy ) { }

		void rotate( BSTNode<INFO_T> node ) {

            SelfOrganizingTree<INFO_T> * temporaryTree = new SelfOrganizingTree;
            BSTNode<INFO_T> temp(temporaryTree->pushBack(node));
// TO DO: need to add an insert function that accepts nodes instead of just labels    
            // if it's a left child, we do a right rotation
            if( &node == node.parent( )->leftChild( ) ) {
                temporaryTree->copyFromNode( node.leftChild( ), temporaryTree->root( ), true );
/*                temp = temporaryTree->insert( root( ), temp, false);
                temporaryTree->copyFromNode( root( )->rightChild( ),temp, false);
                temporaryTree->copyFromNode( node->rightChild( ), temp, true); */
            }
            // if it's a right child, we do a left rotation
            else {
                temporaryTree->copyFromNode( node.rightChild( ), temporaryTree->root( ), false );
/*                temp = temporaryTree->insert( root( ), temp, true);
                temporaryTree->copyFromNode( node->leftChild( ) ,temp, false);
                temporaryTree->copyFromNode( root()->leftChild( ), temp, true); */
            }
//            this = temporaryTree;


/* PSEUDOCODE van bovenstaande
            // if it's the left child, we do a right rotatio            
            if( &node == node.parent( )->leftChild( ) ) {
                temporaryTree->leftSubTree( ) = node->leftSubTree( );                
                temporaryTree->rightChild( ) = this->root();
                temporaryTree->rightChild( )->rightSubTree( ) = this->root()->rightSubTree( );
                temporaryTree->rightChild( )->leftSubtree( ) = node.rightSubTree();                
            }
            // if it's the right child, we do a left rotation
            else {
             ik ga pseudocodo
                temporaryTree->rightSubTree( ) = node->rightSubTree( );                
                temporaryTree->leftChild( ) = this->root();
                temporaryTree->leftChild( )->rightSubTree( ) = node.leftSubTree( );
                temporaryTree->leftChild( )->leftSubtree( ) = this->root()->leftSubTree();     
            }
                this = temporaryTree;
            */
		}

    private:

};


#endif
