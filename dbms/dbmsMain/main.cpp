#include "database.h"
#include "parser.h"
#include "tokenizer.h"
#include "Application.h"
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	database db;
	parser p(db);
	
	stringstream ss;
	ss << "CREATE TABLE shapes(shape VARCHAR(20)) PRIMARY KEY(shape);" <<
		"INSERT INTO shapes VALUES FROM(\"circle\");" <<
		"INSERT INTO shapes VALUES FROM(\"square\");" <<
		"INSERT INTO shapes VALUES FROM(\"rectangle\");" <<
		"INSERT INTO shapes VALUES FROM(\"triangle\");" <<
		"SHOW shapes;" <<
		"CREATE TABLE colors(color VARCHAR(20)) PRIMARY KEY(color);" <<
		"INSERT INTO colors VALUES FROM(\"red\");" <<
		"INSERT INTO colors VALUES FROM(\"blue\");" <<
		"SHOW colors;" <<
		"product_test <-shapes * colors;"<<
		"SHOW product_test;";
	cin.rdbuf(ss.rdbuf());
	p.evaluate_statement();
	


	//Application A(db, p);
	//A.initialize();

	
	system("pause");
	return 0;
}
