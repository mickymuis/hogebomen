/**
 * ExpressionTree: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    ExpressionTree.cc
 * @date    26-10-2014
 **/
 
#include "ExpressionTree.h"

list<ExpressionAtom> ExpressionTree::tokenize( const string& str ) {

    list<ExpressionAtom> tokenlist;
    stringstream ss( str );
    while( ss.good( ) ) {
        string token;
        ss >> token;
        ExpressionAtom atom;
        bool unary_minus =false;
        
        if( token.size( ) > 1 && token[0] == '-' ) {
            token =token.substr( 1 );
            unary_minus =true;
        }
        
        if( token.find( "." ) != string::npos ) { // Float
            try {
                atom.setFloat( (unary_minus ? -1.0f : 1.0f) 
                                * std::stof( token ) );
                unary_minus =false;
            } catch( std::invalid_argument& e ) {
                throw ParserException( string ("Invalid float `") 
                                        + token 
                                        + string("`") );
            }
        }
        else if( token == "*" )
            atom.setOperator( ExpressionAtom::PRODUCT );
        else if( token == "/" )
            atom.setOperator( ExpressionAtom::DIVISION );
        else if( token == "+" )
            atom.setOperator( ExpressionAtom::SUM );
        else if( token == "-" )
            atom.setOperator( ExpressionAtom::DIFFERENCE );
        else if( token == "^" )
            atom.setOperator( ExpressionAtom::EXPONENT );
        else if( token == "sin" )
            atom.setFunction( ExpressionAtom::SIN );
        else if( token == "cos" )
            atom.setFunction( ExpressionAtom::COS );
        else if( token == "tan" )
            atom.setFunction( ExpressionAtom::TAN );
        else if( token == "ln" )
            atom.setFunction( ExpressionAtom::LN );
        else if( token == "log" )
            atom.setFunction( ExpressionAtom::LOG );
        else if( token == "sqrt" )
            atom.setFunction( ExpressionAtom::SQRT );
        else if( token == "abs" )
            atom.setFunction( ExpressionAtom::ABS );
        else if( token == "e" )
            atom.setFunction( ExpressionAtom::E );
        else if( token == "pi" )
            atom.setFunction( ExpressionAtom::PI );
        else if( token.find( "/" ) != string::npos ) { // Fraction
            size_t pos =token.find( "/" );
            Fraction f;
            try {
                f.numerator =(unary_minus ? -1 : 1) 
                            * std::stoi( token.substr( 0, pos ) );
                f.denominator =std::stoi( token.substr( pos + 1 ) );
                atom.setFraction( f );
                unary_minus =false;
            }
            catch( std::invalid_argument& e ){
                throw ParserException( string ("Invalid fraction `") 
                                       + token 
                                       + string("`") );
            }
        }
        else {
            try { // Try integer
                atom.setInteger( (unary_minus ? -1 : 1) * std::stol( token ) );
                unary_minus =false;
                
            } // Try variable
            catch( invalid_argument& e ){
                for( unsigned int i =0; i < token.size( ); ++i )
                    if( !isalpha( token[i] ) )
                        throw ParserException( string ("Invalid token `") 
                                               + token 
                                               + string("`") );
                atom.setNamed( token );
            }
        }
         
        if( unary_minus )
            tokenlist.push_back( ExpressionAtom::UNARY_MINUS );   
        tokenlist.push_back( atom );
    }
    return tokenlist;
}

void ExpressionTree::fromString( const string& expression ) {
    list<ExpressionAtom> tokenlist;
                
    try{
        tokenlist =ExpressionTree::tokenize( expression );
    } catch( ParserException & e ) {
        throw e;
    }
    
    Tree<ExpressionAtom>::node_t *n =0;
    
    for( auto atom : tokenlist ) {
        if( !n ) {
            n =pushBack( atom );
            continue;
        }
        while ( !n->info( ).arity( ) 
        || ( n->info( ).arity( ) == 1 && n->hasChildren( ) )
        || ( n->info( ).arity( ) == 2 && n->isFull( ) ) ) {
            n =n->parent ( );
            if( !n )
                throw ParserException( "Argument count to arity mismatch" );
        }
        
        n =insert( atom, n );
    }
}

ExpressionTree ExpressionTree::differentiate( string varName ) {
    ExpressionTree derivatree;
    differentiate( root( ), varName, derivatree.root( ), derivatree );
    derivatree.simplify( );
    return derivatree;
}

void ExpressionTree::simplify( ) {
    m_root =simplifyRecursive( root( ) );
}

ExpressionTree 
ExpressionTree::evaluate( string varName, ExpressionAtom expr ) const {
    ExpressionTree t( *this );
    t.mapVariable( varName, expr );
    t.simplify( );
    return std::move( t );
}

ExpressionTree
ExpressionTree::evaluate( const map<string,ExpressionAtom>& varmap ) const {
    ExpressionTree t( *this );
    t.mapVariables( varmap );
    t.simplify( );
    return std::move( t );
}

void ExpressionTree::mapVariable( string varName, ExpressionAtom expr ) {
    map<string,ExpressionAtom> varmap;
    varmap[varName] =expr;
    mapVariables( varmap );
}

void ExpressionTree::mapVariables( const map<string,ExpressionAtom>& varmap ) {
    for( auto &node : *this ) {
        if( node.info( ).type( ) == ExpressionAtom::NAMED_OPERAND ) {
            auto it =varmap.find( node.info( ).getNamed( ) );
            if( it != varmap.cend( ) )
                node =it->second;
        }
    }
}

void ExpressionTree::differentiate( node_t * n, string varName,
                                    node_t * derivative,
                                    ExpressionTree &derivatree ) {
    ExpressionAtom atom =(*n);   
    switch( atom.type( ) ) {
        case ExpressionAtom::OPERATOR:
        switch( atom.getOperator( ) ) {
            case ExpressionAtom::SUM:
            case ExpressionAtom::DIFFERENCE:
                differentiateAddition( &(*n), varName, derivative, derivatree );
                break;
            case ExpressionAtom::PRODUCT:
                differentiateProduct( &(*n), varName, derivative, derivatree );
                break;
            case ExpressionAtom::EXPONENT:
                differentiateExponent( &(*n), varName, derivative, derivatree );
                break;
            case ExpressionAtom::DIVISION:
                differentiateDivision( &(*n), varName, derivative, derivatree );
                break;
        }        
        break;
        case ExpressionAtom::FUNCTION:
            differentiateFunction( &(*n), varName, derivative, derivatree );
            break;
        case ExpressionAtom::NAMED_OPERAND:
            atom.getNamed( ) == string( varName ) ?
            derivatree.insert( 1L, derivative ) :
            derivatree.insert( 0L, derivative );
            break;
        default:
            derivatree.insert( 0L, derivative );
    }
}

void ExpressionTree::differentiateFunction( node_t * n, string varName,
                                            node_t * derivative,
                                            ExpressionTree &derivatree ) {
    Tree<ExpressionAtom> tempTree;
    Tree<ExpressionAtom>::node_t *temp;
    ExpressionAtom atom =(*n);
    switch( atom.getFunction( ) ){
        case ExpressionAtom::SIN:
            temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
            differentiate( (*n).leftChild( ), varName, temp, derivatree );
            temp =derivatree.insert( ExpressionAtom::COS, temp );
            copyFromNode( (*n).leftChild( ), temp, true );
            break;
        case ExpressionAtom::TAN:;
            temp =tempTree.insert( ExpressionAtom::DIVISION, tempTree.root( ) );
            temp =tempTree.insert( ExpressionAtom::SIN, temp );
            copyFromNode( (*n).leftChild( ), temp, true );
            temp =temp->parent( );
            temp =tempTree.insert( ExpressionAtom::COS, temp );
            copyFromNode( (*n).leftChild( ), temp, true );
            differentiate( tempTree.root( ), varName, derivative, derivatree );
            tempTree.clear( );        
            break;
        case ExpressionAtom::COS:
            temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
            temp =derivatree.insert( ExpressionAtom::UNARY_MINUS, temp );
            differentiate( (*n).leftChild( ), varName, temp, derivatree );
            temp =temp->parent( );
            temp =derivatree.insert( ExpressionAtom::SIN, temp );
            copyFromNode( (*n).leftChild( ), temp, true );
            break;
        case ExpressionAtom::LN:
            if( contains( (*n).leftChild( ), string( varName ) ) ) {
                temp =derivatree.insert( ExpressionAtom::DIVISION, derivative);
                differentiate( (*n).leftChild( ), varName, temp, derivatree );
                copyFromNode( (*n).leftChild( ), temp, false );
            }
            else
                derivatree.insert( 0L, derivative); 
            break;
        case ExpressionAtom::SQRT:
            temp =derivatree.insert( ExpressionAtom::DIVISION, derivative );
            differentiate( (*n).leftChild( ), varName, temp, derivatree );
            temp =derivatree.insert( ExpressionAtom::PRODUCT, temp );
            derivatree.insert( 2L, temp );
            copyFromNode( &(*n), temp, false );
            break;
        case ExpressionAtom::LOG:
            temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
            temp =derivatree.insert( ExpressionAtom::DIVISION, temp );
            derivatree.insert( 1L, temp);
            temp =derivatree.insert( ExpressionAtom::LN, temp );
            copyFromNode( (*n).leftChild( ), temp, true );
            temp =temp->parent( )->parent( );
            temp =derivatree.insert( ExpressionAtom::DIVISION, temp );
            differentiate( (*n).rightChild( ), varName, temp, derivatree );
            copyFromNode( (*n).rightChild( ), temp, false );        
            break;
        case ExpressionAtom::ABS:
            if( (*n).leftChild( )->info( ).type( ) ==
                ExpressionAtom::NAMED_OPERAND &&
                (*n).leftChild( )->info( ).getNamed( ) == string( varName ) ) {
                temp =derivatree.insert( ExpressionAtom::DIVISION, derivative );
                copyFromNode( (*n).leftChild( ), temp, true );
                copyFromNode( &(*n), temp, false );
            }
            else {
                temp =derivatree.insert( ExpressionAtom::DIVISION, derivative );
                temp =derivatree.insert( ExpressionAtom::PRODUCT, temp );
                copyFromNode( (*n).leftChild( ), temp, true );
                differentiate( (*n).leftChild( ), varName, temp, derivatree );
                temp =temp->parent( );
                copyFromNode( &(*n), temp, false );
            }
            break;
    }
}

void ExpressionTree::differentiateAddition( node_t * n, string varName,
                                            node_t * derivative,
                                            ExpressionTree &derivatree ) {
    Tree<ExpressionAtom>::node_t *temp;
    ExpressionAtom atom =(*n);
    if( atom.getOperator( ) == ExpressionAtom::SUM )
        temp =derivatree.insert( ExpressionAtom::SUM, derivative );
    else
        temp =derivatree.insert( ExpressionAtom::DIFFERENCE, derivative );
    differentiate( (*n).leftChild( ), varName, temp, derivatree );
    if( (*n).rightChild( ) )
        differentiate( (*n).rightChild( ), varName, temp, derivatree );
}

void ExpressionTree::differentiateDivision( node_t * n, string varName,
                                            node_t * derivative,
                                            ExpressionTree &derivatree ) {
    Tree<ExpressionAtom>::node_t *temp;
    temp =derivatree.insert( ExpressionAtom::DIVISION, derivative );
    temp =derivatree.insert( ExpressionAtom::DIFFERENCE, temp );
    temp =derivatree.insert( ExpressionAtom::PRODUCT, temp);
    copyFromNode( (*n).rightChild( ), temp, true );
    differentiate( (*n).leftChild( ), varName, temp, derivatree );
    temp =temp->parent( );
    temp =derivatree.insert( ExpressionAtom::PRODUCT, temp);
    copyFromNode( (*n).leftChild( ), temp, true );
    differentiate( (*n).rightChild( ), varName, temp, derivatree );
    temp =temp->parent( )->parent( );
    temp =derivatree.insert( ExpressionAtom::EXPONENT, temp );
    copyFromNode( (*n).rightChild( ), temp, true );
    derivatree.insert( 2L, temp );
}

void ExpressionTree::differentiateProduct( node_t * n, string varName,
                                           node_t * derivative,
                                           ExpressionTree &derivatree ) {
    Tree<ExpressionAtom>::node_t *temp;
    if( (*n).leftChild( )->info( ).isNumericOperand( ) ) {
        // n * x
        if( (*n).rightChild( )->info( ).type( ) ==
            ExpressionAtom::NAMED_OPERAND &&
            (*n).rightChild( )->info( ).getNamed( ) == string( varName ) )
            derivatree.insert( (*n).leftChild( )->info( ), derivative );
        // n * f(x)
        else {
            temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
             derivatree.insert( (*n).leftChild( )->info( ), temp );
             differentiate( (*n).rightChild( ), varName, temp, derivatree );
        }
    }
    else if( (*n).rightChild( )->info( ).isNumericOperand( ) ) {
        // x * n
        if( (*n).leftChild( )->info( ).type( ) ==
            ExpressionAtom::NAMED_OPERAND &&
            (*n).leftChild( )->info( ).getNamed( ) == string( varName ) )
            derivatree.insert( (*n).rightChild( )->info( ), derivative );
        // f(x) * n
        else {
            temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
             derivatree.insert( (*n).rightChild( )->info( ), temp );
             differentiate( (*n).leftChild( ), varName, temp, derivatree );
        }
    }
    // f(x) * g(x)
    else {
        temp =derivatree.insert( ExpressionAtom::SUM, derivative );
        temp =derivatree.insert( ExpressionAtom::PRODUCT, temp );
        copyFromNode( (*n).rightChild( ), temp, true );
        differentiate( (*n).leftChild( ), varName, temp, derivatree );
        temp =temp->parent( );
        temp =derivatree.insert( ExpressionAtom::PRODUCT, temp );
        copyFromNode( (*n).leftChild( ), temp, true );
        differentiate( (*n).rightChild( ), varName, temp, derivatree );
    }
}

void ExpressionTree::differentiateExponent( node_t * n, string varName,
                                            node_t * derivative,
                                            ExpressionTree &derivatree ) {
    Tree<ExpressionAtom>::node_t *temp;
    Tree<ExpressionAtom> tempTree;
    if( contains( (*n).leftChild( ), string( varName ) ) ) {
        // f(x) ^ g(x)
        if( contains( (*n).rightChild( ), string( varName ) ) ) {
            // f(x)^g(x) =e^(ln(f(x))g(x))
            temp =tempTree.insert( ExpressionAtom::EXPONENT, tempTree.root( ) );
            tempTree.insert( ExpressionAtom::E, temp );
            temp =tempTree.insert( ExpressionAtom::PRODUCT, temp );
            temp =tempTree.insert( ExpressionAtom::LN, temp );
            copyFromNode( (*n).leftChild( ), temp, true );
            temp =temp->parent( );
            copyFromNode( (*n).rightChild( ), temp, false );
            differentiate( tempTree.root( ), varName, derivative, derivatree );
            tempTree.clear( );
        }
        // f(x) ^ n
        else {
            if( (*n).leftChild( )->info( ).type( ) == 
                ExpressionAtom::NAMED_OPERAND && 
                (*n).leftChild( )->info( ).getNamed( ) == 
                string( varName )  ) {
                // x ^ 0
                if( (*n).rightChild( )->info( )  == 0L )
                    derivatree.insert( 1L, derivative );
                // x ^ 1
                else if( (*n).rightChild( )->info( ) == 1L )
                    derivatree.insert( string( "x" ), derivative );
                // x ^ n ( n > 1 )
                else if( (*n).rightChild( )->info( ) > 1L ) {
                    temp =derivatree.insert( ExpressionAtom::PRODUCT, 
                                             derivative );
                    derivatree.insert( (*n).rightChild( )->info( ), temp );
                    temp =derivatree.insert( ExpressionAtom::EXPONENT , temp );
                    derivatree.insert( string( varName ) , temp );
                    derivatree.insert( (*n).rightChild( )->info( ) - 1L, temp );                        
                }
                // x ^ n ( n < 0 )
                else if( (*n).rightChild( )->info( ) < 0L ) {
                    temp =derivatree.insert( ExpressionAtom::DIVISION, 
                                             derivative);
                    derivatree.insert( (*n).rightChild( )->info( ), temp );
                    temp =derivatree.insert( ExpressionAtom::EXPONENT, temp);
                    derivatree.insert( string( varName ), temp);
                    derivatree.insert( (*n).rightChild( )->info( ) - 
                                       (*n).rightChild( )->info( ) - 
                                       (*n).rightChild( )->info( ) + 1L, temp);
                }
            }
            else {
                temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
                temp =derivatree.insert( ExpressionAtom::PRODUCT, temp );
                copyFromNode( (*n).rightChild( ), temp, true );
                temp =derivatree.insert( ExpressionAtom::EXPONENT, temp );
                copyFromNode( (*n).leftChild( ), temp, true );
                derivatree.insert( (*n).rightChild( )->info( ) - 
                                   (*n).rightChild( )->info( ) - 1L, temp );
                temp =temp->parent( )->parent( );
                differentiate( (*n).leftChild( ), varName, temp, derivatree );
            }
        }
    }
    //e ^ f(x)
    else if( (*n).leftChild( )->info( ).type( ) == ExpressionAtom::FUNCTION &&
             (*n).leftChild( )->info( ).getFunction( ) == ExpressionAtom::E ) {
        temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative) ;
        differentiate( (*n).rightChild( ), varName, temp, derivatree );
        copyFromNode( &(*n), temp, false);  
    }
    // n ^ f(x)
    else if( contains( (*n).rightChild( ), string( varName ) ) ) {
        temp =derivatree.insert( ExpressionAtom::PRODUCT, derivative );
        temp =derivatree.insert( ExpressionAtom::PRODUCT, temp );
        differentiate( (*n).rightChild( ), varName, temp, derivatree );
        temp =derivatree.insert( ExpressionAtom::LN, temp );
        copyFromNode( (*n).leftChild( ), temp, true );
        temp =temp->parent( )->parent( );
        temp =derivatree.insert( ExpressionAtom::EXPONENT, temp );
        copyFromNode( (*n).leftChild( ), temp, true );
        copyFromNode( (*n).rightChild( ), temp, false );
    }
}


ExpressionTree::node_t *
ExpressionTree::simplifyRecursive( node_t* root ) {
    if( !root )
        return 0;
        
    node_t *n =root->leftChild( );
    node_t *m =root->rightChild( );
    
    /* cascade( ): removes root and child n, replaces root with child m */
    auto cascade =[&]( ) -> node_t* {
        remove( n );
        if( root->parent( ) ) {
            if( root ==root->parent( )->leftChild( ) )
                root->parent( )->setLeftChild( m );
            else
                root->parent( )->setRightChild( m );
            m->setParent( root->parent( ) );
        }
        else
            m->setParent( 0 );
        delete root;
        return m;
    };
    
    /* merge( ): 
       replaces the root by the result of its operation on the children */
    auto merge =[&]( ) -> node_t* {

        ExpressionAtom &lhs =root->leftChild( )->info( );
        ExpressionAtom &rhs =root->rightChild( )->info( );
        ExpressionAtom &op =root->info( );
        
        assert( lhs.isNumericOperand( ) && rhs.isNumericOperand( ) );
        
        switch( op.getOperator( ) ) {
            case ExpressionAtom::SUM:
                op =std::move( lhs + rhs );
                break;
            case ExpressionAtom::DIFFERENCE:
                op =std::move( lhs - rhs );
                break;
            case ExpressionAtom::PRODUCT:
                op =std::move( lhs * rhs );
                break;
            case ExpressionAtom::DIVISION:
                op =std::move( lhs / rhs );
                break;
            case ExpressionAtom::EXPONENT:
                op =std::move( lhs.pow( rhs ) );
                break;
        }
        
        remove( m );
        remove( n );
        return root;
    };
    
    /* mergeInto( ): replaces the root by expr and removes the children */
    auto mergeInto =[&]( ExpressionAtom&& expr ) -> node_t* {
        remove( m );
        remove( n );
        root->info( ) =std::move( expr );
        return root;
    };
    
    bool stop =false;
    do {
    
        if( n ) {
            n =simplifyRecursive( n );
            if( n && !n->hasChildren( ) ) {
                // Simplify the one-fraction
                if( n->info( ).type( ) == ExpressionAtom::FRACTION_OPERAND
                        && n->info( ).getFraction( ).numerator == 1 )
                    n->info( ).setInteger( 1 );
                
                // two operands-case
                if( n->info( ).isNumericOperand( ) 
                    && m && m->info( ).isNumericOperand( ) ) {
                    root =merge( );
                    return root;
                }
                        
                // 1 case
                if( n->info( ).isNumericOperand( ) 
                    && compare( 1.0f, n->info( ).toFloat( ) ) ) {
                    if( root->info( ) == ExpressionAtom::PRODUCT ) {
                        root =cascade( );
                    }
                    else if( root->info( ) == ExpressionAtom::EXPONENT ) {
                        if( n == root->leftChild( ) )
                            root =mergeInto( 1l );
                        else
                            root =cascade( );
                    }
                    else if( root->info( ) == ExpressionAtom::DIVISION ) {
                        if( n == root->rightChild( ) )
                            root =cascade( );
                    }
                }
                // 0 case
                else if( n->info( ).isNumericOperand( ) 
                         && compare( 0.0f, n->info( ).toFloat( ) ) ) {
                    if( root->info( ) == ExpressionAtom::SUM )
                        root =cascade( );
                    else if( root->info( ) == ExpressionAtom::PRODUCT ) {
                        root =mergeInto( 0l );
                    }
                    else if( root->info( ) == ExpressionAtom::DIVISION ) {
                        if( n == root->leftChild( ) )
                            root =mergeInto( 0l );
                    }
                    else if( root->info( ) == ExpressionAtom::DIFFERENCE ) {
                        if( n == root->rightChild( ) )
                            root =cascade( );
                        else if( m && m->info( ).isNumericOperand( ) ) {
                            root =mergeInto( ExpressionAtom( -1l ) 
                                             * m->info( ) );
                        }
                    }
                    else if( root->info( ) == ExpressionAtom::EXPONENT ) {
                        if( n == root->leftChild( ) ) {
                            if( m && m->info( ).isNumericOperand( )
                                  && compare( 1.0f, m->info( ).toFloat( ) ) )
                                root =mergeInto( 1l );
                            else {
                                root =mergeInto( 0l );
                            }    
                        }
                        else {
                            root =mergeInto( 1l );
                        }
                    }
                }
                // trivial functions
                else if( root->info( ).type( ) == ExpressionAtom::FUNCTION ) {
                    switch( root->info( ).getFunction( ) ) {
                        case ExpressionAtom::UNARY_MINUS:
                            if( n->info( ).isNumericOperand( ) )
                                root =mergeInto( ExpressionAtom( -1l ) 
                                                 * n->info( ) );
                            break;
                        case ExpressionAtom::LN: // ln(e)
                            if( n->info( ) == ExpressionAtom::E )
                                root =mergeInto( 1l );
                            break;
                    } 
                }
            }
        }
    
        if( stop )
            break;
            
        n =root->rightChild( );
        m =root->leftChild( );
        stop =true;
    } while( n );                

return root;
}

void 
ExpressionTree::generateInOrderRecursive( node_t *root, ostream& buffer ) const{
    if( !root )
        return;
    
    if( root->info( ).type( ) == ExpressionAtom::FUNCTION ) {   // Function type
        bool enclose =root->isFull( ) // Only enclose in ( )'s if neccessary
            || ( root->leftChild( ) && !root->leftChild( )->hasChildren( ) )
            || ( root->rightChild( ) && !root->rightChild( )->hasChildren( ) );
            
        if( root->info( ).getFunction( ) == ExpressionAtom::UNARY_MINUS ) {
            buffer << '(';
            enclose =false;
        }
        
        buffer << root->info( );
            
        if( enclose )
            buffer << '(';
            
        generateInOrderRecursive( root->leftChild( ), buffer );
        
        if( root->isFull( ) ) // Function with two params, otherwise no comma
            buffer << ',';
            
        generateInOrderRecursive( root->rightChild( ), buffer );
        
        if( enclose )
            buffer << ')';
            
        if( root->info( ).getFunction( ) == ExpressionAtom::UNARY_MINUS )
            buffer << ')';
    } else {    // Operator+operands type
        if( root->hasChildren( ) && root != m_root )
            buffer << '(';
        
        generateInOrderRecursive( root->leftChild( ), buffer );
        
        if( !(root->info( ) == ExpressionAtom::PRODUCT  // implicit multipl.
            && root->leftChild( ) 
            && root->leftChild( )->info( ).isNumericOperand( ) ) )
            buffer << root->info( );
        generateInOrderRecursive( root->rightChild( ), buffer );
        
        if( root->hasChildren( ) && root != m_root )
            buffer << ')';
    }
}
