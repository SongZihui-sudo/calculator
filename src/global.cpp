#include "./global.h"

int global_table::join_var( sstring _name, type _type ) {}

int global_table::join_string( const char* str ) {}

type global_table::get_var_value( sstring name ) {}

int global_table::str( char* buf ) {}

int global_table::replace_var_value( sstring _name, type _type ) {}

int global_table::replace_str( sstring old_str, sstring new_str ) {}

int global_table::del_str( sstring str ) {}

int global_table::del_var( sstring name ) {}

bool global_table::isvar( sstring name ) {}