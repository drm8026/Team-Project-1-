#include "table.h"
#include <stdlib.h> 
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

//mutator function
void table::set_attr_names(vector<string> _attribute_names) {
	attribute_names = _attribute_names;
}

//Helper functions
//inserts an entity into table
void table::insert(vector<string> _field_values) {
	entity e;
	vector<bool> found;
	bool present = true;

	for (int i = 0; i < _field_values.size(); i++){
		e.set_attribute(attribute_names[i], _field_values[i]);
	}

	for (int i = 0; i < primary_key.size(); i++){
		found.push_back(false);
		for (int j = 0; j < entity_table.size(); j++){
			if (e.attributes[primary_key[i]] == entity_table[j].attributes[primary_key[i]]){
				found[i] = true;
			}
		}
	}

	for (int k = 0; k < found.size(); k++){
		if (found[k] == false){
			present = false;
		}
	}

	if (present == false){
		entity_table.push_back(e);
	}

	if (present){
		cout << "Duplicate entity detected. Insert FAILED." << endl;
	}
	
	
}

//prints table for user
void table::display_table() {
	cout << name << endl;
	for(int i = 0; i < attribute_names.size(); i++){
		cout << attribute_names[i] << '\t';
	}
	
	cout << endl;
	
	for(int i = 0; i < entity_table.size(); i++){		
		entity_table[i].show_attributes(attribute_names);
		cout << endl;
	}
	cout << endl;
}

//chuncks a string by spaces and returns a vector with inputs
vector<string> table::split_on_spaces(string str) {
	istringstream iss(str);
	string s;
	vector<string> result;

	while (getline(iss, s, ' ')){
		result.push_back(s.c_str());
	}
	
	return result;
}

//goes through table andfinds which arguements meet set arguments and updates though values
void table::update(vector<pair<string, string>> _set_argument, condition_obj condit) {
	
	vector<int> indices_to_update = eval_condition(condit);

	for (int i = 0; i < indices_to_update.size(); i++) {
		int index = indices_to_update[i];
		for (int j = 0; j < _set_argument.size(); j++) {
			entity_table[index].set_attribute(_set_argument[0].first, _set_argument[0].second);
		}
	}
}

//goes through table and deletes arguements that meet set arguments
void table::delete_from(condition_obj condit) {

	vector<int> indices_to_update = eval_condition(condit);
	for (int i = 0; i < indices_to_update.size(); i++) {
		int index = indices_to_update[i];

		entity_table.erase(entity_table.begin() + index);
	}
}


bool do_comparison(string oper1, string op, string oper2) {
	int d_oper1, d_oper2;
	int integer_op_flag = 0;

	if (isdigit(oper1[0])) {
		d_oper1 = atoi(oper1.c_str());
		
		d_oper2 = atoi(oper2.c_str());
		integer_op_flag = 1;
	}

	if (op == "<") {
		if (integer_op_flag) {
			if (d_oper1 < d_oper2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (oper1 < oper2) {
			return true;
		}
	}
	else if (op == "<=") {
		if (integer_op_flag) {
			if (d_oper1 <= d_oper2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (oper1 <= oper2) {
			return true;
		}
	}
	else if (op == ">") {
		if (integer_op_flag) {
			if (d_oper1 > d_oper2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (oper1 > oper2) {
			return true;
		}
	}
	else if (op == ">=") {
		if (integer_op_flag) {
			if (d_oper1 >= d_oper2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (oper1 >= oper2) {
			return true;
		}
	}
	else if (op == "==") {
		if (integer_op_flag) {
			if (d_oper1 == d_oper2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (oper1 == oper2) {
			return true;
		}
	}
	else if (op == "!=") {
		if (integer_op_flag) {
			if (d_oper1 != d_oper2) {
				return true;
			}
			else {
				return false;
			}
		}
		if (oper1 != oper2) {
			return true;
		}
	}
	return false;
}

vector<int> table::eval_condition(condition_obj condit) {
	vector<entity> entities; //for returning
	vector<int> condition_satisfactory_indices;
	vector<int> conjunction_satisfactory_indices;
	vector<int> indices_to_update;
	//loop through every conjunction (conjunction || conjunction || ...) in condition condit
	for (int i = 0; i < condit.conjunctions.size(); i++) { 
		//loop through every comparison (comparison && comparison && ..) in i-th conjunction
		for (int j = 0; j < condit.conjunctions[i].comparisons.size(); j++) {
			
			string oper1 = condit.conjunctions[i].comparisons[j].oper1;
			string oper2 = condit.conjunctions[i].comparisons[j].oper2;
			string op = condit.conjunctions[i].comparisons[j].op;
			string e_oper2;
			bool comparison_true = false;
			//loop through every entity in table
			//if oper1 (field of entity) satisfies op with oper2, then push index to satisfactory_indices
			for (int y = 0; y < entity_table.size(); y++) {
				
				e_oper2 = entity_table[y].get_attribute(oper1); //get value of attribute "oper1" (attribute name)
				
				comparison_true = do_comparison(e_oper2, op, oper2);

				if (comparison_true) {
					conjunction_satisfactory_indices.push_back(y); //since entity satisfies comparison, push back
				}

				comparison_true = false;
			}
			//check each previous satisfactory entity with new comparison

		}
		for (int x = 0; x < conjunction_satisfactory_indices.size(); x++) {
			int index = conjunction_satisfactory_indices[x];
			for (int k = condit.conjunctions[i].comparisons.size() - 1; k > -1; k--) {
				string e_oper2 = entity_table[index].get_attribute(condit.conjunctions[i].comparisons[k].oper1);
				string oper2 = condit.conjunctions[i].comparisons[k].oper2;
				string op = condit.conjunctions[i].comparisons[k].op;
				bool comparison_true = do_comparison(e_oper2, op, oper2);

				if (!comparison_true) {
					conjunction_satisfactory_indices.erase(conjunction_satisfactory_indices.begin() + x); //remove x-th index because entity does not satisfy comparison
				}
				comparison_true = false;
			}

		}

		//push every satisfactory index in conjunction into the overall satisfactory indices
		for (int j = 0; j < conjunction_satisfactory_indices.size(); j++) {
			condition_satisfactory_indices.push_back(conjunction_satisfactory_indices[j]);
		}

	}
	sort(condition_satisfactory_indices.begin(), condition_satisfactory_indices.end());
	condition_satisfactory_indices.erase(std::unique(condition_satisfactory_indices.begin(), condition_satisfactory_indices.end()), condition_satisfactory_indices.end());
	return condition_satisfactory_indices;
}
