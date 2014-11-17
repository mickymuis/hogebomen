/**
 * main2.cc: Simpel programma dat de functionaliteit 
 *   van Tree demonstreert
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    main2.cc
 * @date    26-10-2014
 **/

#include <iostream>
#include "Tree.h"

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

int main ( ) {
    /* random tree
 
                 =
         *              /
      +     -        :      %
     1 2   3 4      5 6    7 8
    */    
    
    Tree<char> tree;
        
    tree.pushBack( '=' );
    tree.pushBack( '*' );
    tree.pushBack( '/' );
    tree.pushBack( '+' );
    tree.pushBack( '-' );
    tree.pushBack( ':' );
    tree.pushBack( '%' );
    tree.pushBack( '1' );
    tree.pushBack( '2' );
    tree.pushBack( '3' );
    tree.pushBack( '4' );
    tree.pushBack( '5' );
    tree.pushBack( '6' );
    tree.pushBack( '7' );
    tree.pushBack( '8' );

    cout << endl << "in-order traversal: ";
    
    // In-order traversal
    Tree<char>::iterator_in it2( tree.begin_in( ) );
    
    for( ; it2 !=tree.end_in( ); ++it2 ) {
        cout << *it2 << " ";
    }
    
    cout << endl << "post-order traversal: ";
    
    // Post-order traversal
    Tree<char>::iterator_post it3( tree.begin_post( ) );
    
    for( ; it3 !=tree.end_post( ); ++it3 ) {
        cout << *it3 << " ";
    }
     
    cout << endl << "pre-order traversal: ";
    
    // Pre-order traversal
    Tree<char>::iterator_pre it( tree.begin_pre( ) );
    
    for( ; it !=tree.end_pre( ); ++it ) {
        cout << *it << " ";
    }
    
    cout << endl;
    
    printTree<char>( tree, 4 );
    
    return 0;
}
