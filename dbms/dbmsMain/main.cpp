#include "database.h"
#include "parser.h"
#include "Application.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main() {


	database db;
	parser p(db);

	ifstream ifs("input.txt", ifstream::in);
	stringstream ss;
	string line;
	while (getline(ifs, line)) {
		ss << line << '\n';
	}

	p.set_ss_ptr(ss);
	p.evaluate_statement();


	//Application A(db, p);
	//A.initialize();

	
	system("pause");
	return 0;
}
