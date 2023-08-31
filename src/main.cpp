#include "./calculator.h"
#include <loguru.hpp>

int main( int argc, char* argv[] )
{
    loguru::init( argc, argv );
    calculator obj;
    obj.repl();
    return 0;
}