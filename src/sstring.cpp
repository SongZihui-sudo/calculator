#include "./sstring.h"
#include <cstddef>
#include <string>
#include <functional>

size_t sstring_table::hash( sstring str )
{
    size_t index;
    std::hash< std::string > hash;
    index = hash( to_stdstring( str ) );
    return index;
}

void sstring_table::join( sstring str )
{
    size_t index = hash( str );
    if ( mTab[index]->flag )
    {
        sstring_node* tmp = mTab[index];
        while ( tmp->next )
        {
            tmp = tmp->next;
        }
        sstring_node* cur = new sstring_node( str );
    }
    else
    {
        mTab[index]->value = str;
    }
}

int sstring_table::del( sstring str )
{
    size_t index = hash( str );
    if ( mTab[index]->flag )
    {
        sstring_node* tmp = mTab[index];
        while ( tmp->next && tmp->next->value == str )
        {
            tmp = tmp->next;
        }
        if ( tmp->next->next )
        {
            tmp->next = tmp->next->next;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
    return 1;
}

bool sstring_table::isin( sstring str )
{
    size_t index = hash( str );
    if ( mTab[index]->flag )
    {
        sstring_node* tmp = mTab[index];
        while ( tmp->next && tmp->next->value == str )
        {
            tmp = tmp->next;
        }
        if ( tmp )
        {
            return true;
        }
    }
    return false;
}
