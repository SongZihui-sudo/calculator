#ifndef global_h
#define global_h

#include "./sstring.h"
#include "./type.h"

#define global_var var_table
#define global_string sstring_table
#define global_state global_table

class global_table
{
public:
    global_table(){};
    ~global_table() = default;

public:
    template< class T >
    void join_var( sstring _name, T _val )
    {
        mVars.join( _name, _val );
    }

    void join_string( const char* str );

    template< class T >
    T get_var_value( sstring name )
    {
        return mVars.get( name ).get_value< T >();
    }

    template< class T >
    int replace_var_value( sstring _name, T _val )
    {
        return mVars.replace_value( _name, _val );
    }
    
    int del_str( sstring str );

    int del_var( sstring name );

    bool isstring( sstring str );

    bool isvar( sstring name );

private:
    global_var mVars;
    global_string mStrings;
};

#endif