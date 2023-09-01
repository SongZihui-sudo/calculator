#include "../src/calculator.h"
#include <loguru.hpp>
#include <assert.h>

int main( int argc, char* argv[] )
{
    loguru::init( argc, argv );
    calculator obj;
    double res;
    /* test case 1 : to_suffix */
    res = obj.run<double>( "100+120+230*2" );
    assert( res == 680 );
    /* test case 2 : to_suffix */
    res = obj.run<double>( "1+1" );
    assert( res == 2 );
    /* test case 3 : to_suffix */
    res = obj.run<double>( "(120 - 130) * 50" );
    assert( res == -500 );
    /* test case 4 : to_suffix */
    res = obj.run<double>( "(((170 - 180) + 99 ) - 1) + ((120 / 20) + 3)" );
    assert( res == 97 );
    /* test case 5 : to_suffix */
    res = obj.run<double>( "1 + 1 + 2" );
    assert( res == 4 );
    /* test case 6 : to_suffix */
    res = obj.run<double>( "1000" );
    assert( res == 1000 );
    return 0;
}