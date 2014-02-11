#include "table.h"
#include "database.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	database db;
	//attributes list
	string name = "animals";
	vector<string> attribute_names;
	attribute_names.push_back("name");
	attribute_names.push_back("kind");
	attribute_names.push_back("years");

	//primary keys list
	vector<string> primary_key;
	primary_key.push_back("name");
	primary_key.push_back("kind");

	//creation of table using above
	table t (name, attribute_names, primary_key); 
	//database.create_table(name, attribute_names, primary_key); 
	
	//creating tuples
	//first
	vector<string> joe;
	joe.push_back("joe");
	joe.push_back("dog");
	joe.push_back("4");
	//second
	vector<string> bob;
	bob.push_back("bob");
	bob.push_back("cat");
	bob.push_back("3");
	//third
	vector<string> marty;
	marty.push_back("marty");
	marty.push_back("cat");
	marty.push_back("5");
	//forth
	vector<string> spot;
	spot.push_back("spot");
	spot.push_back("dog");
	spot.push_back("6");
	
	
	//creating vector for rename
	vector<string> renames;
	renames.push_back("id");
	renames.push_back("species");
	renames.push_back("years");
	
	
	
	cout<<endl<<endl;
	cout<<"TESTING UNION"<<endl;
	db.create_table("dogs", attribute_names, primary_key);
	db.create_table("cats", attribute_names, primary_key);
	db.get_table("dogs").insert(joe);
	db.get_table("dogs").insert(spot);
	db.get_table("cats").insert(bob);
	db.get_table("cats").insert(marty);
	
	cout<<"PRINTING=====================Dogs"<<endl;
	db.get_table("dogs").display_table();
	cout<<"PRINTING=====================Cats"<<endl;
	db.get_table("cats").display_table();
	cout<<"PRINTING=====================Union"<<endl;
	table temp = db.set_union("pets", "cats", "dogs");
	temp.display_table();
	cout<<"PRINTING=====================Differnce"<<endl;
	table temp2 = db.set_difference("animals", "cats", "dogs");
	temp2.display_table();
	cout<<"PRINTING=====================Rename"<<endl;
	table temp3 = db.set_renaming("pests", "cats", renames);
	temp3.display_table();
	cout<<"PRINTING=====================projection"<<endl;
	vector<string> species;
	species.push_back("kind");
	species.push_back("name");
	table temp4 = db.set_projection("proj", "cats", species);
	temp4.display_table();
	cout<<"PRINTING=====================selection"<<endl;
	vector<string> felines;
	felines.push_back("cat");
	table temp5 = db.set_selection("sell", "cats", felines);
	temp5 = db.set_selection("sell", "cats", felines);
	temp5.display_table();
	felines.push_back("6");
	table temp6 = db.set_selection("sell", "dogs", felines);
	temp6.display_table();
/*
//Testing cross product ---------------------------------------------------------------------------
	vector<string> circle;
	circle.push_back("circle");
	vector<string> square;
	square.push_back("square");
	vector<string> rectangle;
	rectangle.push_back("rectangle");

	vector<string> red;
	red.push_back("red");
	vector<string> blue;
	blue.push_back("blue");

	vector<string> attribute_names2;
	attribute_names2.push_back("shape");

	vector<string> primary_key2;
	primary_key2.push_back("shape");

	vector<string> attribute_names3;
	attribute_names3.push_back("color");

	vector<string> primary_key3;
	primary_key3.push_back("color");

	db.create_table("shapes", attribute_names2, primary_key2);
	db.create_table("colors", attribute_names3, primary_key3);
	db.get_table("shapes").insert(circle);
	db.get_table("shapes").insert(square);
	db.get_table("shapes").insert(rectangle);

	db.get_table("colors").insert(red);
	db.get_table("colors").insert(blue);
	table product_test = db.set_cross_product("product test", "shapes", "colors");
	cout << "CROSS PRODUCT TEST ==============================================" << endl;
	product_test.display_table();
*/
	//selection test

	//db.set_selection("bob", "kind", "5");


//Testing natural join ---------------------------------------------------------------------------

	db.get_table("cats").insert(joe);
	db.get_table("cats").insert(spot);

	table natural_join_test = db.set_natural_join("natural join test", "cats", "dogs");
	natural_join_test.display_table();






	cin.get();
	return 0;
}