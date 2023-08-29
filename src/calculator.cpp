#include "./calculator.h"
#include <cctype>
#include <clocale>
#include <cstddef>
#include <cstdio>
#include <string>
#include <stack>
#include <type_traits>
#include <iostream>

void calculator::repl()
{
    std::string str;
    std::cout << "$: ";
    while ( std::getline( std::cin, str ) )
    {
        if ( str == "quit" )
        {
            break;
        }
        str = to_suffix( str );
        run( str );
        std::cout << "$: ";
    }
}

std::string calculator::to_suffix( std::string line )
{
    std::string result;
    std::stack< _operator_ > ss;
    for ( size_t i = 0; i < line.size(); i++ )
    {
        if ( std::isalpha( line[i] ) )
        {
            result += line[i];
        }
        else
        {
            _operator_ cur( line[i] );
            if ( ss.empty() )
            {
                ss.push( cur );
            }
            else if ( cur.get_name() == ')' )
            {
                while ( ss.top().get_name() == '(' )
                {
                    result += ss.top().get_name();
                    ss.pop();
                }
            }
            else if ( cur > ss.top() )
            {
                result += ss.top().get_name();
                ss.pop();
            }
            else
            {
                ss.push( cur );
            }
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