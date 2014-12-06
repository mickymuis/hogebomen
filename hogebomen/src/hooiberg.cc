/**
 * hooiberg.cc: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    helehogebomen.cc
 * @date    10-12-2014
 **/

#include "BinarySearchTree.h"
#include "Tree.h"
#include "AVLTree.h"
#include "SplayTree.h"
#include "Treap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

int printUsage( const char* prog ) {

    std::cout << "Reads an input file and searches it for a set of strings\n\n"
         << "Usage: " << prog << " [type] [haystack] [needles]\n"
         << "\t[type]\t\tTree type to use. One of `splay', `avl', `treap', `bst'\n"
         << "\t[haystack]\tInput file, delimited by newlines\n"
         << "\t[needles]\tFile containing sets of strings to search for, delimited by newlines\n"
         << std::endl;
    return 0;
}

bool extractNeedles( std::vector<string> &list, std::ifstream &file ) {
    string needle;
    while( !file.eof( ) ) {
        std::getline( file, needle );
        if( needle.size( ) )
            list.push_back( needle );
    }
    return true;
}

bool fillTree( BinarySearchTree<string>* tree, std::ifstream &file ) {
    string word;
    while( !file.eof( ) ) {
        std::getline( file, word );
        if( word.size( ) )
            tree->pushBack( word );
    }
    return true;
}

void findAll( std::vector<string> &list, BinarySearchTree<string>* tree ) {
    for( auto needle : list ) {
        if( tree->find( 0, needle ) )
            std::cout << "Found `" << needle << '\'' << std::endl;
        else
            std::cout << "Didn't find `" << needle << '\'' << std::endl;
    }
} 

int main ( int argc, char **argv ) {

    enum MODE { NONE =0, BST, AVL, SPLAY, TREAP };
    int mode =NONE;
    
    if( argc < 4 )
        return printUsage( argv[0] );
    
    if( std::string( argv[1] ) == "bst" )
        mode =BST;
    else if( std::string( argv[1] ) == "avl" )
        mode =AVL;
    else if( std::string( argv[1] ) == "treap" )
        mode =TREAP;
    if( std::string( argv[1] ) == "splay" )
        mode =SPLAY;

    if( !mode )
        return printUsage( argv[0] );
 
    std::ifstream fhaystack( argv[2] );
    if( !fhaystack.good( ) ) {
        std::cerr << "Could not open " << argv[2] << std::endl;
        return -1;          
    }
    
    std::ifstream fneedles( argv[3] );
    if( !fneedles.good( ) ) {
        std::cerr << "Could not open " << argv[3] << std::endl;
        return -1;          
    }
    
    std::vector<string> needles;
    if( !extractNeedles( needles, fneedles ) ) {
        cerr << "Could not read a set of strings to search for." << endl;
        return -1;          
    }
    
    BinarySearchTree<string> *tree;
    switch( mode ) {
        case BST:
            tree = new BinarySearchTree<string>();
            break;
        case AVL:
            tree = new AVLTree<string>();
            break;
        case SPLAY:
            tree = new SplayTree<string>();
            break;
        case TREAP:
            tree = new Treap<string>();
            break;
    }
    
    if( !fillTree( tree, fhaystack ) ) {
        cerr << "Could not read the haystack." << endl;
        return -1;          
    }
    
    findAll( needles, tree );
       
    //printTree<string>(*tree, 6);
    
    fhaystack.close( );
    fneedles.close( );
    return 0;   
}