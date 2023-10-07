#ifndef type_h
#define type_h

#include <cmath>
#include <sys/types.h>
#include <string>
#include <map>
#include <type_traits>
#include <loguru.hpp>
#include "./sstring.h"

enum type_name
{
    _int_ = 0,
    _float_,
    _uint_,
    _string_,
    _none_
};

struct type
{
    template< class T >
    type( T val )
    {
        if constexpr ( std::is_same< T, int >::value )
        {
            mType         = _int_;
            value.val_int = val;
        }
#define xx( t1, t2 )                                                                       \
    else if constexpr ( std::is_same< T, t1 >::value )                                     \
    {                                                                                      \
        mType          = t2;                                                               \
        value.val_##t1 = val;                                                              \
    }
        xx( double, _float_ ) xx( uint, _uint_ ) xx( sstring, _string_ )
#undef xx
        else
        {
            LOG_F( ERROR, "Unsupported type!" );
        }
    }

    template< class T >
    T get_value()
    {
        T result;
        if constexpr ( std::is_same< T, int >::value )
        {
            result = value.val_int;
        }
#define xx( t1 )                                                                           \
    else if constexpr ( std::is_same< T, t1 >::value )                                     \
    {                                                                                      \
        result = value.val_##t1;                                                           \
    }
        xx( double ) xx( uint ) xx( sstring )
#undef xx
        else
        {
            LOG_F( ERROR, "Unsupported type!" );
        }
        return result;
    }

    template< class T >
    void set_value( T val )
    {
        if constexpr ( std::is_same< T, int >::value )
        {
            value.val_int = val;
        }
#define xx( t1 )                                                                           \
    else if constexpr ( std::is_same< T, t1 >::value )                                     \
    {                                                                                      \
        value.val_##t1 = val;                                                              \
    }
        xx( double ) xx( unsigned int ) xx( sstring )
#undef xx
        else
        {
            LOG_F( ERROR, "Unsupported type!" );
        }
    }

    type_name mType;
    union
    {
        int val_int;
        double val_double;
        unsigned int val_uint;
        sstring val_sstring;
    } value;
};

class var
{
public:
    var()
    {
        mName = "None";
        mType = nullptr;
    }
    template< class T >
    var( sstring _name, T _val )
    {
        mName = _name;
        mType = new type( _val );
    }

    ~var() = default;

public:
    sstring get_name() { return mName; }

    type* get_type() { return mType; }

    static bool isnumber( std::string str )
    {
        for ( char const& c : str )
        {
            if ( std::isdigit( c ) == 0 )
                return false;
        }
        return true;
    }

    template< class T >
    void set_value( T val )
    {
        mType->set_value( val );
    }

    template< class T >
    T get_value()
    {
        return mType->get_value< T >();
    }

private:
    sstring mName;
    type* mType;
};

class var_table
{
public:
    var_table(){};
    ~var_table() = default;

public:
    template< class T >
    void join( sstring name, T val );

    void join( var in );

    var get( sstring name );

    template< class T >
    int replace_value( sstring name, T new_value );

    int replace_name( sstring name, sstring new_name );

    int del( sstring name );

    bool isin( sstring name );

private:
    std::map< sstring, var > mTab;
};

#endif
