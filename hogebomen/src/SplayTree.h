/**
 * SplayTree - Splay-tree implementation
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    SplayTree.h
 * @date    3-11-2014
 **/

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "SelfOrganizingTree.h"

template <class INFO_T> class SplayTree : public SelfOrganizingTree<INFO_T> {
    public:
        typedef BSTNode<INFO_T> node_t;
        typedef SelfOrganizingTree<INFO_T> S; // super class

        SplayTree( ) : SelfOrganizingTree<INFO_T>( ) { }
        
        SplayTree( const SplayTree& copy ) 
            : SelfOrganizingTree<INFO_T>( copy ) { }
        
        /**
        * @function  insert( )
        * @abstract  reimplemented virtual function from BinarySearchTree<>
        *            the new node will always be the root
        * @param     info, the contents of the new node
        * @param     parent, ignored
        * @param     preferRight, ignored
        * @param     replaceBehavior, ignored
        * @return    returns a pointer to the inserted node (root)
        **/
        virtual node_t* insert( const INFO_T& info,
                            TreeNode<INFO_T>* parent =0, // Ignored
                            bool preferRight =false,     // Ignored
                            int replaceBehavior =0 ) { // Ignored
            return splay( S::insert( info, parent, preferRight ) );
        }
        
        /**
        * @function  replace( )
        * @abstract  reimplemented virtual function from BinarySearchTree<>
        *            replaces a given node or the root
        *            the resulting node will be propagated to location of the root
        * @param     info, the contents of the new node
        * @param     node, node to be replaced
        * @param     alignRight, ignored
        * @param     replaceBehavior, ignored
        * @return    returns a pointer to the new node (=root)
        * @pre       node should be in this tree
        * @post      replace() will delete and/or remove node.
        *            if node is 0, it will take the root instead
        **/
        virtual node_t* replace( const INFO_T& info, 
                             TreeNode<INFO_T>* node =0, 
                             bool alignRight =false, 
                             int replaceBehavior =0 ) {
            return splay( S::replace( info, node, alignRight ) );
        }
        
       /**
        * @function  remove( )
        * @abstract  reimplemented virtual function from BinarySearchTree<>
        *            removes a given node or the root and restores the
        *            BST properties. The node-to-be-removed will be spayed
        *            before removal.
        * @param     node, node to be removed
        * @pre       node should be in this tree
        * @post      memory for node will be deallocated
        **/
        virtual void remove( TreeNode<INFO_T> *node ) {
            S::remove( splay( static_cast<node_t*>(node) ) );
        }
        
       /**
        * @function  find( )
        * @abstract  reimplemented virtual function from Tree<>
        *            performs a binary search in a given (sub)tree
        *            splays the node (if found) afterwards
        * @param     haystack, the subtree to search. Give 0 for the entire tree
        * @param     needle, key/info-value to find
        * @return    returns a pointer to node, if found
        * @pre       haystack should be in this tree
        * @post      may return 0, the structure of the tree may change
        **/
        virtual TreeNode<INFO_T>* find( TreeNode<INFO_T>* haystack, 
                                        const INFO_T& needle ) {
            return splay( static_cast<node_t*>( S::find( haystack, needle ) ) );
        }
        
       /**
        * @function  splay( )
        * @abstract  Performs the splay operation on a given node.
        *            'Splay' means a certain amount of rotations in order
        *            to make the given node be the root of the tree while
        *            maintaining the binary search tree properties.
        * @param     node, the node to splay
        * @pre       The node must be a node in this tree
        * @post      The node will be the new root of the tree
        *            No nodes will be invalided and no new memory is
        *            allocated. Iterators may become invalid.
        **/
        node_t* splay( node_t* node ) {
        
            enum MODE {
                LEFT =0x1, RIGHT =0x2,
                PLEFT =0x4, PRIGHT =0x8 };
        
            // Can't splay the root (or null)
            if( !node || S::m_root == node )
                return 0;
                
            node_t *p =static_cast<node_t*>( node->parent( ) );
            int mode;
            
            while( p != S::m_root ) {
                if( p->leftChild( ) == node )
                    mode =RIGHT;
                else
                    mode =LEFT;
                    
                assert( p->parent( ) != nullptr );
                
                // Node's grandparent
                node_t* g =static_cast<node_t*>( p->parent( ) );
                
                if( g->leftChild( ) == p )
                    mode |= PRIGHT;
                else
                    mode |= PLEFT;
                    
                // True if either mode is LEFT|PLEFT or RIGHT|PRIGHT
                if( (mode >> 2) == (mode & 0x3 ) ) {
                    // the 'zig-zig' step
                    // first rotate g-p then p-node
                    
                    if( mode & PLEFT )
                        this->rotateLeft( g );
                    else
                        this->rotateRight( g );
                    
                    if( mode & LEFT )
                        this->rotateLeft( p );
                    else
                        this->rotateRight( p );
                }
                else {
                    // the 'zig-zag' step
                    // first rotate p-node then g-p
                    
                    if( mode & LEFT )
                        this->rotateLeft( p );
                    else
                        this->rotateRight( p );
                    
                    if( mode & PLEFT )
                        this->rotateLeft( g );
                    else
                        this->rotateRight( g );
                }
                
                // perhaps we're done already...
                if( node == this->root( ) )
                    return node;
            }
            
            // The 'zig-step': parent of node is the root
            
            if( p->leftChild( ) == node )
                this->rotateRight( p );
            else
                this->rotateLeft( p );
            
            return node;
        }
};

#endif
