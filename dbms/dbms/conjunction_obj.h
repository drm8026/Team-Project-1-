#ifndef CONJUNCTION_OBJ_H
#define CONJUNCTION_OBJ_H
#include "comparison_obj.h"

//an operand term or multiple terms anded together
class conjunction_obj {
public:
	std::vector<comparison_obj> comparisons; //&& between elements
	bool operator==(const conjunction_obj& c);
};

inline bool conjunction_obj::operator == (const conjunction_obj& c) {	//overloaded boolean operator
	bool is_equal = false;
	if (comparisons.size() != c.comparisons.size()) {			//unequal size means unequal terms
		return false;
	}
	for (int i = 0; i < comparisons.size(); i++) {
		if (comparisons[i] == c.comparisons[i]) {		//go through and confirm equality fail at first equality
			is_equal = true;
		}
		else {
			return false;
		}
	}
	return is_equal;
}

#endif