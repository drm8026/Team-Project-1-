#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct entity {

	map<string, string> attributes;	// map of column to value stored in column
	
	entity() {}
	
	//add an additional entry x directionally
	void add_column(string _field_name, string _field_value);
	
	//print function
	void show_attributes(vector<string> _ordering);
	
	//accessor function
	string get_attribute(string _attribute_name);

	vector<string> get_attr_values();
	
	//mutation function
	void set_attribute(string _field_name, string _field_value);
	
	bool operator == (const entity &Ref) const {		//checks if two tuples have same values
        return attributes==Ref.attributes;
    }	
};

#endif