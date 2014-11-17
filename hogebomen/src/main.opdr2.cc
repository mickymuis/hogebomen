/**
 * main.cc: Simpel programma dat de functionaliteit 
 *   van ExpressionTree demonstreert
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    main.cc
 * @date    26-10-2014
 **/

#include <iostream>
#include "ExpressionTree.h"
#include <string>

using namespace std;

/**
* @function  showEvaluation( )
* @abstract  subinterface for evaluation of a tree
* @param     tree, the tree we want to evaluate 
* @post      the tree is evaluated
**/ 
void showEvaluation( ExpressionTree& tree ) {
    string var;
    float value;
    
    cout << "What is the variable?" << endl;
    getline( cin, var );
    cout << "What is the value you want to fill in?" << endl;
    cin >> value;
    cout << "It has been evaluated to: " << endl;

    tree.evaluate( var, value ).generateInOrder( cout );
    
    cout << endl;
}

/**
* @function  saveToDot( )
* @abstract  subinterface for the conversion to Dot-notation of a tree
* @param     tree, the tree we want to convert
* @post      the tree is converted
**/ 
void saveToDot( ExpressionTree& tree ) {
    string input;
    ofstream file;
    
    cout << "To what file should the tree be written?" << endl;
    getline( cin, input );
    file.open( input );
    cout << "How should we call the tree?" << endl;
    getline( cin, input );

    tree.toDot( file, input );
    cout << "Done!" << endl;

}

int main ( ) {
    string input;
    string moreInput;
    char inputChar;
    char inputTree;
    ExpressionTree expression;
    ExpressionTree derivative;

    cout << "With this program you can differentiate an expression. "
         << "The program has been made by Lisette and Micky. Enjoy!" << endl 
         << endl
         << "What's the expression in prefix notation?" << endl;
    getline( cin, input );
    expression =input;
    
    while( inputChar != 'q') {
        cout << "Do you want to [d]ifferentiate, [s]implify, [e]valuate, "
             << "[c]onvert to Dot or [q]uit?" << endl;
        cin >> inputChar;
        cin.ignore( );
        switch( inputChar ) {
            case 'c':
            case 'e':
                if( !derivative.isEmpty( ) ) {
                    cout << "The [d]erivative or the [o]riginal tree?" << endl;
                    cin >> inputTree;
                    cin.ignore( );
                    if( ! (inputChar == 'o' ||  inputChar == 'd') )
                        cout << "Invalid Input." << endl;
                        
                }
                else    
                    inputTree ='o';
                    
                if( inputChar == 'c' )
                    saveToDot( inputTree == 'o' ? expression : derivative );
                else
                    showEvaluation( inputTree == 'o' ? expression : derivative );
                break;
                
            case 'd':
                cout << "What is the variable?" << endl;
                getline( cin, input );
                derivative =expression.differentiate( input );
                cout << "The tree has been derived to :";
                derivative.generateInOrder( cout );
                cout << endl;
                break;
            case 's':
                expression.simplify( );
                cout << "the tree has been simplified to : ";
                expression.generateInOrder( cout );
                cout << endl;
                break;
            case 'q':
                cout << "Thank you for having used this program. Goodbye."
                     << endl;
                break;
            default:
                cout << "You have entered an invalid character." << endl;
        }
    }
    return 0;
}
