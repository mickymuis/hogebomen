/**
**/

#include <iostream>
#include "Tree.h"
#include "ExpressionTree.h"
#include <cmath>

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

int main ( ) {

    // Basis dingen
    ExpressionAtom a( 2l );
    cout << a << endl;
    cout << ( a == 2l ) << endl; // true
    ExpressionAtom b( 4.5f );
    cout << ( a + b ) << endl; // 6.5
    Fraction frac = {1, 2}; // 1/2
    ExpressionAtom c( frac );
    cout << ( c + a ) << endl; // 5/2
    cout << ( c + a ).toFloat( ) << endl; // 2.5
    cout << ( a * b ).toInteger( ) << endl; // 9
    Fraction frac2 ={ 3, 4 }; // 3/4
    ExpressionAtom d( frac2 );
    cout << ( c / d ) << endl << endl; // 4/6

    // Ruige dingen :-)
    cout << a.pow( ExpressionAtom( 3l ) ) << endl; // a^3 = 8
    cout << a.pow( ExpressionAtom( -3l ) ) << endl; // a^-3 = 1/8
    a.setInteger( 4l );
    cout << a.pow( ExpressionAtom( Fraction( { 1, 2 } ) ) ) << endl; // a^(1/2) = sqrt(a) = 4
    cout << a.sqrt( ) << endl; // sqrt(4)
    cout << b.sqrt( ) << endl; // sqrt(4.5) ~2.1...
    cout << c.pow( ExpressionAtom( 3l ) ) << endl; // (1/2)^3 = 1/8
    c.setFraction( Fraction( { 1,4 } ) );
    cout << c.sqrt( ) << endl; // sqrt(1/4) = 1/2
    
    cout << "inequality: should be 1 0 0 1 1 1" << endl;
    cout << (a < b) << endl; // 1
    cout << (b < a) << endl; // 0
    cout << (a > b) << endl; // 0
    cout << (c <= d) << endl; // 1
    cout << (a >= 2l ) << endl; // 1
    cout << (b >= Fraction{ 9, 2 }) << endl; // 1
    
    
    
    //return 0;

    /* een onzin test boom
 
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
    
    // Zoeken
    Tree<char>::node_t *n =tree.contains(0, 'Z' );
    if( n )
        cout << "Z gevonden :-(\n";
    n =tree.contains(0, '%' );
    if( n )
        cout << "% gevonden :-)\n";
    
    
    // verwijderen kan ook  
    //tree.remove( n );

    
    // Hele rij selecteren
    Tree<char>::nodelist row=tree.row( 3 );
    for( auto it =row.begin( ); it !=row.end( ); ++it ) {
        if( (*it) )
            cout << **it << " ";
    }
    
   
    cout << endl << "in: ";
    
    // In-orde wandeling
    Tree<char>::iterator_in it2( tree.begin_in( ) );
    
    for( ; it2 !=tree.end_in( ); ++it2 ) {
        cout << *it2 << " ";
    }
    
    cout << endl << "post: ";
    
    // Post-orde wandeling
    Tree<char>::iterator_post it3( tree.begin_post( ) );
    
    for( ; it3 !=tree.end_post( ); ++it3 ) {
        cout << *it3 << " ";
    }
    
    cout << endl;
    
    n =tree.contains(0, '6' ) ;
    tree.insert( '1', n );
    tree.insert( '2', n );
    
    n =tree.contains(0, '%' ) ;
    tree.replace( '?', n, true, Tree<char>::MOVE_EXISTING );
    
    cout << endl << "pre: ";
    
    // Pre-orde wandeling
    Tree<char>::iterator_pre it( tree.begin_pre( ) );
    
    for( ; it !=tree.end_pre( ); ++it ) {
        cout << *it << " ";
    }
    
    cout << endl;
    
  /*  tree.toDot( cout, "Boom" );
    
    cout << endl << endl;
    
    // Lisette was here!
    
    tree.clear();
    
    cout << tree.last() << endl;

    cout << "As I walk through the tree of the shadow of death. I take a look "
         << "at a node and realize there's nothing left." << endl
         << "Gangsta's parserise (+*4^x2*9^x3)." << endl << endl;
    
    ExpressionTree expression( "*2^x4" );
    
    cout << endl << expression.showInOrder( ) << endl;
    
    expression.differentiate( ); */
    
    //ExpressionTree expression( "* * 2 ^ x 3 * 2 ^ x 3" );
    //ExpressionTree expression( "/ * 4 ^ x 3 * 3 ^ 2 x" );
    ExpressionTree expression( "sin ^ 6 * t * 3 x" );
    //ExpressionTree expression( "* ^ 3 x ^ x 2" );
    
    ExpressionTree expression2 = expression.differentiate( "x" );
    ofstream file ("file2.txt");
    expression2.toDot(file, "HOI");
    expression2.generateInOrder( cout );
    cout << endl;
    // Nieuwe zooi van Micky :-)
    // met af en toe een beetje Lis' rommel :D lol
    
    /*list<ExpressionAtom> tokenlist =ExpressionTree::tokenize("* 3 x" );
    for( auto it=tokenlist.begin( ); it != tokenlist.end( ); ++it ) cout << *it << endl;*/
       
    //printTree<char>( tree, 5 ); // Werkt alleen aan het einde, anders segfault. Waarom?
    //printTree<ExpressionAtom>( expression2, 7 );
 
    expression2.simplify( );
    
    
    ExpressionTree expression3( "+ + * 2 -x - 16 -x * 3 ln e" ); // 2*(-x) + 16-(-x) + 3*ln(e)
    ofstream file2 ("file3.txt");
    expression3.toDot(file2, "HOI"); 
    cout << "Evaluatie testen: f(8)=";
    expression3.evaluate( "x", 8l ).generateInOrder( cout );
    cout << endl;
    printTree<ExpressionAtom>( expression3, 5 );
    return 0;
}
