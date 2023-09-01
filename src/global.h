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
	global_table() {};
	~global_table() = default;

public:
	int join_var(sstring _name, type _type);

	int join_string(const char* str);

	type get_var_value(sstring name);

	int str(char* buf);

	int replace_var_value(sstring _name, type _type);

	int replace_str(sstring old_str, sstring new_str);

	int del_str(sstring str);

	int del_var(sstring name);

	bool isvar(sstring name);

private:
	global_var mVars;
	global_string mStrings;
};

#endif