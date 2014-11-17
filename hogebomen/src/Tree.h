/**
 * Tree: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    tree.h
 * @date    26-10-2014
 **/

#ifndef TREE_H
#define TREE_H
#include "TreeNodeIterator.h"
#include <assert.h>
#include <list>
#include <map>

using namespace std;

template <class INFO_T> class Tree
{
    public:
        enum ReplaceBehavoir {
            DELETE_EXISTING,
            ABORT_ON_EXISTING,
            MOVE_EXISTING
        };
        
        typedef TreeNode<INFO_T> node_t;
        typedef TreeNodeIterator<INFO_T> iterator;
        typedef TreeNodeIterator_in<INFO_T> iterator_in;
        typedef TreeNodeIterator_pre<INFO_T> iterator_pre;
        typedef TreeNodeIterator_post<INFO_T> iterator_post;
        typedef list<node_t*> nodelist;

       /**
        * @function  Tree( )
        * @abstract  Constructor of an empty tree
        **/                 
        Tree( )
            : m_root( 0 ) {
        }
    	
       /**
        * @function  Tree( )
        * @abstract  Copy-constructor of a tree. The new tree contains the nodes
        *            from the tree given in the parameter (deep copy)
        * @param     tree, a tree
        **/      	
        Tree( const Tree<INFO_T>& tree )
            : m_root( 0 ) {
            *this =tree;
        }
        
        /**
        * @function  ~Tree( )
        * @abstract  Destructor of a tree. Timber.
        **/  
        ~Tree( ) {
          clear( );
        }
    	
       /**
        * @function  begin_pre( )
        * @abstract  begin point for pre-order iteration
        * @return    interator_pre containing the beginning of the tree in
        *            pre-order
        **/
        iterator_pre begin_pre( ) {
            // Pre-order traversal starts at the root
            return iterator_pre( m_root );
    	  }
       
       /**
        * @function  begin( )
        * @abstract  begin point for a pre-order iteration
        * @return    containing the beginning of the pre-0rder iteration      
        **/
        iterator_pre begin( ) {
            return begin_pre( );
        }
        
       /**
        * @function  end( )
        * @abstract  end point for a pre-order iteration
        * @return    the end of the pre-order iteration  
        **/   
        iterator_pre end( ) {
            return iterator_pre( (node_t*)0 );
        }   
    	
       /**
        * @function  end_pre( )
        * @abstract  end point for pre-order iteration
        * @return    interator_pre containing the end of the tree in pre-order
        **/
        iterator_pre end_pre( ) {
            return iterator_pre( (node_t*)0 );
        }
    	
       /**
        * @function  begin_in( )
        * @abstract  begin point for in-order iteration
        * @return    interator_in containing the beginning of the tree in 
        *            in-order
        **/
        iterator_in begin_in( ) {
            if( !m_root )
                return end_in( );
            node_t *n =m_root;
            while( n->leftChild( ) )
                n =n->leftChild( );
            return iterator_in( n );
    	  }
    	
       /**
        * @function  end_in( )
        * @abstract  end point for in-order iteration
        * @return    interator_in containing the end of the tree in in-order
        **/
        iterator_in end_in( ) {
            return iterator_in( (node_t*)0 );
        }
    	
       /**
        * @function  begin_post( )
        * @abstract  begin point for post-order iteration
        * @return    interator_post containing the beginning of the tree in 
        *            post-order
        **/
        iterator_post begin_post( ) {
            if( !m_root )
                return end_post( );
            node_t *n =m_root;
            while( n->leftChild( ) )
                n =n->leftChild( );
            return iterator_post( n );
        }
    	
       /**
        * @function  end_post( )
        * @abstract  end point for post-order iteration
        * @return    interator_post containing the end of the tree in post-order 
        **/
        iterator_post end_post( ) {
            return iterator_post( (node_t*)0 );
        }
   	
       /**
        * @function  pushBack( )
        * @abstract  a new TreeNode containing `info` is added to the end
        *            the node is added to the node that :
        *               - is in the row as close to the root as possible
        *               - has no children or only a left-child
        *               - seen from the right hand side of the row
        *            this is the `natural` left-to-right filling order
        *            compatible with array-based heaps and full b-trees
        * @param     info, the contents of the new node
        * @post      A node has been added.     
        **/
        virtual node_t *pushBack( const INFO_T& info ) {
            node_t *n =new node_t( info, 0 );
            if( !m_root ) { // Empty tree, simplest case
                m_root =n;
            }
            else { // Leaf node, there are two different scenarios
                int max =getRowCountRecursive( m_root, 0 );
                node_t *parent;
                for( int i =1; i <= max; ++i ) {
                
                    parent =getFirstEmptySlot( i );
                    if( parent ) {
                        if( !parent->leftChild( ) )
                            parent->setLeftChild( n );
                        else if( !parent->rightChild( ) )
                            parent->setRightChild( n );
                        n->setParent( parent );
                        break;
                    }
                }
            }
            return n;
        }
       
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
        virtual node_t* insert( const INFO_T& info,
                        node_t* parent =0,
                        bool preferRight =false, 
                        int replaceBehavior =ABORT_ON_EXISTING ) {
            if( !parent )
                parent =m_root;
                
            if( !parent )
                return pushBack( info );
            
            node_t *node =0;
            
            if( !parent->leftChild( )
                  && ( !preferRight || ( preferRight &&
                       parent->rightChild( ) ) ) ) {
                node =new node_t( info, parent );
                parent->setLeftChild( node );
                node->setParent( parent );
            
            } else if( !parent->rightChild( ) ) {
                node =new node_t( info, parent );
                parent->setRightChild( node );
                node->setParent( parent );
                
            } else if( replaceBehavior == MOVE_EXISTING ) {
                node =new node_t( info, parent );
                if( preferRight ) {
                    node->setRightChild( parent->rightChild( ) );
                    node->rightChild( )->setParent( node );
                    parent->setRightChild( node );
                } else {
                    node->setLeftChild( parent->leftChild( ) );
                    node->leftChild( )->setParent( node );
                    parent->setLeftChild( node );
                }
                
            } else if( replaceBehavior == DELETE_EXISTING ) {
                node =new node_t( info, parent );
                if( preferRight ) {
                    deleteRecursive( parent->rightChild( ) );
                    parent->setRightChild( node );
                } else {
                    deleteRecursive( parent->leftChild( ) );
                    parent->setLeftChild( node );
                }
                
            }
            return node;
        }
        
       /**
        * @function  replace( )
        * @abstract  replaces an existing node with a new node
        * @param     info, contents of the new node
        * @param     node, node to be replaced. When zero, the root is assumed
        * @param     alignRight, only for MOVE_EXISTING. If true, node will be
        *            the right child of the new node. Otherwise, it will be the
        *            left.
        * @param     replaceBehavior, one of:
        *            ABORT_ON_EXISTING - undefined for replace()
        *            MOVE_EXISTING - make node a child of the new node, 
        *                            satisfies preferRight
        *            DELETE_EXISTING - remove node completely
        * @return    pointer to the inserted TreeNode, replace() is always
        *            successful
        * @pre       If the tree is empty, a root node will be created with info
        *            as it contents
        * @pre       The instance pointed to by node should be part of the
        *            called instance of Tree
        * @post      Ownership is assumed on the new node. When DELETE_EXISTING
        *            is specified, the entire subtree pointed to by node is 
        *            deleted first.
        **/
        virtual node_t* replace( const INFO_T& info, 
                         node_t* node =0, 
                         bool alignRight =false, 
                         int replaceBehavior =DELETE_EXISTING ) {
            assert( replaceBehavior != ABORT_ON_EXISTING );
            
            node_t *newnode =new node_t( info );
            if( !node )
                node =m_root;
            if( !node )
                return pushBack( info );
                
            if( node->parent( ) ) {
                newnode->setParent( node->parent( ) );
                if( node->parent( )->leftChild( ) == node )
                    node->parent( )->setLeftChild( newnode );
                else
                    node->parent( )->setRightChild( newnode );
            } else
                m_root =newnode;
                
            if( replaceBehavior == DELETE_EXISTING ) {

                deleteRecursive( node );   
            }
            else if( replaceBehavior == MOVE_EXISTING ) {
                if( alignRight )
                    newnode->setRightChild( node );
                else
                    newnode->setLeftChild( node );
                node->setParent( newnode );
            }
            return node;
        }
        
       /**
        * @function  remove( )
        * @abstract  removes and deleltes node or subtree
        * @param     n, node or subtree to be removed and deleted    
        * @post      after remove(), n points to an invalid address
        **/
        virtual void remove( node_t *n ) {
            if( !n )
                return;
            if( n->parent( ) ) {
                if( n->parent( )->leftChild( ) == n )
                    n->parent( )->setLeftChild( 0 );
                else if( n->parent( )->rightChild( ) == n )
                    n->parent( )->setRightChild( 0 );
            }
            deleteRecursive( n );
        }
       
       /**
        * @function  clear( )
        * @abstract  clears entire tree
        * @pre       tree may be empty
        * @post      all nodes and data are deallocated
        **/  
        void clear( ) {
            deleteRecursive( m_root );
            m_root =0;
        }
        
       /**
        * @function  empty( )
        * @abstract  test if tree is empty
        * @return    true when empty
        **/ 
        bool isEmpty( ) const {
            return !m_root;
        }
        
      /**
        * @function  root( )
        * @abstract  returns address of the root of the tree
        * @return    the adress of the root of the tree is returned
        * @pre       there needs to be a tree
        **/        
        node_t* root( ){
            return m_root;
        }
        
       /**
        * @function  row( )
        * @abstract  returns an entire row/level in the tree
        * @param     level, the desired row. Zero gives just the root.
        * @return    a list containing all node pointers in that row
        * @pre       level must be positive or zero
        * @post      
        **/ 
        nodelist row( int level ) {
            nodelist rlist;
            getRowRecursive( m_root, rlist, level );
            return rlist;
        }

       /**
        * @function  find( )
        * @abstract  find the first occurrence of info and returns its node ptr
        * @param     haystack, the root of the (sub)tree we want to look in
        *            null if we want to start at the root of the tree
        * @param     needle, the needle in our haystack
        * @return    a pointer to the first occurrence of needle
        * @post      there may be multiple occurrences of needle, we only return 
        *            one. A null-pointer is returned if no needle is found
        **/
        virtual node_t* find( node_t* haystack, const INFO_T& needle ) {
            if( haystack == 0 ) {
                    if( m_root )
                        haystack =m_root;
                    else
                        return 0;
            }
            return findRecursive( haystack, needle );
        }
        
       /**
        * @function  contains( )
        * @abstract  determines if a certain content (needle) is found
        * @param     haystack, the root of the (sub)tree we want to look in
        *            null if we want to start at the root of the tree
        * @param     needle, the needle in our haystack
        * @return    true if needle is found
        **/
        bool contains( node_t* haystack, const INFO_T& needle ) {
            return find( haystack, needle );
        }

       /**
        * @function  toDot( )
        * @abstract  writes tree in Dot-format to a stream
        * @param     out, ostream to write to
        * @pre       out must be a valid stream
        * @post      out (file or cout) with the tree in dot-notation
        **/
        void toDot( ostream& out, const string & graphName ) {
            if( isEmpty( ) )
                return;
            map< node_t *, int> adresses;
            typename map< node_t *, int >::iterator adrIt;
            int i =1;
            int p;
            iterator_pre it;
            iterator_pre tempit;
            adresses[m_root] =0;
            out << "digraph " << graphName << '{' << endl << '"' << 0 << '"';
            for( it =begin_pre( ); it != end_pre( ); ++it ) {
                adrIt =adresses.find( &(*it) );
                if( adrIt == adresses.end( ) ) {
                    adresses[&(*it)] =i;
                    p =i;
                    i ++;
                }
                if( (&(*it))->parent( ) != &(*tempit) )
                  out << ';' << endl << '"' 
                      << adresses.find( (&(*it))->parent( ))->second << '"';
                if( (&(*it)) != m_root )
                    out << " ->  \"" << p << '"';
                tempit =it;
            }
            out << ';' << endl;
            for ( adrIt =adresses.begin( ); adrIt != adresses.end( ); ++adrIt )
                out << adrIt->second << " [label=\""
                    << adrIt->first->info( ) << "\"]";
            out << '}';
        }
        
       /**
        * @function  copyFromNode( )
        * @abstract  copies the the node source and its children to the node 
        *            dest
        * @param     source, the node and its children that need to be copied
        * @param     dest, the node who is going to get the copied children
        * @param     left, this is true if it's a left child.
        * @pre       there needs to be a tree and we can't copy to a root.
        * @post      the subtree that starts at source is now also a child of
        *            dest
        **/        
        void copyFromNode( node_t *source, node_t *dest, bool left ) {
            node_t *acorn =new node_t( dest );
            if(left) {
                if( dest->leftChild( ))
                    return;
                dest->setLeftChild( acorn );
            }
            else {
                if( dest->rightChild( ))
                    return;
                dest->setRightChild( acorn );
            }
            cloneRecursive( source, acorn );
        }

        Tree<INFO_T>& operator=( const Tree<INFO_T>& tree ) {
            clear( );
            if( tree.m_root ) {
                m_root =new node_t( (node_t*)0 );
                cloneRecursive( tree.m_root, m_root );
            }
            return *this;
        }
        
                        
    protected:
       /**
        * @function  cloneRecursive( )
        * @abstract  cloning a subtree to a node
        * @param     source, the node we want to start the cloning process from
        * @param     dest, the node we want to clone to
        * @post      the subtree starting at source is cloned to the node dest
        **/
        void cloneRecursive( node_t *source, node_t* dest ) {
            dest->info() =source->info();
            if( source->leftChild( ) ) {
                node_t *left =new node_t( dest );
                dest->setLeftChild( left );
                cloneRecursive( source->leftChild( ), left );
            }
            if( source->rightChild( ) ) {
                node_t *right =new node_t( dest );
                dest->setRightChild( right );
                cloneRecursive( source->rightChild( ), right );
            }
        }
    
       /**
        * @function  deleteRecursive( )
        * @abstract  delete all nodes of a given tree
        * @param     root, starting point, is deleted last
        * @post      the subtree has been deleted
        **/
        void deleteRecursive( node_t *root ) {
            if( !root )
                return;
            deleteRecursive( root->leftChild( ) );
            deleteRecursive( root->rightChild( ) );
            delete root;
        }
        
       /**
        * @function  getRowCountRecursive( )
        * @abstract  calculate the maximum depth/row count in a subtree
        * @param     root, starting point
        * @param     level, starting level
        * @return    maximum depth/rows in the subtree
        **/
        int getRowCountRecursive( node_t* root, int level ) {
            if( !root )
                return level;
            return max(
                    getRowCountRecursive( root->leftChild( ), level+1 ),
                    getRowCountRecursive( root->rightChild( ), level+1 ) );
        }
    
       /**
        * @function  getRowRecursive( )
        * @abstract  compile a full list of one row in the tree
        * @param     root, starting point
        * @param     rlist, reference to the list so far
        * @param     level, how many level still to go
        * @post      a list of a row in the tree has been made.
        **/
        void getRowRecursive( node_t* root, nodelist &rlist, int level ) {
            // Base-case
            if( !level ) {
                rlist.push_back( root );
            } else if( root ){
                level--;
                if( level && !root->leftChild( ) )
                    for( int i =0; i < (level<<1); ++i )
                        rlist.push_back( 0 );  
                else
                   getRowRecursive( root->leftChild( ), rlist, level );
                
                if( level && !root->rightChild( ) )
                    for( int i =0; i < (level<<1); ++i )
                        rlist.push_back( 0 );  
                else
                    getRowRecursive( root->rightChild( ), rlist, level );
            }
        }
        
        /**
        * @function  findRecursive( )
        * @abstract  first the first occurrence of needle and return its node
        *            ptr
        * @param     haystack, root of the search tree
        * @param     needle, copy of the data to find
        * @return    the node that contains the needle
        **/
        node_t *findRecursive( node_t* haystack, const INFO_T &needle ) {
            if( haystack->info( ) == needle )
                return haystack;
       
            node_t *n =0;
            if( haystack->leftChild( ) )
                n =findRecursive( haystack->leftChild( ), needle );
            if( !n && haystack->rightChild( ) )
                n =findRecursive( haystack->rightChild( ), needle );
            return n;
        }
        
        friend class TreeNodeIterator_pre<INFO_T>;
        friend class TreeNodeIterator_in<INFO_T>;
        TreeNode<INFO_T> *m_root;
        
    private:
        /**
        * @function  getFirstEmptySlot( )
        * @abstract  when a row has a continuous empty space on the right,
        *            find the left-most parent in the above row that has
        *            at least one empty slot.
        * @param     level, how many level still to go
        * @return    the first empty slot where we can put a new node
        * @pre       level should be > 1
        **/
        node_t *getFirstEmptySlot( int level ) {
            node_t *p =0;
            nodelist rlist =row( level-1 ); // we need the parents of this level
            /** changed auto to int **/
            for( auto it =rlist.rbegin( ); it !=rlist.rend( ); ++it ) {
                if( !(*it)->hasChildren( ) )
                    p =(*it);
                else if( !(*it)->rightChild( ) ) {
                    p =(*it);    
                    break;
                } else
                    break;
            }
            return p;
        }
};

#endif

