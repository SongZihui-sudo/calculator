#ifndef calculator_h
#define calculator_h

#include <iostream>
#include <ostream>
#include <string>
#include <stack>
#include <loguru.hpp>

// operator
class _operator_
{
public:
    _operator_( int level, int flag )
    {
        mName  = '?';
        mFlag  = flag;
        mLevel = level;
    }

    _operator_( char cc )
    {
        mName = cc;
        switch ( cc )
        {
            case '+':
                mLevel = 1;
                mFlag  = 0;
                break;
            case '-':
                mLevel = 1;
                mFlag  = 1;
                break;
            case '*':
                mLevel = 2;
                mFlag  = 2;
                break;
            case '/':
                mLevel = 2;
                mFlag  = 3;
                break;
            case '(':
                mLevel = 0;
                mFlag  = 4;
                break;
            case ')':
                mLevel = 0;
                mFlag  = 5;
                break;
            default:
                mLevel = -1;
                mFlag  = -1;
                LOG_F( ERROR, "Not supported!" );
                break;
        }
    }

    ~_operator_() = default;

public:
    // func: get_value()
    // desc: get the level of the operator
    //
    int get_level() { return mLevel; }

    // func: get_flag()
    // desc: get the flag of the flag
    //
    int get_flag() { return mFlag; }

    char get_name() { return mName; }

    bool operator<( _operator_ oper )
    {
        if ( mLevel < oper.mLevel )
        {
            return true;
        }
        return false;
    }

    bool operator>( _operator_ oper )
    {
        if ( mLevel > oper.mLevel )
        {
            return true;
        }
        return false;
    }

    bool operator==( _operator_ oper )
    {
        if ( mLevel == oper.mLevel )
        {
            return true;
        }
        return false;
    }

    virtual double _do_( double num1, double num2 )
    {
        return func_tab[mFlag]( num1, num2 );
    }

    static bool isoperator( char cc );

private:
    static double _do_add( double num1, double num2 ) { return num2 + num1; }
    static double _do_sub( double num1, double num2 ) { return num2 - num1; }
    static double _do_mul( double num1, double num2 ) { return num2 * num1; }
    static double _do_div( double num1, double num2 ) { return num2 / num1; }

    double ( *func_tab[4] )( double, double ) = { _do_add, _do_sub, _do_mul, _do_div };

private:
    char mName;
    int mLevel;
    int mFlag;
};

//
// calculator class
//
class calculator
{
public:
    calculator()  = default;
    ~calculator() = default;

public:
    // func: repl
    // desc: do the main repl
    //
    void repl();

    //  func: run
    //  desc: calculate explession
    //
    double run( std::string line );

    //  func: to_suffix
    //  desc: to the suffix expression
    //
    static std::string to_suffix( std::string line );

    //  func: preprocessor
    //  desc: preprocess line (delete space or check is dight or operator)
    //
    static std::string preprocessor( std::string line );
};

#endif