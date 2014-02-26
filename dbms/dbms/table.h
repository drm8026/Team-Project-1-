#ifndef TABLE_H
#define TABLE_H

#include "entity.h"
#include "condition_obj.h"
#include <vector>

class table {
private:

	//stores name of table
	string name;	
	bool is_cross_product_flag; //flag set to true if table is a cross product view
public:

	//storage variables
	vector<entity> entity_table;				//stores tuples
	vector<string> attribute_names;				//stores column titles
	vector<string> primary_key;					//stores significant columns, blocks redundant entries
	
	table() {};
	table(string _name, vector<string> _attribute_names, vector<string> _primary_key){
		name = _name;
		attribute_names = _attribute_names;
		primary_key = _primary_key;
	};
	void set_cp_flag(bool b) { is_cross_product_flag = b; }

	//mutator function
	void set_name(string _name) {
		name = _name;
	}
	void set_attr_names(vector<string> _attribute_names);
	void set_pri_key(vector<string> _primary_key);

	//accessor function
	string get_name() {
		return name;
	}
	
	//Helper functions
	void insert(vector<string> _field_values);
	
	//inserts an entity into the entity table
	void insert(entity _e) {
		entity_table.push_back(_e);
	}
	
	//updates all values that meet a specific condition
	void update(vector<pair<string, string>> _set_argument, condition_obj condit);
	
	//parses an input into table to return a vector with inputs at each index
	vector<string> split_on_spaces(string _str);
	
	//print function
	void display_table();
	
	//removes an entity from table
	void delete_from(condition_obj condit);

	vector<int> eval_condition(condition_obj condit);

	//overwritten boolean operator to compare two tables equality
	bool operator == (const table &t2);
};

inline bool table::operator == (const table& t2) {
	
	//table name check
	if (name != t2.name) 
	{
		return false;
	}

	//table equality check
	if (entity_table != t2.entity_table) 
	{
		return false;
	}

	//table's primary key check
	if (primary_key != t2.primary_key) 
	{
		return false;
	}

	//table's attribute name check
	if (attribute_names != t2.attribute_names) 
	{
		return false;
	}

	//tables are the same
	return true;

}
#endif