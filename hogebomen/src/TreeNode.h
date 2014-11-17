/**
 * Treenode: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    Treenode.h
 * @date    26-10-2014
 **/

#ifndef TREENODE_H
#define TREENODE_H

using namespace std;

template <class INFO_T> class Tree;
class ExpressionTree;

template <class INFO_T> class TreeNode
{
    public:
       /**
        * @function  TreeNode( )
        * @abstract  Constructor, creates a node
        * @param     info, the contents of a node
        * @param     parent, the parent of the node 
        * @post      A node has been created.
        **/   
      	TreeNode( const INFO_T& info, TreeNode<INFO_T>* parent =0 ) 
      	    : m_lchild( 0 ), m_rchild( 0 ) {
      	    m_info =info;
      	    m_parent =parent;
      	}
      	
       /**
        * @function  TreeNode( )
        * @abstract  Constructor, creates a node
        * @param     parent, the parent of the node    
        * @post      A node has been created.
        **/
      	TreeNode( TreeNode<INFO_T>* parent =0 )
      	    : m_lchild( 0 ), m_rchild( 0 ) {
      	    m_parent =parent;
      	}
      	
       /**
        * @function  =
        * @abstract  Sets a nodes content to N
        * @param     n, the contents you want the node to have
        * @post      The node now has those contents.
        **/
        void operator =( INFO_T n ) { m_info =n; }

       /**
        * @function  INFO_T( ), info( )
        * @abstract  Returns the content of a node
        * @return    m_info, the contents of the node
        **/        
        operator INFO_T( ) const { return m_info; }
        const INFO_T &info( ) const { return m_info; }
        INFO_T &info( ) { return m_info; }          
        /**
        * @function  atRow( )
        * @abstract  returns the level or row-number of this node
        * @return    row, an int of row the node is at
        **/
        int atRow( ) const { 
            const TreeNode<INFO_T> *n =this;
            int row =0;
            while( n->parent( ) ) {
                n =n->parent( );
                row++;
            }
            return row;
        }

       /**
        * @function  parent( ), leftChild( ), rightChild( )
        * @abstract  returns the adress of the parent, left child and right
        *            child respectively
        * @return    the adress of the requested family member of the node
        **/        
        TreeNode<INFO_T> *parent( ) const { return m_parent; }
        TreeNode<INFO_T> *leftChild( ) const { return m_lchild; }
        TreeNode<INFO_T> *rightChild( ) const { return m_rchild; }
        
        /**
        * @function  swapWith( )
        * @abstract  Swaps this node with another node in the tree
        * @param     n, the node to swap this one with
        * @pre       both this node and n must be in the same parent tree
        * @post      n will have the parent and children of this node
        *            and vice verse. Both nodes retain their data.
        **/
        void swapWith( TreeNode<INFO_T>* n ) {
            bool this_wasLeftChild =false, n_wasLeftChild =false;
            if( parent( ) && parent( )->leftChild( ) == this )
                this_wasLeftChild =true;
            if( n->parent( ) && n->parent( )->leftChild( ) == n ) 
                n_wasLeftChild =true;
            
            // Swap the family info
            TreeNode<INFO_T>* newParent =
                ( n->parent( ) == this ) ? n : n->parent( );
            TreeNode<INFO_T>* newLeft =
                ( n->leftChild( ) == this ) ? n :n->leftChild( );
            TreeNode<INFO_T>* newRight =
                 ( n->rightChild( ) == this ) ? n :n->rightChild( );
            
            n->setParent( parent( ) == n ? this : parent( ) );
            n->setLeftChild( leftChild( ) == n ? this : leftChild( ) );
            n->setRightChild( rightChild( ) == n ? this : rightChild( ) );
            
            setParent( newParent );
            setLeftChild( newLeft );
            setRightChild( newRight );
            
            // Restore applicable pointers
            if( n->leftChild( ) )
                n->leftChild( )->setParent( n );
            if( n->rightChild( ) )
                n->rightChild( )->setParent( n );
            if( leftChild( ) )
                leftChild( )->setParent( this );
            if( rightChild( ) )
                rightChild( )->setParent( this );
            if( n->parent( ) ) {
                if( this_wasLeftChild )
                    n->parent( )->setLeftChild( n );
                else
                    n->parent( )->setRightChild( n );
            }
            if( parent( ) ) {
                if( n_wasLeftChild )
                    parent( )->setLeftChild( this );
                else
                    parent( )->setRightChild( this );
            }
        }
        
        /**
        * @function  sibling( )
        * @abstract  returns the address of the sibling
        * @return    the address to the sibling or zero if there is no sibling
        **/
        TreeNode<INFO_T>* sibling( ) {
            if( parent( )->leftChild( ) == this )
                return parent( )->rightChild( );
            else if( parent( )->rightChild( ) == this )
                return parent( )->leftChild( );
            else
                return 0;
        }

       /**
        * @function  hasChildren( ), hasParent( ), isFull( )
        * @abstract  Returns whether the node has children, has parents or is
        *            full (has two children) respectively
        * @param     
        * @return    true or false, depending on what is requested from the node.
        *            if hasChildren is called and the node has children, it will
        *            return true, otherwise false.
        *            If hasParent is called and the node has a parent, it will
        *            return true, otherwise false.
        *            If isFull is called and the node has two children, it will
        *            return true, otherwise false.
        **/                
        bool hasChildren( ) const { return m_lchild || m_rchild; }
        bool hasParent( ) const { return m_parent; }
        bool isFull( ) const { return m_lchild && m_rchild; }

    protected:
        friend class Tree<INFO_T>;
        friend class ExpressionTree;
        
       /**
        * @function  setParent( ), setLeftChild( ), setRightChild( )
        * @abstract  sets the parent, left child and right child of the
        *            particular node respectively
        * @param     p, the node we want to set a certain family member of
        * @return    void  
        * @post      The node now has a parent, a left child or a right child
        *            respectively.
        **/ 
        void setParent( TreeNode<INFO_T> *p ) { m_parent =p; }
        void setLeftChild( TreeNode<INFO_T> *p ) { m_lchild =p; }
        void setRightChild( TreeNode<INFO_T> *p ) { m_rchild =p; }

    private:
        INFO_T m_info;
        TreeNode<INFO_T> *m_parent;
        TreeNode<INFO_T> *m_lchild;
        TreeNode<INFO_T> *m_rchild;
};

/**
* @function  <<
* @abstract  the contents of the node are returned
* @param     out, in what format we want to get the contents
* @param     rhs, the node of which we want the contents
* @return    the contents of the node.
**/ 
template <class INFO_T> ostream &operator <<(ostream& out, const TreeNode<INFO_T> & rhs ) {
    out << rhs.info( );
    return out;
}

#endif


