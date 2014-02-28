#ifndef PARSER_H
#define PARSER_H

#include "database.h"
#include "token_stream.h"
#include "typed_attribute.h"
#include <string>

using namespace std;
class parser {
public:

	database* db_ptr = new database(); //pointer to a database object
	stringstream * ss_ptr;
	
	parser() {};
	parser(database& db) { db_ptr = &db; } //assign the db pointer to a passed database object

	void set_ss_ptr(stringstream &ss) {
		ss_ptr = &ss;
		ts = Token_stream(*ss_ptr);
	}

	char alpha();
	std::string identifier();
	std::string keyword();
	std::string relation_name();
	std::string attribute_name();
	table atomic_expr();
	table expr();
	condition_obj condition();
	conjunction_obj conjunction();
	comparison_obj comparison();
	int type();
	pair<int, int> attr_type();
	typed_attribute typed_attribute_list();
	vector<string> attribute_list();
	vector<string> literal_list();
	vector<string> split_on_spaces(string);

	//commands	
	table create_cmd();
	std::string close_cmd();
	std::string show_cmd();
	void insert_cmd();
	void update_cmd();
	void write_cmd();		//drops table writes to a file, name+.db
	void delete_cmd();		//deletes entry
	void open_cmd();		//loads table form a text file
	void exit_cmd();		//exit(0)

	//queries
	void query();
	table selection_qry();
	table projection_qry();
	table attribute_qry();
	table renaming_qry();
	table tables_qry();


	void evaluate_statement(); //reads from cin to evaluate statements
	Token_stream ts;
};

#endif

