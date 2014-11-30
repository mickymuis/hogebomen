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
    
    SplayTree<int> bst;
    
    auto root =bst.pushBack( 10 );
    auto a =bst.pushBack( 5 );
    bst.pushBack( 15 );
    
    bst.pushBack( 25 );
    auto b =bst.pushBack( 1 );
    bst.pushBack( -1 );
    auto c =bst.pushBack( 11 );
    bst.pushBack( 12 );
    
    //printTree<int>( bst, 5 );
    
    //a->swapWith( b );
    //bst.remove( bst.find( 0, 15 ) );
    //bst.replace( -2, bst.find( 0, 5 ) );
    
    
    printTree<int>( bst, 5 );
    
    //bst.remove( root );
    
    bst.splay( c );
    
    printTree<int>( bst, 5 );
    
    // Test AVLTree //

    AVLTree<int> test;
    test.insert(2);
    auto d =test.insert(4);
    test.insert(8);
    test.insert(7);
    test.insert(6);
    test.insert(1);
    test.insert(0);
    cout << "AVL Boompje:" << endl;
    printTree<int>( test, 5 );
    cout << d->info( ) << " verwijderen: " << endl; 
    test.remove( d );
    printTree<int>( test, 5 );

    return 0;
}
