#ifndef COMPARISON_OBJ_H
#define COMPARISON_OBJ_H
#include <string>
#include <vector>
class comparison_obj {
public:
	std::string oper1;			//operand one
	std::string op;				//operation +,-,*,/, &,|
	std::string oper2;			//operand two
	bool operator==(const comparison_obj& c);		//overloaded boolean operator to define equality
};

inline bool comparison_obj::operator == (const comparison_obj& c){
	if (oper1 == c.oper1 &&
		op == c.op &&
		oper2 == c.oper2) {
		return true;
	}
	else {
		return false;
	}
}
#endif
