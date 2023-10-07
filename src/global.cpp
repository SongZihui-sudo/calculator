#include "./global.h"
#include "sstring.h"

void global_table::join_string( const char* str ) { mStrings.join( sstring( str ) ); }

int global_table::del_str( sstring str ) { return mStrings.del( str ); }

int global_table::del_var( sstring name )
{
    mVars.del( name );
    return 0;
}

bool global_table::isstring( sstring str ) { return mStrings.isin( str ); }

bool global_table::isvar( sstring name ) { return mVars.isin( name ); }
