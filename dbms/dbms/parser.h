#ifndef PARSER_H
#define PARSER_H

#include "database.h"
#include "tokenizer.h"
#include <string>
#include "table.h"

using namespace std;
class typed_attribute {
public:
	vector<string> list;
	vector<pair<int, int>> types; //<1, int> means type varchar of length int, <2, 0> means type integer
								  //first int specifies type of variable, second specifies length assuming its a string
};

class comparison_obj {
public:
	string oper1;
	string op;
	string oper2;
};
class conjunction_obj {
public:
	vector<comparison_obj> comparisons; //&& between elements
};
class condition_obj {
public:
	vector<conjunction_obj> conjunctions; //|| between elements
};


class parser {
public:

	char alpha();
	string identifier();
	string keyword();
	string relation_name();
	string attribute_name();
	condition_obj condition();
	conjunction_obj conjunction();
	comparison_obj comparison();
	int type();
	pair<int, int> attr_type();
	typed_attribute typed_attribute_list();
	vector<string> attribute_list();
	vector<string> literal_list();
	//commands
	table create_cmd();		//creates a table
	string close_cmd();		//writes and then drops table
	string show_cmd();		//prints
	void write_cmd();		//drops table writes to a file, name+.db
	void delete_cmd();		//deletes entry
	void open_cmd();		//loads table form a text file
	void exit_cmd();		//exit(0)
	void insert_cmd();		//inserts a tuple
	void update_cmd();		//updates values in a table
};

#endif

