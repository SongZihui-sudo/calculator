#include "./sstring.h"

size_t sstring_table::hash( sstring str ) {}

int sstring_table::join( sstring str ) {}

int sstring_table::del( sstring str ) {}
int sstring_table::del( size_t index ) {}

int sstring_table::replace( sstring old_str, sstring new_str ) {}

int sstring_table::replace( size_t index, sstring new_str ) {}

int sstring_table::get( size_t index ) {}