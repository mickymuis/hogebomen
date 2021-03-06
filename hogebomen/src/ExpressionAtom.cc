/**
 * ExpressionAtom: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    ExpressionAtom.cc
 * @date    26-10-2014
 **/
 
#include "ExpressionAtom.h"
#include "ExpressionTree.h"

/* Fraction overloads */

bool operator ==( const Fraction& lhs, const Fraction& rhs ) {
    // This function should be in general namespace
    return ExpressionTree::compare( (float)lhs.numerator/(float)lhs.denominator,
                                    (float)rhs.numerator/(float)rhs.denominator );
}

Fraction operator+( const Fraction& lhs, const Fraction& rhs ) {
    Fraction f;
    if( lhs.denominator == rhs.denominator ) {
        f.denominator =lhs.denominator;
        f.numerator =lhs.numerator + rhs.numerator;
    } else {
        f.denominator =lhs.denominator * rhs.denominator;
        f.numerator =lhs.numerator * rhs.denominator 
                    + rhs.numerator * lhs.denominator;
    }
    return f;
}

Fraction operator-( const Fraction& lhs, const Fraction& rhs ) {
    Fraction f;
    if( lhs.denominator == rhs.denominator ) {
        f.denominator =lhs.denominator;
        f.numerator =lhs.numerator - rhs.numerator;
    } else {
        f.denominator =lhs.denominator * rhs.denominator;
        f.numerator =lhs.numerator * rhs.denominator 
                    - rhs.numerator * lhs.denominator;
    }
    return f;
}

Fraction operator*( const Fraction& lhs, const Fraction& rhs ) {
    Fraction f;
    f.denominator =lhs.denominator * rhs.denominator;
    f.numerator =lhs.numerator * rhs.numerator;
    return f;
}

Fraction operator/( const Fraction& lhs, const Fraction& rhs ) {
    Fraction f;
    f.denominator =lhs.denominator * rhs.numerator;
    f.numerator =lhs.numerator * rhs.denominator;
    return f;
}

/* ExpressionAtom implementation */

ExpressionAtom::ExpressionAtom( AtomType t, long int atom ) : m_type( t ) {
    m_atom.integer_atom =std::move( atom );
}

ExpressionAtom::ExpressionAtom( float atom ) : m_type( FLOAT_OPERAND ) {
    m_atom.float_atom =std::move( atom );
}

ExpressionAtom::ExpressionAtom( long int atom ) : m_type( INTEGER_OPERAND ) {
    m_atom.integer_atom =std::move( atom );
}

ExpressionAtom::ExpressionAtom( string var ) : m_type( NAMED_OPERAND ) {
    m_named_atom =std::move( var );
}

ExpressionAtom::ExpressionAtom( OperatorType op ) : m_type( OPERATOR ) {
    m_atom.integer_atom =std::move( op );
}

ExpressionAtom::ExpressionAtom( Function func ) : m_type( FUNCTION ) {
    m_atom.integer_atom =std::move( func );
}

ExpressionAtom::ExpressionAtom( Fraction frac ) : m_type( FRACTION_OPERAND ) {
    m_atom.fraction_atom =std::move( frac );
}

bool ExpressionAtom::operator ==( const ExpressionAtom& rhs ) const {
    if( rhs.m_type != m_type )
        return false;
    switch( m_type ) {
        case UNDEFINED:
            return false;
        case INTEGER_OPERAND:
        case OPERATOR:
        case FUNCTION:
            return m_atom.integer_atom == rhs.m_atom.integer_atom;
        
        case FLOAT_OPERAND:
            return m_atom.float_atom == rhs.m_atom.float_atom;
            
        case FRACTION_OPERAND:
            return m_atom.fraction_atom == rhs.m_atom.fraction_atom;
            
        case NAMED_OPERAND:
            return m_named_atom == rhs.m_named_atom;
        
    }
    return false;
}

bool ExpressionAtom::operator <( const ExpressionAtom& rhs ) const {
    if( !rhs.isNumericOperand( ) || !isNumericOperand( ) )
        return false;
    return toFloat( ) < rhs.toFloat( );
}

bool ExpressionAtom::operator >( const ExpressionAtom& rhs ) const {
    if( !rhs.isNumericOperand( ) || !isNumericOperand( ) )
        return false;
    return toFloat( ) > rhs.toFloat( );
}

bool ExpressionAtom::operator <=( const ExpressionAtom& rhs ) const {
    if( !rhs.isNumericOperand( ) || !isNumericOperand( ) )
        return false;
    return toFloat( ) <= rhs.toFloat( );
}

bool ExpressionAtom::operator >=( const ExpressionAtom& rhs ) const {
    if( !rhs.isNumericOperand( ) || !isNumericOperand( ) )
        return false;
    return toFloat( ) >= rhs.toFloat( );
}

ExpressionAtom ExpressionAtom::operator+( const ExpressionAtom& rhs ) const {
    ExpressionAtom a;
    if( isNumericOperand( ) && rhs.isNumericOperand( ) ) {
        if( m_type == FLOAT_OPERAND || rhs.m_type == FLOAT_OPERAND )
            a.setFloat( toFloat( ) + rhs.toFloat( ) );
        else if( m_type == FRACTION_OPERAND || rhs.m_type == FRACTION_OPERAND ) 
            a.setFraction( toFraction( ) + rhs.toFraction( ) );
        else
            a.setInteger( getInteger( ) + rhs.getInteger( ) );
    }
    return a;
}

ExpressionAtom ExpressionAtom::operator-( const ExpressionAtom& rhs ) const {
    ExpressionAtom a;
    if( isNumericOperand( ) && rhs.isNumericOperand( ) ) {
        if( m_type == FLOAT_OPERAND || rhs.m_type == FLOAT_OPERAND )
            a.setFloat( toFloat( ) - rhs.toFloat( ) );
        else if( m_type == FRACTION_OPERAND || rhs.m_type == FRACTION_OPERAND ) 
            a.setFraction( toFraction( ) - rhs.toFraction( ) );
        else
            a.setInteger( getInteger( ) - rhs.getInteger( ) );
    }
    return a;
}

ExpressionAtom ExpressionAtom::operator*( const ExpressionAtom& rhs ) const {
    ExpressionAtom a;
    if( isNumericOperand( ) && rhs.isNumericOperand( ) ) {
        if( m_type == FLOAT_OPERAND || rhs.m_type == FLOAT_OPERAND )
            a.setFloat( toFloat( ) * rhs.toFloat( ) );
        else if( m_type == FRACTION_OPERAND || rhs.m_type == FRACTION_OPERAND ) 
            a.setFraction( toFraction( ) * rhs.toFraction( ) );
        else
            a.setInteger( getInteger( ) * rhs.getInteger( ) );
    }
    return a;
}

ExpressionAtom ExpressionAtom::operator/( const ExpressionAtom& rhs ) const {
    ExpressionAtom a;
    if( isNumericOperand( ) && rhs.isNumericOperand( ) ) {
        if( m_type == FLOAT_OPERAND || rhs.m_type == FLOAT_OPERAND )
            a.setFloat( toFloat( ) / rhs.toFloat( ) );
        else if( m_type == FRACTION_OPERAND || rhs.m_type == FRACTION_OPERAND ) 
            a.setFraction( toFraction( ) / rhs.toFraction( ) );
        else
            a.setInteger( getInteger( ) / rhs.getInteger( ) );
    }
    return a;
}

ExpressionAtom ExpressionAtom::pow( const ExpressionAtom& power ) const {
    ExpressionAtom a;
    if( isNumericOperand( ) && power.isNumericOperand( ) ) {
 
        if( power.m_type == FRACTION_OPERAND 
            && power.m_atom.fraction_atom == Fraction( { 1, 2 } ) ) {
            return sqrt( );
        }
        else if( m_type == FLOAT_OPERAND 
            || power.m_type == FLOAT_OPERAND 
            || power.m_type == FRACTION_OPERAND )
            a.setFloat( ::powf( toFloat( ), power.toFloat( ) ) );
        else if( m_type == FRACTION_OPERAND ) {
            Fraction f;
            f.numerator =m_atom.fraction_atom.numerator;
            f.denominator =::pow( m_atom.fraction_atom.denominator,
                                power.getInteger( ) );
            a.setFraction( f );
        }
        else {
            if( power.getInteger( ) > 0 )
                a.setInteger( ::powl( getInteger( ), power.getInteger( ) ) );
            else if( power.getInteger( ) == 0 )
                a.setInteger( 1 );
            else {
                Fraction f;
                f.numerator =1;
                f.denominator =::pow( m_atom.integer_atom,
                                    abs( power.m_atom.integer_atom ) );
                a.setFraction( f );
            }
        }
    }
    return a;
}

ExpressionAtom ExpressionAtom::sqrt( ) const {
    ExpressionAtom a;
    if( isNumericOperand( ) ) {
        if( m_type == FLOAT_OPERAND  ) {
            a.setFloat( ::sqrtf( toFloat( ) ) );
        }
        else if( m_type == FRACTION_OPERAND ) {
            float f =::sqrtf( (float)m_atom.fraction_atom.denominator );
            if( ceil( f ) == floor( f ) )
                a.setFraction( 
                    Fraction( { m_atom.fraction_atom.numerator, (int)f } ) );
            else
                a.setFloat( f );
        }
        else {
            float f =::sqrtf( (float)m_atom.integer_atom );
            if( ceil( f ) == floor( f ) )
                a.setInteger( (int)f );
            else
                a.setFloat( f );
        }
    }
    return a;
}

float ExpressionAtom::toFloat( ) const {
    if( m_type == INTEGER_OPERAND )
        return (float)m_atom.integer_atom;
    else if( m_type == FLOAT_OPERAND )
        return m_atom.float_atom;
    else if( m_type == FRACTION_OPERAND )
        return (float)m_atom.fraction_atom.numerator /
               (float)m_atom.fraction_atom.denominator;
               
    return float( );
}
long int ExpressionAtom::toInteger( ) const {
    if( m_type == INTEGER_OPERAND )
        return m_atom.integer_atom;
    else if( m_type == FLOAT_OPERAND )
        return (long int)m_atom.float_atom;
    else if( m_type == FRACTION_OPERAND )
        return m_atom.fraction_atom.numerator /
               m_atom.fraction_atom.denominator;
               
    return int( );
}
Fraction ExpressionAtom::toFraction( ) const {
    Fraction frac;
    if( m_type == FRACTION_OPERAND )
        return m_atom.fraction_atom;
    else if( m_type == INTEGER_OPERAND ) {
        frac.numerator =m_atom.integer_atom;
        frac.denominator =1;
    }
    return frac;
}

short ExpressionAtom::arity( ) const {
    switch( type( ) ) {
        case ExpressionAtom::INTEGER_OPERAND:
        case ExpressionAtom::FLOAT_OPERAND:
        case ExpressionAtom::FRACTION_OPERAND:
        case ExpressionAtom::NAMED_OPERAND:
            return 0;
            
        case ExpressionAtom::OPERATOR:
            return 2;
        case ExpressionAtom::FUNCTION:
            switch( getFunction( ) ) {
                case ExpressionAtom::SIN:
                case ExpressionAtom::COS:
                case ExpressionAtom::TAN:
                case ExpressionAtom::LN:
                case ExpressionAtom::SQRT:
                case ExpressionAtom::ABS:
                case ExpressionAtom::UNARY_MINUS:
                    return 1;
                case ExpressionAtom::E:
                case ExpressionAtom::PI:
                    return 0;
                case ExpressionAtom::LOG:
                    return 2;
            }
            break;
        case ExpressionAtom::UNDEFINED:
        default:
            return 0;
    }
    return 0;
}

/* General namespace */

ostream& operator <<( ostream& out, const ExpressionAtom& atom ) {
    switch( atom.type( ) ) {
        case ExpressionAtom::INTEGER_OPERAND:
            out << atom.getInteger( );
            break;
        case ExpressionAtom::FLOAT_OPERAND:
            out << atom.getFloat( );
            break;
        case ExpressionAtom::FRACTION_OPERAND:
            out << atom.getFraction( ).numerator << "/" 
                 << atom.getFraction( ).denominator;
            break;
        case ExpressionAtom::NAMED_OPERAND:
            out << atom.getNamed( );
            break;
        case ExpressionAtom::OPERATOR:
            switch( atom.getOperator( ) ) {
                case ExpressionAtom::SUM:
                    out << "+";
                    break;
                case ExpressionAtom::DIFFERENCE:
                    out << "-";
                    break;
                case ExpressionAtom::PRODUCT:
                    out << "*";
                    break;
                case ExpressionAtom::DIVISION:
                    out << "/";
                    break;
                case ExpressionAtom::EXPONENT:
                    out << "^";
                    break;
            }        
            break;
        case ExpressionAtom::FUNCTION:
            switch( atom.getFunction( ) ) {
                case ExpressionAtom::SIN:
                    out << "sin";
                    break;
                case ExpressionAtom::COS:
                    out << "cos";
                    break;
                case ExpressionAtom::TAN:
                    out << "tan";
                    break;
                case ExpressionAtom::LOG:
                    out << "log";
                    break;
                case ExpressionAtom::LN:
                    out << "ln";
                    break;
                case ExpressionAtom::SQRT:
                    out << "sqrt";
                    break;
                case ExpressionAtom::ABS:
                    out << "abs";
                    break;
                case ExpressionAtom::E:
                    out << "e";
                    break;
                case ExpressionAtom::PI:
                    out << "pi";
                    break;
                case ExpressionAtom::UNARY_MINUS:
                    out << "-";
                    break;
            }
            break;
        case ExpressionAtom::UNDEFINED:
        default:
            break;
    }
    return out;
}
