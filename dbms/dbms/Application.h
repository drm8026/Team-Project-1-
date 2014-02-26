#ifndef APPLICATION_H
#define APPLICATION_H

#include "parser.h"
#include <cctype>

class Application{
	private:
		database * db;		//a database for storing all relations and views
		parser * p;			//parser to read user input and pass instructions to database
	public:
		Application(database& _db, parser& _p) { db = &_db; p = &_p; }

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//											Display Functions
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		void print_tables();				//print a list of all tables currently in databse
		void print_size();					//testing purposes, used to show differnce in database tables size
		void display_menu();				//prints default menu for user to read what inputs are accepted
		void display_detailed_menu();		//in case of typo or confusion to what they do "Help" displays descriptions
											//of all functions

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//											Helper Functions
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		vector<string> split_on_spaces(string str){  //given a string divides a string into a vector and returns vector
			istringstream iss(str);
			string s;
			vector<string> result;

			while (getline(iss, s, ' '))
			{
				result.push_back(s.c_str());
			}

			return result;
		}	 

		string prompt_tuple(string name);			//prompts user on input values of a table into a specific table
		string prompt_primary();					//prompts user on primary key by which to identify unique tuples
		string prompt_type(string attr);			//prompts types of attribute list varchar or integer
		string prompt_attributes();					//prompts user on name of attribute list for create table
		string prompt_reattributes();				//prompts user on name of new attributes for rename
		string prompt_condition(string name);		//used to prompt user on attribute list and compare using operators

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//											Query Functions
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		string prompt_select(string name);			//prompts user on what values of attributes to select
		string prompt_project(string name);			//prompts user on what attributs to project
		string prompt_filter();						//prompts user on how to filter a table project or select
		string prompt_combine();					//prompts user on how to combine two relations + - *
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//											Command Functions
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		string prompt_remove();				//user input to compare to values, remove any that match requirements
		string prompt_rename();				//user inputs a new attribute lists names
		string prompt_update();				//user input to compare to values, set values that match requirements
		string prompt_add();				//adds a new tuple to a relation from user input
		string prompt_new_table();			//creates a new table using user input
		string prompt_save();				//writes a table to an output file, "file.db"
		string prompt_open();				//opens a table from a input file, "file.db"
		string prompt_close();				//writes a table to an output file, "file.db", drops table from database
		string prompt_display();			//displays table to screen
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//									MAIN INITIALIZATION FUNCTION
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		void initialize();					//initializes menu and displays prompts based on input
};

#endif