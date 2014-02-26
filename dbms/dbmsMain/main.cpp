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

	Application A(db, p);
	A.initialize();

	
	system("pause");
	return 0;
}
