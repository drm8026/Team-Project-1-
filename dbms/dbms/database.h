#ifndef DATABASE_H
#define DATABASE_H
#include "table.h"

class database{
private:
	vector<table> tables;

public:
	database() {};
	//create table using name, attributes, and primary key
	void create_table(string _name, vector<string> _attribute_names, vector<string> _primary_key)
	{
		table t (_name, _attribute_names, _primary_key);
		add_table(t);
	}
	//insert table into database
	void add_table(table t)
	{
		tables.push_back(t);
	}
	//remove table from database
	void delete_table(table t)
	{
		int index = find_table(t.get_name());
		tables.erase(tables.begin() + index);
	}
	//return index of table
	int find_table(string table_name)
	{
		for(int i = 0; i <tables.size(); i++)
		{
			if(tables[i].get_name()==table_name)
				return i;
		}
		return -1;
	}
	table& get_table(string table_name)
	{
		return tables[find_table(table_name)];
	}
	table set_union(string view_name, table tble1, table tble2);							//: compute the union of two relations; the relations must be union-compatible.
	table set_difference(string view_name, table tble1, table tble2);						//: compute the set difference of two relations; the relations must be union-compatible.
	vector<entity> set_selection(table table, int op, int);								//: select the tuples in a relation that satisfy a particular condition.
	table set_projection(string view_name, table tble, vector<string> attributes);						//: select a subset of the attributes in a relation.
	table set_selection(string view_name, table tble, condition_obj condit);
	table set_renaming(string view_name, table tble, vector<string> attributes);							//: rename the attributes in a relation.
	table set_cross_product(string view_name, table tble1, table tble2);					//: compute the Cartesian product of two relations.
	table set_natural_join(string view_name, table tble1, table tble2);
	int table_num(){ return tables.size(); }
};

#endif