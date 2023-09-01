#include "./type.h"

template<class T>
void var_table::join( sstring name, T val )
{
	mTab[name] = var(name, val);
}

void var_table::join( var in ) { mTab[in.get_name()] = in; }

var var_table::get( sstring name )
{
    if ( mTab.find( name ) == mTab.end() )
    {
        LOG_F( ERROR, "Variable undefined! %s", name.str() );
        return var();
    }
    return mTab[name];
}

template< class T >
int var_table::replace_value( sstring name, T new_value )
{
    if ( mTab.find( name ) == mTab.end() )
    {
        LOG_F( ERROR, "Variable undefined! %s", name.str() );
        return -1;
    }
    mTab[name].set_value( new_value );
    return 1;
}

int var_table::replace_name( sstring name, sstring new_name )
{
    if ( mTab.find( name ) == mTab.end() )
    {
        LOG_F( ERROR, "Variable undefined! %s", name.str() );
        return -1;
    }
    var tmp        = mTab[name];
    mTab[new_name] = tmp;
    mTab.erase( name );
    return 1;
}

int var_table::del( sstring name )
{
    if ( mTab.find( name ) == mTab.end() )
    {
        LOG_F( ERROR, "Variable undefined! %s", name.str() );
        return -1;
    }
    mTab.erase( name );
    return 1;
}

bool var_table::isin(sstring name)
{
    if ( mTab.find( name ) == mTab.end() )
    {
        LOG_F( ERROR, "Variable undefined! %s", name.str() );
        return false;
    }
    return true;
}
