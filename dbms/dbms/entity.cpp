#include "entity.h"
#include <algorithm>

//add entry in x direction to tuple
void entity::add_column(string _field_name, string _field_value) {
	attributes[_field_name] = _field_value;
}

//sets attribute at a specified column title
void entity::set_attribute(string _field_name, string _field_value) {
	attributes[_field_name] = _field_value;
}

//print function for displaying entries in tuples
void entity::show_attributes(vector<string> _ordering, int max_length) {
	for(int i = 0; i < _ordering.size(); i++){
		cout << left << setw(max_length+2) << setfill(' ') << attributes[_ordering[i]];
	}	
}

vector<string> entity::get_attr_values() {
	vector<string> vals;

	for (map<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++) {
		vals.push_back(it->second);
	}
	return vals;
}

int entity::max_attr_length() {
	int max_length = 0;
	for (map<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++) {
		max_length = std::max((int)it->second.size(), max_length);
	}
	return max_length;


}

//returns the value stored at a column title
string entity::get_attribute(string _attribute_name) {
	for (map<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++){ 
		if (it->first == _attribute_name){
			return it->second;
		}
	}	
}