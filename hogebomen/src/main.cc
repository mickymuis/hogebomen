/**
 * main.cc: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    main.cc
 * @date    26-10-2014
 **/

#include <iostream>
#include "BinarySearchTree.h"
#include "Tree.h"
#include "AVLTree.h"
#include "SplayTree.h"
#include "Treap.h"
#include <string>

using namespace std;

// Makkelijk voor debuggen, moet nog beter
template<class T> void printTree( Tree<T> tree, int rows ) {
    typename Tree<T>::nodelist list =tree.row( 0 );
    int row =0;
    while( !list.empty( ) && row < rows ) {
        string offset;
        for( int i =0; i < ( 1 << (rows - row) ) - 1 ; ++i )
            offset += ' ';
        
        
        for( auto it =list.begin( ); it != list.end( ); ++it ) {
            if( *it )
                cout << offset << (*it)->info() << " " << offset;
            else
                cout << offset << ". " << offset;
        }
        cout << endl;
        row++;
        list =tree.row( row );
    }
}

int main ( int argc, char **argv ) {

    /* BST hieronder */

    cout << "BST:" << endl;
    BinarySearchTree<int> bst;
    
   /* auto root =bst.pushBack( 10 );
    bst.pushBack( 5 );
    bst.pushBack( 15 );
    
    bst.pushBack( 25 );
    bst.pushBack( 1 );
    bst.pushBack( -1 );
    bst.pushBack( 11 );
    bst.pushBack( 12 );*/
    
    Tree<int>* bstP =&bst; // Dit werkt gewoon :-)
    
    auto root =bstP->pushBack( 10 );
    bstP->pushBack( 5 );
    bstP->pushBack( 15 );
    
    bstP->pushBack( 25 );
    bstP->pushBack( 1 );
    bstP->pushBack( -1 );
    bstP->pushBack( 11 );
    bstP->pushBack( 12 );
    
    //printTree<int>( bst, 5 );
    
    
    //bst.remove( bst.find( 0, 15 ) );
    //bst.replace( -2, bst.find( 0, 5 ) );
    
    
    printTree<int>( bst, 5 );
    
    bst.remove( root );

    
    printTree<int>( bst, 5 );

    /* Splay Trees hieronder */
    
    cout << "Splay Boom:" << endl;
    SplayTree<int> splay;
    
    splay.pushBack( 10 );
    auto a =splay.pushBack( 5 );
    splay.pushBack( 15 );
    
    splay.pushBack( 25 );
    auto b =splay.pushBack( 1 );
    splay.pushBack( -1 );
    auto c =splay.pushBack( 11 );
    splay.pushBack( 12 );
    
    //printTree<int>( splay, 5 );
    
    //a->swapWith( b );
    //splay.remove( splay.find( 0, 15 ) );
    //splay.replace( -2, splay.find( 0, 5 ) );
    
    
    printTree<int>( splay, 5 );
    
    //splay.remove( root );
    
    splay.splay( c );
    
    printTree<int>( splay, 5 );
    
    // Test AVLTree //

    AVLTree<char> test;
    test.insert('a');
    auto d =test.insert('b');
    test.insert('c');
    test.insert('d');
    test.insert('e');
    test.insert('f');
    test.insert('g');
    cout << "AVL Boompje:" << endl;
    printTree<char>( test, 5 );
    cout << d->info( ) << " verwijderen: " << endl; 
    test.remove( d );
    printTree<char>( test, 5 );

    // Test Treap //

    cout << "Treap" << endl;

    Treap<int> testTreap(5);
    testTreap.insert(2);
    testTreap.insert(3);
    auto e =testTreap.insert(4);
    testTreap.insert(5);
    printTree<int>( testTreap, 5 );
    testTreap.remove(e);
    printTree<int>( testTreap, 5 );

    return 0;
}
