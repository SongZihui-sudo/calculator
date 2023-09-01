#ifndef sstring_h
#define sstring_h

#include <cstddef>
#include <string.h>
#include <assert.h>

#define sstring_default_len 64
#define sstring_tab_default_len 128

#define std_tosstring(str)  \
    sstring(str.c_str())

class sstring
{
public:
    sstring()
    {
        mLen = sstring_default_len;
        mbuf = new char[mLen];
    }

    sstring( const char* str )
    {
        mLen = strlen( str );
        mbuf = new char[mLen];
    }

    ~sstring()
    {
        mLen = 0;
        delete mbuf;
        mbuf = nullptr;
    }

public:
    int get_buffer( char* buf )
    {
        assert( buf );
        buf = mbuf;
        return 1;
    }

    int get_len() { return mLen; }

    bool operator==( sstring other )
    {
        if ( mLen != other.mLen )
        {
            return false;
        }
        if ( !strcmp( mbuf, other.mbuf ) )
        {
            return true;
        }
        return false;
    }

    bool operator+( sstring other ) { return strcat( mbuf, other.mbuf ); }

private:
    size_t mLen;
    char* mbuf;
};

class sstring_table
{
public:
    sstring_table() { mTab = new sstring[mLen]; }

    ~sstring_table()
    {
        mLen = 0;
        delete[] mTab;
        mTab = nullptr;
    }

public:
    size_t hash( sstring str );

    int join( sstring str );

    int del( sstring str );

    int del( size_t index );

    int replace( sstring old_str, sstring new_str );

    int replace( size_t index, sstring new_str );

    int get( size_t index );

private:
    size_t mLen = sstring_tab_default_len;
    sstring* mTab;
};

#endif