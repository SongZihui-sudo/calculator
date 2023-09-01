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
    _uint_
};

struct type
{
    template<class T>
    type(T val)
    {
        if constexpr (std::is_same<T, int>::value)
        {
            mType = _int_;
            value.val_int = val;
        }
        else if constexpr (std::is_same<T, double>::value)
        {
            mType = _float_;
            value.val_float = val;
        }
        else if constexpr (std::is_same<T, uint>::value)
        {
            mType = _uint_;
            value.val_uint = val;
        }
        else
        {
            LOG_F(ERROR, "Unsupported type!");
        }
    }

    template<class T>
    T get_value()
    {
        T result;
        if constexpr (std::is_same<T, int>::value)
        {
            result = value.val_int;
        }
        else if constexpr (std::is_same<T, double>::value)
        {
            result = value.val_float;
        }
        else if constexpr (std::is_same<T, uint>::value)
        {
            result = value.val_uint;
        }
        else
        {
            LOG_F(ERROR, "Unsupported type!");
        }
        return result;
    }
    type_name mType;
    union
    {
        int val_int;
        double val_float;
        uint val_uint;
    } value;
};

class var
{
public:
    template<class T>
    var( sstring _name, T _val )
    {
        mName = _name;
        mType = new type(_val);
    }

    ~var()
    {
        delete mType;
        mType = nullptr;
    }

public:
    sstring get_name() { return mName; }

    type get_type() { return mType; }

    static bool isnumber( std::string str )
    {
        for ( char const& c : str )
        {
            if ( std::isdigit( c ) == 0 )
                return false;
        }
        return true;
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
    int join( var in );

    var get( sstring name );

    int replace_value( sstring name, type new_value );

    int replace_name( sstring name, sstring new_name );

    int del( sstring name );

private:
    std::map< sstring, var > mbuffer;
};

#endif