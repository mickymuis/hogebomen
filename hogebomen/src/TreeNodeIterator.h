/**
 * TreeNodeIterator: Provides a set of iterators that follow the STL-standard
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    TreeNodeIterator.h
 * @date    26-10-2014
 **/
 
#include <iterator>
#include "TreeNode.h"

template <class INFO_T> class TreeNodeIterator 
                        : public std::iterator<std::forward_iterator_tag, 
                                               TreeNode<INFO_T>> {
    public:
        typedef TreeNode<INFO_T> node_t;
        
       /**
        * @function  TreeNodeIterator( )
        * @abstract  (copy)constructor
        * @pre       TreeNodeIterator is abstract and cannot be constructed
        **/
        TreeNodeIterator( node_t* ptr =0 ) : p( ptr ) { }
        TreeNodeIterator( const TreeNodeIterator& it ) : p( it.p ) { }
        
       /**
        * @function  (in)equality operator overload
        * @abstract  Test (in)equality for two TreeNodeIterators
        * @param     rhs, right-hand side of the comparison
        * @return    true if both iterators point to the same node (==)
        *            false if both iterators point to the same node (!=)
        **/
        bool operator == (const TreeNodeIterator& rhs) { return p==rhs.p; }
        bool operator != (const TreeNodeIterator& rhs) { return p!=rhs.p; }
        
       /**
        * @function  operator*( )
        * @abstract  Cast operator to node_t reference
        * @return    The value of the current node
        * @pre       Must point to a valid node
        **/ 
        node_t& operator*( ) { return *p; }
        
       /**
        * @function  operator++( )
        * @abstract  pre- and post increment operators
        * @return    TreeNodeIterator that has iterated one step
        **/
        TreeNodeIterator &operator++( ) { next( ); return *this; }
        TreeNodeIterator operator++( int ) 
            { TreeNodeIterator tmp( *this ); operator++( ); return tmp; }
    protected:
    
       /**
        * @function  next( ) //(pure virtual)
        * @abstract  Implement this function to implement your own iterator
        */
        virtual bool next( ){ return false; }// =0;
        node_t *p;
};

template <class INFO_T> class TreeNodeIterator_pre 
                        : public TreeNodeIterator<INFO_T> {
    public:
        typedef TreeNode<INFO_T> node_t;
        
        TreeNodeIterator_pre( node_t* ptr =0 ) 
            : TreeNodeIterator<INFO_T>( ptr ) { }
        TreeNodeIterator_pre( const TreeNodeIterator<INFO_T>& it ) 
            : TreeNodeIterator<INFO_T>( it ) { }
        TreeNodeIterator_pre( const TreeNodeIterator_pre& it ) 
            : TreeNodeIterator<INFO_T>( it.p ) { }

        TreeNodeIterator_pre &operator++( ) { next( ); return *this; }
        TreeNodeIterator_pre operator++( int ) 
            { TreeNodeIterator_pre tmp( *this ); operator++( ); return tmp; }
       
    protected:
        using TreeNodeIterator<INFO_T>::p;
        
       /**
        * @function  next( )
        * @abstract  Takes one step in pre-order traversal
        * @return    returns true if such a step exists
        */
        bool next( ) {
            if( !p )
                return false;
            if( p->hasChildren( ) ) { // a possible child that can be the next
                p =p->leftChild( ) ? p->leftChild( ) : p->rightChild( );
                return true;
            }
            else if( p->hasParent( ) // we have a right brother
                    && p->parent( )->rightChild( )
                    && p->parent( )->rightChild( ) != p ) {
                p =p->parent( )->rightChild( );
                return true;
            }
            else if( p->hasParent( ) ) { // just a parent, thus we go up
                TreeNode<INFO_T> *tmp =p->parent( );
                while( tmp->parent( ) ) {
                    if( tmp->parent( )->rightChild( ) 
                            && tmp->parent( )->rightChild( ) != tmp ) {
                        p =tmp->parent( )->rightChild( );
                        return true;
                    }
                    tmp =tmp->parent( );
                }
            }
            // Nothing left
            p =0;
            return false;    
        }
      
};

template <class INFO_T> class TreeNodeIterator_in 
                        : public TreeNodeIterator<INFO_T>{
    public:
        typedef TreeNode<INFO_T> node_t;
        
        TreeNodeIterator_in( node_t* ptr =0 ) 
            : TreeNodeIterator<INFO_T>( ptr ) { }
        TreeNodeIterator_in( const TreeNodeIterator<INFO_T>& it ) 
            : TreeNodeIterator<INFO_T>( it ) { }
        TreeNodeIterator_in( const TreeNodeIterator_in& it ) 
            : TreeNodeIterator<INFO_T>( it.p ) { }

        TreeNodeIterator_in &operator++( ) { next( ); return *this; }
        TreeNodeIterator_in operator++( int ) 
            { TreeNodeIterator_in tmp( *this ); operator++( ); return tmp; }
       
    protected:
        using TreeNodeIterator<INFO_T>::p;
       /**
        * @function  next( )
        * @abstract  Takes one step in in-order traversal
        * @return    returns true if such a step exists
        */
        bool next( ) {
            if( p->rightChild( ) ) {
                p =p->rightChild( );
                while( p->leftChild( ) )
                    p =p->leftChild( );
                return true;
            }
            else if( p->parent( ) && p->parent( )->leftChild( ) == p ) {
                p =p->parent( );
                return true;
            } else if( p->parent( ) && p->parent( )->rightChild( ) == p ) {
                p =p->parent( );
                while( p->parent( ) && p == p->parent( )->rightChild( ) ) {
                    p =p->parent( );
                }
                if( p )
                    p =p->parent( );
                if( p )
                    return true;
                else
                    return false;
            }
            // Er is niks meer
            p =0;
            return false;    
        }
};

template <class INFO_T> class TreeNodeIterator_post 
                        : public TreeNodeIterator<INFO_T>{
    public:
        typedef TreeNode<INFO_T> node_t;
        
        TreeNodeIterator_post( node_t* ptr =0 ) 
            : TreeNodeIterator<INFO_T>( ptr ) { }
        TreeNodeIterator_post( const TreeNodeIterator<INFO_T>& it ) 
            : TreeNodeIterator<INFO_T>( it ) { }
        TreeNodeIterator_post( const TreeNodeIterator_post& it ) 
            : TreeNodeIterator<INFO_T>( it.p ) { }

        TreeNodeIterator_post &operator++( ) { next( ); return *this; }
        TreeNodeIterator_post operator++( int ) 
            { TreeNodeIterator_post tmp( *this ); operator++( ); return tmp; }
       
    protected:
        using TreeNodeIterator<INFO_T>::p;
       /**
        * @function  next( )
        * @abstract  Takes one step in post-order traversal
        * @return    returns true if such a step exists
        */
        bool next( ) {
        
            if( p->hasParent( ) // We have a right brother
                    && p->parent( )->rightChild( )
                    && p->parent( )->rightChild( ) != p ) {
                p =p->parent( )->rightChild( );
                while( p->leftChild( ) )
                    p =p->leftChild( );
                return true;
            } else if( p->parent( ) ) {
                p =p->parent( );
                return true;
            }
            // Nothing left
            p =0;
            return false;    
        }
};
