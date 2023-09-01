#ifndef sstring_h
#define sstring_h

#include <cstddef>
#include <string.h>
#include <assert.h>

#define sstring_default_len 64
#define sstring_tab_default_len 128

#define std_tosstring( str ) sstring( str.c_str() )
#define to_stdstring(str) std::string(str.str())

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
    char* str() { return mbuf; }

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

    bool operator<( const sstring& other ) const
    {
        if ( mLen > other.mLen )
        {
            return true;
        }
        return false;
    }

    bool operator>( const sstring& other ) const
    {
        if ( mLen < other.mLen )
        {
            return true;
        }
        return false;
    }

    bool operator+( sstring other ) { return strcat( mbuf, other.mbuf ); }

    size_t len() { return mLen; }

private:
    size_t mLen;
    char* mbuf;
};

struct sstring_node
{
    sstring_node() {};
    sstring_node(sstring str)
    {
        value = str;
    }
    bool flag = false;
    sstring_node* next;
    sstring value;
};

class sstring_table
{
public:
    sstring_table() { mTab = new sstring_node*[mLen]; }

    ~sstring_table()
    {
        mLen = 0;
        delete[] mTab;
        mTab = nullptr;
    }

public:
    size_t hash( sstring str );

    void join( sstring str );

    int del( sstring str );

    bool isin( sstring str );

private:
    size_t mLen = sstring_tab_default_len;
    sstring_node** mTab;
};

#endif