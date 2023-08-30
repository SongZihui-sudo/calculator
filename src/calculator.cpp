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
        case '+':
            flag = true;
            break;
        case '-':
            flag = true;

            break;
        case '*':
            flag = true;

            break;
        case '/':
            flag = true;

            break;
        case '(':
            flag = true;

            break;
        case ')':
            flag = true;

            break;
        default:
            flag = false;
            LOG_F( ERROR, "Not supported!" );
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
        if ( str == "quit" )
        {
            LOG_F(INFO, "quiting!");
            break;
        }
        str = preprocessor( str );
        str = to_suffix( str );
        LOG_F( WARNING, "suffix: %s", str.c_str() );
        LOG_F( INFO, "%f", run( str ) );
        std::cout << "$: ";
    }
}

std::string calculator::to_suffix( std::string line )
{
    std::string result;
    std::stack< _operator_ > ss;
    for ( size_t i = 0; i < line.size(); i++ )
    {
        char cc = line[i];
        if ( !std::isdigit( line[i] ) )
        {
            _operator_ cur( line[i] );
            if ( cur.get_name() == ')' )
            {
                while ( ss.top().get_name() == '(' && !ss.empty() )
                {
                    cc = ss.top().get_name();
                    ss.pop();
                }
                if ( ss.empty() )
                {
                    LOG_F( ERROR, "The brackets do not match!" );
                    result = "";
                    return result;
                }
            }
            else if ( !ss.empty() && cur > ss.top() )
            {
                cc = ss.top().get_name();
                ss.pop();
            }
            else
            {
                ss.push( cur );
                continue;
            }
        }
        result += cc;
    }
    while ( !ss.empty() )
    {
        result += ss.top().get_name();
        ss.pop();
    }
    return result;
}

std::string calculator::preprocessor( std::string line )
{
    std::string result;
    for ( int i = 0; i < line.size(); i++ )
    {
        if ( line[i] != ' ' && ( std::isdigit( line[i]) || _operator_::isoperator( line[i] ) ) )
        {
            result += line[i];
        }
        else
        {
            LOG_F( ERROR, "Unknown character: %c", line[i] );
            result = "";
            return result;
        }
    }
    return result;
}

double calculator::run( std::string line )
{
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
        else
        {
            int cur = std::stoi( tmp );
            nums.push( cur );
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