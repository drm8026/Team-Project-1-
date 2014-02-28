#include "Application.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Display Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Application::print_tables(){
	//uses get_tables_vector to traverse db's tables and print their names
	for (int i = 0; i < db->get_tables_vector().size(); i++){					
		cout << "Table " << i + 1 << ": " <<								
			db->get_tables_vector()[i].get_name() << endl;
	}
}
void Application::print_size(){
	cout << db->get_tables_vector().size();
}
void Application::display_menu(){
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "                                    Commands and Queries                              	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "                                         Add                    				" << endl;
	cout << "                                       Remove									" << endl;
	cout << "                                       Combine									" << endl;
	cout << "                                        Display									" << endl;
	cout << "                                          New                 						" << endl;
	cout << "                                         Save										" << endl;
	cout << "                                         Open             						" << endl;
	cout << "                                      SaveAndClose								" << endl;
	cout << "                                      Help(For testing)								" << endl;
	cout << "                                         Rename									" << endl;
	cout << "                                         Filter									" << endl;
	cout << "                                     Exit(To terminate)								" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
}
void Application::display_detailed_menu(){
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "                                    Commands and Queries                              	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        AddToZoo     : Add a Zoo to a specific collection.             				" << endl;
	cout << "        RemoveFromZoo  : Remove a specific or collection of Zoos that 					" << endl;
	cout << "		                meet a condition."											      << endl;
	cout << "        CombineZoos : Perform an operation on collections of Zoos						" << endl;
	cout << "                       Add, Cross, Difference."										  << endl;
	cout << "        DisplayZoo : Display the contents of a collection with specified 				" << endl;
	cout << "		                 name.		"												      << endl;
	cout << "        RenameZoo  : Renames a Zoo to users specifications								" << endl;
	cout << "        NewZoo     : Creates a new collection of Zoos 									" << endl;
	cout << "        SaveZoo : Saves values to a file for future readi	ng							" << endl;
	cout << "        OpenZoo : Opens and reads from a file a Zoo       								" << endl;
	cout << "        SaveAndCloseZoo : Closes and saves values to a file 							" << endl;
	cout << "        Help          :	You should know you are here, but it prints					" << endl;
	cout << "    					detailed description of each instruction						" << endl;
	cout << "        FilterZoo	: Filters a Collection based on input								" << endl;
	cout << "        Exit(To terminate)	: Terminates Application    								" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Helper Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string Application::prompt_primary(){
	string attr_list;			//full command of space delimited primary keys
	vector<string> split_list;		//full command of primary keys in vector
	stringstream ss;		//used for final return including braces and brackets
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What key values would you like to use to specify unique entries? " << endl;
	cout << "i.e. two entries cannot have the same name and age	  	" << endl;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear junk from cin
	getline(cin, attr_list);					
	split_list = split_on_spaces(attr_list);		//divide attr_list into a vector

	ss << "PRIMARY KEY (";
	
	//store the divided vector into primary key with commas between values
	for (int i = 0; i < split_list.size(); i++){				
		
		ss << split_list[i];										
		if (i < split_list.size() - 1){
			ss << ", ";
		}

	}
	
	ss << ")";
	return ss.str();			//returns (primary, key, in, this, format)
}
string Application::prompt_type(string attr){
	string type;			//stores users input of string or int
	stringstream ss;		//used for final return including braces and brackets
	int length;					//each string will have a length
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "Is " << attr << " a number or a word? " << endl;
	cout << "enter \"number\" or \"word\" without the quotes " << endl;
	cout << "i.e. color is a word such as blue or green, age would be a number like 3" << endl;
	cin >> type;
	
	//if its a varchar then it will have a length
	if (type == "word"){
		cout << "---------------------------------------------------------------------------		" << endl;
		cout << "What is the maximum length " << attr << " can have?" << endl;
		cout << "i.e. name can only be 8 letters long" << endl;
		cin >> length;
		type = "VARCHAR";
	}
	//else it will be just an integer
	else if (type == "number"){
		type = "INTEGER";
	}

	//store the attribute and the type into final return
	ss << attr << " " << type;

	//if its a word will have a length parameter too
	if (type == "VARCHAR"){
		ss << "(" << length << ")";
	}
	return ss.str();
}
string Application::prompt_attributes(){
	string attr_list;			//full command of space delimited attributes
	vector<string> split_list;		//full command split into a vector of attributes names
	stringstream ss;		//used for final return including braces and brackets
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What descriptions do you want in your collection?" << endl;
	cout << "i.e. name age color statistics	  	" << endl;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clear junk from cin
	getline(cin, attr_list);
	split_list = split_on_spaces(attr_list);	//chunks attributes into a vector

	ss << " (";
	//stores vector into parentheses with commas between values
	for (int i = 0; i < split_list.size(); i++){
		ss << prompt_type(split_list[i]);
		if (i < split_list.size() - 1){
			ss << ", ";
		}

	}
	ss << ")";
	return ss.str();			//returns (attr,list, in, format)
}
string Application::prompt_reattributes(){
	string attr_list;			//full command of space delimited attributes
	vector<string> split_list;		//full command split into a vector of attributes names
	stringstream ss;		//used for final return including braces and brackets
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What descriptions do you want your collection's current ones renamed to?" << endl;
	cout << "i.e. name age color statistics	  	" << endl;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//clears junk from cin
	getline(cin, attr_list); 
	split_list = split_on_spaces(attr_list);		//splits into a vector
	
	ss << " (";
	//stores values betwene parentheses with commas between values
	for (int i = 0; i < split_list.size(); i++){
		ss << split_list[i];
		if (i < split_list.size() - 1){
			ss << ", ";
		}

	}
	ss << ")";
	return ss.str();	//returns (reattr, list, in, format)
}
string Application::prompt_tuple(string name){
	string attribute;			//full command of space delimited attributes
	vector<string> split_list;		//full command split into a vector of attributes names
	stringstream ss;		//used for final return including braces and brackets
	vector <string> table_attr_list = db->get_table(name).attribute_names;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What values would you like for ";
	//prompts user on each attr and pushes back into a vector
	for (int i = 0; i < table_attr_list.size(); i++){
		cout << table_attr_list[i] << "?" << endl;
		cin >> attribute;
		split_list.push_back(attribute);
	}

	ss << " (";
	//stores values into parentheses and checks if value is a word, if so encapsulates in quotes
	for (int i = 0; i < split_list.size(); i++){
		//value is a varchar
		if (isalpha(split_list[i][0])){		
			split_list[i] = '"' + split_list[i] + '"';
		}
		
		ss << split_list[i];
		//inserts comma after non edge values
		if (i < split_list.size() - 1){
			ss << ", ";
		}

	}
	ss << ")";
	return ss.str();	//returns (tuple, "in", "this", format)
}
string Application::prompt_condition(string name)
{

	vector<string> split_list;		//full command split into a vector of attributes names
	vector<string> literals;		//strings containing &&, or, or ==, each pairing with a key specified
	vector<string> conj;		//strings containing &&, or, or ==, each pairing with a key specified
	string attr_list;			//full command of space delimited attributes
	string conjugate;					//value contianing equals, not equals, greater than, or less than
	string value;				//value to compare a attribute to
	stringstream ss;		//used for final return including braces and brackets
	vector <string> table_attr_list = db->get_table(name).attribute_names;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What descriptors do you want to check against?" << endl;
	cout << "choices:  	";
	
	for (int j = 0; j < table_attr_list.size(); j++)
	{
		cout << table_attr_list[j] << " ";
	}

	cout << endl;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');		//clears junk from cin
	getline(cin, attr_list); 
	split_list = split_on_spaces(attr_list);				//now has a vector of attrs


	cout << "-------------------------------------------------------------------------------		" << endl;

	//prompts user for each attribute and asks how they would like to check against
	for (int i = 0; i < split_list.size(); i++)
	{
		cout << "For " << split_list[i] << ", what value do you want to compare to?" << endl;
		cin >> value;
		literals.push_back(value);
		cout << "For " << split_list[i] << ", Do want want values lower, equal to, not equal, or greater?" << endl;
		cout << "Enter \"less\", \"equal\",\"nequal\", or \"greater\".	  	" << endl;
		cin >> conjugate;
		conj.push_back(conjugate);
	}


	ss << " (";
	for (int i = 0; i < split_list.size(); i++)
	{
		ss << split_list[i];

		//checks for each functiont check against and adds to stringstream
		if (conj[i] == "equal")
		{
			ss << "==";
		}

		else if (conj[i] == "nequal")
		{
			ss << "!=";
		}

		else if (conj[i] == "greater")
		{
			ss << ">";
		}

		else if (conj[i] == "less")
		{
			ss << "<";
		}

		//encapsulates if literal is a string
		if (isalpha(literals[i][0]))
		{		//value is a varchar
			literals[i] = '"' + literals[i] + '"';
		}

		ss << literals[i];
		
		//ands every check until edge case
		if (i < split_list.size() - 1)
		{
			ss << " && ";
		}

	}
	ss << ") ";
	return ss.str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Query Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool check_if_string(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (!isalpha(s.at(i))) {
			return false;
		}
	}
	return true;
}
string Application::prompt_select(string name){

	vector<string> split_list;		//full command split into a vector of attributes names
	vector<string> literals;		//strings containing &&, or, or ==, each pairing with a key specified
	vector<string> conj;		//strings containing &&, or, or ==, each pairing with a key specified
	string attr_list;			//full command of space delimited attributes
	string conjugate;					//value contianing equals, not equals, greater than, or less than
	string value;				//value to compare a attribute to
	stringstream ss;		//used for final return including braces and brackets
	vector <string> table_attr_list = db->get_table(name).attribute_names;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What descriptors do you want to filter your collection by?" << endl;
	cout << "i.e. name age color statistics	  	" << endl;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');		//clears junk from cin
	getline(cin, attr_list); 
	split_list = split_on_spaces(attr_list);				//now has a vector of strings


	cout << "-------------------------------------------------------------------------------		" << endl;
	
	//prompts user for each value in attribute list and how user wants to check agianst them, as well as what
	//literal to check against
	for (int i = 0; i < split_list.size(); i++){
		cout << "For " << split_list[i] << ", what value do you want to compare to?" << endl;
		cin >> value;
		if (check_if_string(value)) {
			value = '"' + value + '"';
		}
		literals.push_back(value);
		cout << "For " << split_list[i] << ", Do want want values lower, equal to, not equal, or greater?" << endl;
		cout << "Enter \"less\", \"equal\",\"nequal\", or \"greater\".	  	" << endl;
		cin >> conjugate;
		conj.push_back(conjugate);
	}


	ss << " (";
	for (int i = 0; i < split_list.size(); i++){
		ss << split_list[i];
		
		//adds to stringstream the parser language for each inequality
		if (conj[i] == "equal"){
			ss << "==";
		}
		else if (conj[i] == "nequal"){
			ss << "!=";
		}
		else if (conj[i] == "greater"){
			ss << ">";
		}
		else if (conj[i] == "less"){
			ss << "<";
		}
		ss << literals[i];

		if (i < split_list.size() - 1){
			ss << " && ";
		}

	}
	ss << ") ";
	return ss.str();
}
string Application::prompt_project(string name){
	string attr_list;			//full command of space delimited attributes
	vector<string> split_list;		//full command split into a vector of attributes names
	stringstream ss;		//used for final return including braces and brackets
	vector <string> table_attr_list = db->get_table(name).attribute_names;	//saves the attribute list of current table
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "What descriptors in " << name << " would you like to filter by?  " << endl;
	cout << "Enter all to filter by seperated by spaces i.e. \"name age color\" without quotes." << endl;

	for (int i = 0; i < table_attr_list.size(); i++){				//print out the attribute list
		cout << table_attr_list[i] << " ";
	}
	cout << endl;

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clears junk from cin
	getline(cin, attr_list); 							
	split_list = split_on_spaces(attr_list);	//split string into vector for usage

	ss << " (";
	//fill stringstream with attributes to project seperated by commas
	for (int i = 0; i < split_list.size(); i++){
		ss << split_list[i];
		if (i < split_list.size() - 1){
			ss << ", ";
		}
	}
	ss << ") ";
	return ss.str();
}
string Application::prompt_filter(){
	string table1, view;	//name of both tables, table1 for existing, view for new name
	string filter;		//the value entered by user to define project or select
	string elements;		//can be attributes or a tuple
	stringstream ss;

	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        From which Zoo would you like to filter?                          			" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();

	cout << "----------Enter the tables name------------------------------------------------		" << endl;
	cin >> table1;

	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        What would you like to call this filtered collection?                         	" << endl;
	cin >> view;

	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        How would you like to filter " << table1 << "                         			" << endl;
	cout << "Filter by description(name, age) or by values (name is bob)                        	" << endl;
	cout << "Enter \"Description\" or \"Value\" without the parentheses                      		" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cin >> filter;
	
	//decides which function to send user to based on description or value
	if (filter == "Description"){
		filter = "project";
		elements = prompt_project(table1);
	}
	else if (filter == "Value"){
		filter = "select";
		elements = prompt_select(table1);
	}
	
	ss << view << " <- " << filter << elements << table1;
	return ss.str();
}
string Application::prompt_rename(){
	string view;
	string table1;
	stringstream ss;
	string attributes = "";
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        What would you like to call this renamed collection?                         	" << endl;
	cin >> view;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "	     Which Zoo would you like to rename the descriptors of?    					" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	
	cout << "----------Enter the Tables name -----------------------------------------------		" << endl;
	cin >> table1;
	attributes = prompt_reattributes();
	
	ss << view << " <-" << " rename " << attributes << table1;
	return ss.str();
}
string Application::prompt_combine(){
	string table1, table2;
	string view;
	string operation; // union, differnce, or cross
	stringstream ss;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        What would like to call your new Zoo                         				" << endl;
	cin >> view;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        Which Zoos would you like to combine?										" << endl;
	print_tables();
	
	cout << "----------Enter the first tables name-------------------------------------------		" << endl;
	cin >> table1;
	
	cout << "----------Enter the second tables name------------------------------------------		" << endl;
	cin >> table2;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        How would you like to combine these two Zoos?								" << endl;
	cout << "	 -> To view every Animal in both Zoo's type \"Union\" wihtout the quotes.      	" << endl;
	cout << "	 -> To view every Animal in one Zoo or the other, " << endl;
	cout << "	    type  \"Differnce\" wihtout the quotes. " << endl;
	cout << "    -> To view every pair of animals between both Zoo's type \"Cross\" wihtout the quotes. " << endl;
	
	cin >> operation;

	//decides which table operation user wants to use on tables
	if (operation == "Union"){
		operation = " + ";
	}
	else if (operation == "Differnce"){
		operation = " - ";
	}
	else if (operation == "Cross"){
		operation = " * ";
	}
	
	ss << view << "<-" << table1 << operation << table2;
	return ss.str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Command Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string Application::prompt_update()
{
	string table1;
	stringstream ss;
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        Which Zoo would you like to update?      	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	
	cout << "----------Enter the tables name------------------------------------------------" << endl;
	cin >> table1;
	
	//needs to prompt user on full values of tuple and saves into a string (in, this, format)
	string condition = prompt_condition(table1);
	condition = condition.substr(2, condition.size() - 4);
	int more = 1;
	string attr;
	string val;
	ss << "UPDATE " << table1 << " SET ";
	while (more) {
		cout << "Which attribute do you want to update? " << endl;
		for (int i = 0; i < db->get_table(table1).attribute_names.size(); i++){				//print out the attribute list
			cout << db->get_table(table1).attribute_names[i] << " ";
		}
		cout << endl;
		cin >> attr;
		ss << attr << " = ";
		cout << "What new value do you want " << attr << " to have?" << endl;
		cin >> val;
		if (isdigit(val.at(0))) {
			ss << val;
		}
		else {
			ss << '"' << val << '"';
		}
		cout << "Update more? (y/n)" << endl;
		char choice;
		cin >> choice;
		switch (choice) {
		case 'y':
			more = 1;
			ss << ", ";
			break;
		case 'n':
			more = 0; 
			break;
		}
	}
	ss << " WHERE " << condition;
	return ss.str();
}
string Application::prompt_remove()
{
	string table1;
	stringstream ss;

	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        Which Zoo would you like to remove from?      	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	cout << "----------Enter the tables name------------------------------------------------" << endl;
	cin >> table1;
	
	//needs to determine what conditions to apply to remove so prompts conditions
	string condition = prompt_condition(table1);
	
	condition = condition.substr(2, condition.size() - 4);
	
	ss << "DELETE FROM " << table1 << " WHERE " << condition;
	return ss.str();
}
string Application::prompt_new_table(){
	string table1;
	stringstream ss;
	string attributes = "";
	
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        What is the name of the new Zoo Collection		                         	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cin >> table1;
	
	//prompts attributes from user to use in string to pass to parser
	attributes = prompt_attributes();
	
	//prompts primary key from user to use in string to pass to parser
	string primary = prompt_primary();
	
	ss << "CREATE TABLE " << table1 << attributes << primary;
	return ss.str();
}
string Application::prompt_display(){
	string table1;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        Which Zoo do you want to display				                        	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	
	cout << "----------Enter the tables name------------------------------------------------" << endl;
	cin >> table1;
	return "SHOW " + table1;
}
string Application::prompt_save(){
	string table1;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "				 Which Zoo would you like to save?                  					" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	
	cout << "----------Enter the Tables name -----------------------------------------------" << endl;
	cin >> table1;
	return "WRITE " + table1;
}
string Application::prompt_open(){
	string table1;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        What is the name of the Zoo you would like to open?                       	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cin >> table1;
	
	return "OPEN " + table1;
}
string Application::prompt_close(){
	string table1;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        Which Zoo would you like to save and close?                          					" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	
	cout << "----------Enter the Tables name -----------------------------------------------" << endl;
	cin >> table1;
	return "CLOSE " + table1;
}
string Application::prompt_add(){
	string table1;
	stringstream ss;
	cout << "-------------------------------------------------------------------------------		" << endl;
	cout << "        Which Zoo would you like to add to?      	" << endl;
	cout << "-------------------------------------------------------------------------------		" << endl;
	print_tables();
	
	cout << "----------Enter the tables name------------------------------------------------" << endl;
	cin >> table1;

	//needs to prompt user on what tuple to add to table1
	string attributes = prompt_tuple(table1);
	
	ss << "INSERT INTO " << table1 << " VALUES FROM " << attributes;
	return ss.str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//											Main Initialization Function
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Application::initialize(){
	streambuf * buf = cin.rdbuf(); //back up cin buffer in a clean state
	string parsed_inst;						//used for achievement, player, and game names
	string command;							//used to keep track of switch case
	bool exit = false;
	display_menu();
	while (1){
		cout << "What would you like to do=>" << endl;
		cin.clear();
		cin.rdbuf(buf); //every loop restore cin buffer to clean state stored previously
		cin >> command;
		stringstream eval_input;
		eval_input.clear();
		eval_input.str(string()); //set eval_input's buffer to an empty string
		
		if (command == "add"){
			parsed_inst = prompt_add();
		}
		else if (command == "remove"){
			parsed_inst = prompt_remove();
		}
		else if (command == "combine"){
			parsed_inst = prompt_combine();
		}
		else if (command == "display"){
			parsed_inst = prompt_display();
		}
		else if (command == "new"){
			parsed_inst = prompt_new_table();
		}
		else if (command == "update"){
			parsed_inst = prompt_update();
		}
		else if (command == "save"){
			parsed_inst = prompt_save();
		}
		else if (command == "open"){
			parsed_inst = prompt_open();
		}
		else if (command == "saveandclose"){
			parsed_inst = prompt_close();
		}
		else if (command == "filter"){
			parsed_inst = prompt_filter();
		}
		else if (command == "help"){
			cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
			display_detailed_menu();
			continue;
		}
		else if (command == "rename"){
			parsed_inst = prompt_rename();
		}
		else if (command == "exit"){
			parsed_inst = "EXIT";
		}
		else{
			cout << "Type In The Keyword Of The Action You Would Like To Perform." << endl;
			display_detailed_menu();
			continue;
		}
		parsed_inst = parsed_inst + ';';
		eval_input << parsed_inst; //set eval_input to the command string to send to parser
		p->set_ss_ptr(eval_input);  //set cin's buffer to eval_inputs buffer so parser can read the command
		p->evaluate_statement();
	}
}