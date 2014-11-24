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

       /**
        * @function  insert( )
        * @abstract  inserts node or subtree under a parent or creates an empty 
        *            root node
        * @param     info, contents of the new node
        * @param     parent, parent node of the new node. When zero, the root is
        *            assumed
        * @param     alignRight, insert() checks on which side of the parent
        *            node the new node can be inserted. By default, it checks 
        *            the left side first.
        *            To change this behavior, set preferRight =true.
        * @param     replaceBehavior, action if parent already has two children. 
        *            One of:
        *            ABORT_ON_EXISTING - abort and return zero
        *            MOVE_EXISTING - make the parent's child a child of the new
        *                            node, satisfies preferRight
        *            DELETE_EXISTING - remove one of the children of parent 
        *                              completely also satisfies preferRight
        * @return    pointer to the inserted TreeNode, if insertion was
        *            successfull
        * @pre       If the tree is empty, a root node will be created with info
        *            as it contents
        * @pre       The instance pointed to by parent should be part of the 
        *            called instance of Tree
        * @post      Return zero if no node was created. Ownership is assumed on
        *            the new node.
        *            When DELETE_EXISTING is specified, the entire subtree on 
        *            preferred side may be deleted first.
        **/     

        virtual node_t* insert( const node_t* info,
                        node_t* parent =0,
                        bool preferRight =false, 
                        int replaceBehavior =S::ABORT_ON_EXISTING ) {
            cout << "I am being called!" << endl;
/*
            node_t *node =  info;

            if( !parent )
                parent =m_root;
                
            if( !parent )
                return pushBack( info );
            
            node_t *node =0;
            
            if( !parent->leftChild( )
                  && ( !preferRight || ( preferRight &&
                       parent->rightChild( ) ) ) ) {
                node =info;
                parent->setLeftChild( node );
                node->setParent( parent );
            
            } else if( !parent->rightChild( ) ) {
                node = info;
                parent->setRightChild( node );
                node->setParent( parent );
                
            } else if( replaceBehavior == S::MOVE_EXISTING ) {
                node = info;
                if( preferRight ) {
                    node->setRightChild( parent->rightChild( ) );
                    node->rightChild( )->setParent( node );
                    parent->setRightChild( node );
                } else {
                    node->setLeftChild( parent->leftChild( ) );
                    node->leftChild( )->setParent( node );
                    parent->setLeftChild( node );
                }
                
            } else if( replaceBehavior == S::DELETE_EXISTING ) {
                node = info;
                if( preferRight ) {
                    deleteRecursive( parent->rightChild( ) );
                    parent->setRightChild( node );
                } else {
                    deleteRecursive( parent->leftChild( ) );
                    parent->setLeftChild( node );
                }
                
            } 
            return node;*/
        }

		void rotate( BSTNode<INFO_T> node ) {

            SelfOrganizingTree<INFO_T> * temporaryTree = new SelfOrganizingTree;
            node_t temp(temporaryTree->pushBack(node));

// TO DO: need to add an insert function that accepts nodes instead of just labels    
            // if it's a left child, we do a right rotation
            if( &node == node.parent( )->leftChild( ) ) {
                temporaryTree->copyFromNode( node.leftChild( ), temporaryTree->root( ), true );
                temp = temporaryTree->insert( root( ), temp, false );
/*                temporaryTree->copyFromNode( root( )->rightChild( ),temp, false);
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
