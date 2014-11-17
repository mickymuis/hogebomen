/**
 * ExpressionAtom: 
 *
 * @author  Micky Faas (s1407937)
 * @author  Lisette de Schipper (s1396250)
 * @file    ExpressionAtom.h
 * @date    26-10-2014
 **/

#ifndef EXPRESSIONATOM_H
#define EXPRESSIONATOM_H

#include <ostream>
#include <string>
#include <cmath>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

/**
* @function  operator==( )
* @abstract  Test equality for two Fractions
* @param     lhs and rhs are two sides of the comparison
* @return    true upon equality
* @post      Two Fraction are equal if
*            lhs.numerator/lhs.denominator == rhs.numerator/rhs.denominator
**/
bool operator ==( const Fraction& lhs, const Fraction& rhs );

/**
* @function  Arithmetic operators +, -, *, /
* @abstract  Arithmetic result of two Fractions
* @param     lhs and rhs are two sides of the expression
**/
Fraction operator+( const Fraction& lhs, const Fraction& rhs );
Fraction operator-( const Fraction& lhs, const Fraction& rhs );
Fraction operator*( const Fraction& lhs, const Fraction& rhs );
Fraction operator/( const Fraction& lhs, const Fraction& rhs );

using namespace std;

class ExpressionAtom {
    public:
        enum AtomType {
            UNDEFINED =0x0,
            INTEGER_OPERAND,
            FLOAT_OPERAND,
            FRACTION_OPERAND,
            NAMED_OPERAND, // Variable
            OPERATOR,
            FUNCTION
        };
        
        enum OperatorType {
            SUM,
            DIFFERENCE,
            PRODUCT,
            DIVISION,
            EXPONENT
        };
        
        enum Function {
            SIN,
            COS,
            TAN,
            LOG,
            LN,
            SQRT,
            ABS,
            E,
            PI,
            UNARY_MINUS
        };
        
       /**
        * @function  ExpressionAtom( )
        * @abstract  Constructor, defines an ExpressionAtom for various types
        * @param     Either one of AtomType, OperatorType, Function,
        *            float, long int, Fraction or string
        * @post      ExpressionAtom is always valid, containing the 
        *            supplied value. No argument yields UNDEFINED.
        **/ 
        ExpressionAtom( AtomType t =UNDEFINED, long int atom =0l );
        ExpressionAtom( float atom );
        ExpressionAtom( long int atom );
        ExpressionAtom( string var );
        ExpressionAtom( OperatorType op );
        ExpressionAtom( Function func );
        ExpressionAtom( Fraction frac );
        
       /**
        * @function  operator==( )
        * @abstract  Test equality for two ExpressionAtom
        * @param     ExpressionAtom or either one of AtomType, OperatorType,
        *            Function, float, long int, Fraction  or string
        * @return    true upon equality
        * @post      Two ExpressionAtoms are equal if
        *            - their types are equal
        *            - their value is equal
        *            - they are not UNDEFINED
        **/
        bool operator ==( const ExpressionAtom& rhs ) const;
        
       /**
        * @function  Inquality operators <, >, <= and >=
        * @abstract  Test equality for two ExpressionAtoms
        * @param     ExpressionAtom or either one of AtomType, OperatorType,
        *            Function, float, long int, Fraction  or string
        * @return    true upon resp. lt, gt, lte or gte
        * @pre       Both operands should be of the numeric operand type
        *            Types do not have to be equal
        * @post      always false if !isNumericOperand( ) or UNDEFINED
        **/
        bool operator <( const ExpressionAtom& rhs ) const;
        bool operator >( const ExpressionAtom& rhs ) const;
        bool operator <=( const ExpressionAtom& rhs ) const;
        bool operator >=( const ExpressionAtom& rhs ) const;
        
       /**
        * @function  Arithmetic operators +, -, *, /
        * @abstract  Arithmetic result of two ExpressionAtoms
        * @param     ExpressionAtom or either one of AtomType, OperatorType,
        *            Function, float, long int, Fraction  or string
        * @return    ExpressionAtom (xvalue) containing the result
        *            The type of this ExpressionAtom doesn't need to be
        *            equal to one of the operand's types
        * @pre       Both operands should be of the numeric operand type
        *            Types do not have to be equal
        * @post      undefined if !isNumericOperand( ) or UNDEFINED
        **/
        ExpressionAtom operator+( const ExpressionAtom& rhs ) const;
        ExpressionAtom operator-( const ExpressionAtom& rhs ) const;
        ExpressionAtom operator*( const ExpressionAtom& rhs ) const;
        ExpressionAtom operator/( const ExpressionAtom& rhs ) const;
        
       /**
        * @function  pow( )
        * @abstract  Raise to power
        * @param     ExpressionAtom or Either one of AtomType, OperatorType,
        *            Function, float, long int, Fraction  or string
        * @return    ExpressionAtom (xvalue) containing the result
        *            The type of this ExpressionAtom doesn't need to be
        *            equal to one of the operand's types
        * @pre       Both operands should be of the numeric operand type
        *            Types do not have to be equal
        * @post      undefined if !isNumericOperand( ) or UNDEFINED
        **/
        ExpressionAtom pow( const ExpressionAtom& power ) const;
       /**
        * @function  sqrt( )
        * @abstract  Square root
        * @pre       Instance should be of the numeric operand type
        *            Types do not have to be equal
        * @return    ExpressionAtom (xvalue) containing the result
        *            The type of this ExpressionAtom doesn't need to be
        *            equal to the operand's types
        * @post      undefined if !isNumericOperand( ) or UNDEFINED
        **/
        ExpressionAtom sqrt( ) const;
        
       /**
        * @function  setters
        * @abstract  sets ExpressionAtom to a given value
        * @param     Either one of AtomType, OperatorType,
        *            Function, float, long int, Fraction  or string
        * @post      The type is changed to match the new value
        **/
        void setFloat( float d ) 
            { m_type =FLOAT_OPERAND; m_atom.float_atom =std::move( d ); }
        void setInteger( long int i ) 
            { m_type =INTEGER_OPERAND; m_atom.integer_atom =std::move( i ); }
        void setFraction( const Fraction& frac ) 
            { m_type =FRACTION_OPERAND; m_atom.fraction_atom =std::move( frac ); }
        void setFunction( Function f ) 
            { m_type =FUNCTION; m_atom.integer_atom =std::move( f ); }
        void setOperator( OperatorType op ) 
            { m_type =OPERATOR; m_atom.integer_atom =std::move( op ); }
        void setNamed( string str ) 
            { m_type =NAMED_OPERAND; m_named_atom =std::move( str ); }
        
       /**
        * @function  getters
        * @abstract  Return the value as a certain type
        * @return    Returns the value as the requested type
        * @pre       Type should match the requested datatype
        * @post      undefined if type doesn't match or UNDEFINED
        **/
        float getFloat( ) const { return m_atom.float_atom; }
        long int getInteger( ) const { return m_atom.integer_atom; }
        Fraction getFraction( ) const { return m_atom.fraction_atom; }
        int getFunction( ) const { return (int)m_atom.integer_atom; }
        int getOperator( ) const { return (int)m_atom.integer_atom; }
        string getNamed( ) const { return m_named_atom; }
        
       /**
        * @function  isNumericOperand( )
        * @abstract  Returns whether this instance holds a numeric type
        * @return    bool with the result
        **/
        bool isNumericOperand( ) const { 
            return m_type == FLOAT_OPERAND 
                || m_type == INTEGER_OPERAND 
                || m_type == FRACTION_OPERAND; }
        
       /**
        * @function  numeric casting functions
        * @abstract  Casts the value to a certain type
        * @return    Returns the value as the requested type
        * @pre       Type should be a numeric operand
        *            toFloat( ) and toInteger( ) are defined for
        *            FLOAT_OPERAND, INTEGER_OPERAND and FRACTION_OPERAND
        *            toFraction( ) is defined for INTEGER_OPERAND and FRACTION
        * @post      undefined if !isNumericOperand( )
        **/
        float toFloat( ) const;
        long int toInteger( ) const;
        Fraction toFraction( ) const;
        
       /**
        * @function  type( )
        * @abstract  Gives the specified type
        * @return    One of AtomType
        **/
        AtomType type( ) const { return m_type; }
        
       /**
        * @function  arity( )
        * @abstract  Returns the arity of the specified type
        * @return    Arity ranging from 0 to 2
        **/
        short arity( ) const;
        
    private:
        union {
            long int integer_atom;
            float float_atom;
            Fraction fraction_atom;
        } m_atom;
        string m_named_atom;
        AtomType m_type;
};

/**
* @function  operator <<( ostream& out, const ExpressionAtom& atom )
* @abstract  Overloads operator<< to support ExpressionAtom
* @return    an ostream with the contents of atom inserted
**/
ostream& operator <<( ostream& out, const ExpressionAtom& atom );

#endif

