/**
 * ExpressionTree: 
 *
 * @author Micky Faas (s1407937)
 * @author Lisette de Schipper (s1396250)
 * @file ExpressionTree.h
 * @date 10-10-2014
 **/

#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include "Tree.h"
#include "ExpressionAtom.h"
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;

class ParserException : public exception
{
    public:   
       ParserException( const string &str ) : s( str ) {}
       ~ParserException() throw () {}
       const char* what() const throw() { return s.c_str(); }
       
    private:
       string s;
};

class ExpressionTree : public Tree<ExpressionAtom>
{
    public:
       /**
        * @function  ExpressionTree( )
        * @abstract  Constructor, creates an object of the tree.
        * @post      The tree has been declared.
        **/    
        ExpressionTree( ) : Tree<ExpressionAtom>() { }

       /**
        * @function  ExpressionTree( )
        * @abstract  fromString is called to make a tree from the string.
        * @param     str, a string that will be parsed to create the three.
        * @post      The tree has been declared and initialized.
        **/
        ExpressionTree( const string& str ) : Tree<ExpressionAtom>() {
            fromString( str );
        }
        
       /**
        * @function  tokenize( )
        * @abstract  Breaks the string provided by fromString up into tokens
        * @param     str, a string expression
        * @return    tokenlist, a list of ExpressionAtom's
        * @pre       str needs to be a correct space-separated string
        * @post      We have tokens of the string
        **/ 
        static list<ExpressionAtom> tokenize( const string& str );
  
       /**
        * @function  fromString( )
        * @abstract  calls tokenize to generate tokens from an expression and
        *            fills the ExpressionTree with them.
        * @param     expression, a string expression
        * @post      The provided expression will be converted to an
        *            ExpressionTree if it has the right syntax.
        **/
        void fromString( const string& expression );

       /**
        * @function  differentiate( )
        * @abstract  calls the other differentiate function and returns the
        *            derivative in the form of a tree
        * @param     string varName, the variable
        * @return    the derivative of the original function in the form of a 
        *            tree
        * @pre       There needs to be a tree
        * @post      Derivatree has been changed by the private differentiate 
        *            function.
        **/      
        ExpressionTree differentiate( string varName );
        
       /**
        * @function  simplify( )
        * @abstract  Performs mathematical simplification on the expression
        * @post      Upon simplification, nodes may be deleted.
        *            references and iterators may become invalid
        **/
        void simplify( );
        
       /**
        * @function  evaluate( )
        * @abstract  Evaluates the tree as far as possible given a variable and 
        *            its mapping
        * @return    A new ExpressionTree containing the evaluation (may be a 
        *            single node)
        * @param     varName, variable name to match (e.g, 'x')
        * @param     expr, expression to put in place of varName
        **/
        ExpressionTree evaluate( string varName, ExpressionAtom expr ) const;
        
       /**
        * @function  evaluate( )
        * @abstract  Evaluates the tree as far as possible using a given mapping
        * @return    A new ExpressionTree containing the evaluation (may be a 
        *            single node)
        * @param     varmap, list of varName/expr pairs
        **/
        ExpressionTree evaluate( const map<string,ExpressionAtom>& varmap ) const;
        
       /**
        * @function  mapVariable( )
        * @abstract  Replaces a variable by an expression
        * @param     varName, variable name to match (e.g, 'x')
        * @param     expr, expression to put in place of varName
        * @post      Expression may change, references and iterators
        *            remain valid after this function.
        **/
        void mapVariable( string varName, ExpressionAtom expr );
        
       /**
        * @function  mapVariables( )
        * @abstract  Same as mapVariable( ) for a set of variables/expressions
        * @param     varmap, list of varName/expr pairs       
        * @post      Expression may change, references and iterators
        *            remain valid after this function.
        **/
        void mapVariables( const map<string,ExpressionAtom>& varmap );
        
       /**
        * @function  generateInOrder( )
        * @abstract  generates the infix notation of the tree.
        * @param     out, the way in which we want to see the output
        * @post      The infix notation of the tree has been generated
        **/ 
        void generateInOrder( ostream& out ) const {
            generateInOrderRecursive( m_root, out );
        }
       
    private:
       /**
        * @function  differentiate( ), differentiateExponent( ),
        *            differentiateDivision( ), differentiateProduct( ),
        *            differentiateFunction( ), differentiateAddition( )
        * @abstract  differentiates ExpressionTree and places the derivative in
        *            the tree assigned to the last variable
        * @param     n, the node we need to start differentiating from
        * @param     varName, variable name to match (e.g, 'x')
        * @param     derivative, the node we want to differentiate from
        * @param     derivatree, the tree we want to differentiate to
        * @return    the derivative of the original function in the form of a 
        *            tree
        * @pre       There needs to be a tree
        * @post      The derivatree has been changed, now it shows the
        *            derivative of ExpressionTree.
        **/
        void differentiate( node_t * n, string varName,
                            node_t * derivative,
                            ExpressionTree &derivatree );
        void differentiateExponent( node_t * n, string varName, 
                                    node_t * derivative, 
                                    ExpressionTree &derivatree );
        void differentiateDivision( node_t * n, string varName,
                                    node_t * derivative,
                                    ExpressionTree &derivatree );
        void differentiateProduct( node_t * n, string varName,
                                   node_t * derivative,
                                   ExpressionTree &derivatree );
        void differentiateFunction( node_t * n, string varName,
                                    node_t * derivative,
                                    ExpressionTree &derivatree );
        void differentiateAddition( node_t * n, string varName,
                                    node_t * derivative,
                                    ExpressionTree &derivatree );
        
       /**
        * @function  simplify( )
        * @abstract  Performs mathematical simplification on the expression
        * @param     root, root of the subtree to simplify
        * @return    New node in place of the passed value/node for root 
        * @post      Upon simplification, nodes may be deleted.
        *            references and iterators may become invalid
        **/        
        node_t *simplifyRecursive( node_t* root );
        
       /**
        * @function  generateInOrderRecursive( )
        * @abstract  Recursively goes through the tree to get the infix notation
        *            of the tree
        * @param     root, the node we're looking at
        * @param     buffer, the output    
        * @post      Eventually the infix notation of the tree with parenthesis
        *            has been generated. 
        **/ 
        void generateInOrderRecursive( node_t *root, ostream& buffer ) const;
        
    public:
       /**
        * @function  compare( )
        * @abstract  Throws a parser expression.
        * @param     f1, the first value we want to compare
        * @param     f2, the second value we want to compare
        * @param     error, the marge in which the difference is accepted.
        * @return    if the difference between f1 and f2 is smaller or equal to
        *            error
        * @post      A ParserException is thrown.
        **/ 
        static bool compare( const float &f1, const float &f2, float &&error =0.00001f ) {
            return ( fabs( f1-f2 ) <= error );
        }
        
};
#endif

