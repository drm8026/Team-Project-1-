#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>

class myexception : public std::exception {
private:
	std::string message;
public:
	myexception(const std::string& msg);
	virtual const char* what() const throw()
	{
		return message.c_str();
	}


};

inline myexception::myexception(const std::string& msg) : message(msg) {}

#endif