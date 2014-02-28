#include "entity.h"

//add entry in x direction to tuple
void entity::add_column(string _field_name, string _field_value) {
	attributes[_field_name] = _field_value;
}

//sets attribute at a specified column title
void entity::set_attribute(string _field_name, string _field_value) {
	attributes[_field_name] = _field_value;
}

//print function for displaying entries in tuples
void entity::show_attributes(vector<string> _ordering) {
	for(int i = 0; i < _ordering.size(); i++){
		cout << attributes[_ordering[i]] << '\t';
	}	
}

vector<string> entity::get_attr_values() {
	vector<string> vals;

	for (map<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++) {
		vals.push_back(it->second);
	}
	return vals;
}


//returns the value stored at a column title
string entity::get_attribute(string _attribute_name) {
	for (map<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++){ 
		if (it->first == _attribute_name){
			return it->second;
		}
	}	
}