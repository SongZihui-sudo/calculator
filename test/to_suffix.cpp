#include "../src/calculator.h"
#include <loguru.hpp>

int main( int argc, char* argv[] )
{
    loguru::init( argc, argv );
    calculator obj;
    /* test case 1 : to_suffix */
    obj.to_suffix( "111+120+230*20" );
    /* test case 2 : to_suffix */
    obj.to_suffix( "1+1" );
    /* test case 3 : to_suffix */
    obj.to_suffix( "(120 - 130) * 50" );
    /* test case 4 : to_suffix */
    obj.to_suffix( "{[(170 - 180) + 99 ] - 1} / [(120 + 20) + 3]" );
    /* test case 5 : to_suffix */
    obj.to_suffix( "1 + 1 + 2" );
    /* test case 6 : to_suffix */
    obj.to_suffix( "1000" );
    return 0;
}