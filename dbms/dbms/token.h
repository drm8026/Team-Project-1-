#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
	char kind;        // what kind of token
	int value;     // for numbers: a value 
	char letter;
	Token(char ch)    // make a character Token from a char
		:kind(ch), value(0), letter('\0') { }
	Token(char ch, char ch2)	// make a letter Token from a char and a letter
		:kind(ch), value(0), letter(ch2){ }
	Token(char ch, int val)   // make a number Token from a char and a double
		:kind(ch), value(val), letter('\0') { }

};

#endif