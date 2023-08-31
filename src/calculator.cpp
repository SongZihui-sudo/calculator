#include "./calculator.h"
#include <cctype>
#include <clocale>
#include <cstddef>
#include <cstdio>
#include <string>
#include <stack>
#include <type_traits>
#include <iostream>

bool _operator_::isoperator( char cc )
{
    bool flag;
    switch ( cc )
    {
#define xx( cc, val )                                                                      \
    case cc:                                                                               \
        flag = val;                                                                        \
        break;
        xx( '+', true );
        xx( '-', true );
        xx( '*', true );
        xx( '/', true );
        xx( ')', true );
        xx( '(', true );
        xx( ']', true );
        xx( '[', true );
        xx( '}', true );
        xx( '{', true );
#undef xx
        default:
            flag = false;
            LOG_F( ERROR, "Unknown character: %c", cc );
            break;
    }
    return flag;
}

void calculator::repl()
{
    std::string str;
    std::cout << "$: ";
    while ( std::getline( std::cin, str ) )
    {
        if ( str == "quit" || str == "exit" )
        {
            LOG_F( INFO, "quiting!" );
            break;
        }
        LOG_F( WARNING, "suffix: %s", str.c_str() );
        LOG_F( INFO, "%f", run( str ) );
        std::cout << "$: ";
    }
}

std::string calculator::to_suffix( std::string line )
{
    line = preprocessor( line );
    std::string result;
    std::string buffer;
    std::stack< _operator_ > ss;
    for ( size_t i = 0; i < line.size(); i++ )
    {
        char cc = line[i];
        if ( line[i] == '\\' )
        {
            result += buffer;
            buffer.clear();
        }
        else if ( !std::isdigit( line[i] ) )
        {
            _operator_ cur( line[i] );
            if ( !ss.empty() && ss.top() < cur )
            {
                while ( !ss.empty() && ss.top() < cur )
                {
                    result += ss.top().get_name();
                    ss.pop();
                }
                ss.push( cur );
            }
#define xx( right, left )                                                                  \
    else if ( line[i] == right )                                                           \
    {                                                                                      \
        while ( !ss.empty() && ss.top() == left )                                          \
        {                                                                                  \
            result += ss.top().get_name();                                                 \
            ss.pop();                                                                      \
        }                                                                                  \
    }
            xx( ')', '(' ) xx( ']', '[' ) xx( '}', '{' )
#undef xx
            else
            {
                ss.push( cur );
            }
        }
        else
        {
            buffer += cc;
        }
    }
    LOG_F( WARNING, "str: %s", result.c_str() );
    return result;
}

std::string calculator::preprocessor( std::string line )
{
    bool operator_flag  = false;
    size_t num_dight    = 0;
    size_t num_operator = 0;
    std::string buffer;
    std::string result;
    for ( int i = 0; i < line.size(); i++ )
    {
        if ( std::isdigit( line[i] ) )
        {
            operator_flag = false;
            buffer += line[i];
        }
        else if ( _operator_::isoperator( line[i] ) )
        {
            if ( !buffer.empty() )
            {
                operator_flag = false;
                buffer += '\\';
                result += buffer;
                buffer.clear();
                num_dight++;
            }
            if ( line[i] == '-' || line[i] == '+' || line[i] == '*' || line[i] == '/' )
            {
                if ( operator_flag )
                {
                    LOG_F( ERROR,
                           "A continuous add or subtract, multiply, divide operator! %s",
                           line.c_str() );
                    return std::string( "" );
                }
                else
                {
                    operator_flag = true;
                    num_operator++;
                }
            }
            result += line[i];
        }
        else if ( line[i] == ' ' )
        {
            continue;
        }
        else
        {
            LOG_F( ERROR, "Unknown character : %c", line[i] );
            return std::string( "" );
        }
    }
    if ( !buffer.empty() )
    {
        buffer += '\\';
        result += buffer;
        num_dight++;
    }
    return result;
}

double calculator::run( std::string line )
{
    line          = to_suffix( line );
    double result = 0;
    std::string tmp;
    std::stack< int > nums;
    std::stack< _operator_ > operators;
    for ( int i = 0; i < line.size(); i++ )
    {
        if ( std::isdigit( line[i] ) )
        {
            tmp += std::to_string( line[i] );
        }
        else if ( line[i] == '\\' )
        {
            int cur = std::stoi( tmp );
            nums.push( cur );
            tmp.clear();
        }
        else
        {
            int num_right = nums.top();
            nums.pop();
            int num_left = nums.top();
            nums.pop();
            double result_tmp;
            if ( !operators.empty() )
            {
                result_tmp = _operator_( operators.top() )._do_( num_right, num_left );
                operators.pop();
            }
            operators.push( _operator_( line[i] ) );
        }
    }
    return result;
}