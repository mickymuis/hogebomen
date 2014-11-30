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

        SplayTree( ) : SelfOrganizingTree<INFO_T>( ) {
        
        }
        
        SplayTree( const SplayTree& copy ) : SelfOrganizingTree<INFO_T>( copy ) {
        
        }
        
        void splay( node_t* node ) {
        
            enum MODE {
                LEFT =0x1, RIGHT =0x2,
                PLEFT =0x4, PRIGHT =0x8 };
        
            // Can't splay the root
            if( S::m_root == node )
                return;
                
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
                
                bool isRoot =false;
                if( g == S::m_root )
                    isRoot =true;
                
                if( g->leftChild( ) == p )
                    mode |= PRIGHT;
                else
                    mode |= PLEFT;
                    
                // True if either mode is LEFT|PLEFT or RIGHT|PRIGHT
                if( (mode >> 2) == (mode & 0x3 ) ) {
                    // the 'zig-zig' step
                    // first rotate g-p then p-node
                    
                    if( mode & PLEFT )
                        g->rotateLeft( );
                    else
                        g->rotateRight( );
                    
                    if( mode & LEFT )
                        p->rotateLeft( );
                    else
                        p->rotateRight( );
                }
                else {
                    // the 'zig-zag' step
                    // first rotate p-node then g-p
                    
                    if( mode & LEFT )
                        p->rotateLeft( );
                    else
                        p->rotateRight( );
                    
                    if( mode & PLEFT )
                        g->rotateLeft( );
                    else
                        g->rotateRight( );
                }
                
                // perhaps we're done already...
                if( isRoot ) {
                    S::m_root =node;
                    return;
                }
            }
            
            // The 'zig-step': parent of node is the root
            
            if( p->leftChild( ) == node )
                S::m_root =p->rotateRight( );
            else
                S::m_root =p->rotateLeft( );
        }
};

#endif
