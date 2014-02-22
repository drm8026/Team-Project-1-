#include "tokenizer.h"
Token_stream::Token_stream() :full(false), buffer(0) {}   // no Token in buffer
void Token_stream::putback(Token t)
{
	if (full) cerr << "";
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}
Token Token_stream::get()
{
	if (full) {       // do we already have a Token ready?
		// remove token from buffer
		full = false;
		return buffer;
	}

	char ch;
	if (cin >> ch) {    // note that >> skips whitespace (space, newline, tab, etc.)


		switch (ch) {
		case ',': case '(': case ')': case '+': case '-': case '*':
		case '/': case '<': case '>': case '=': case '!': case '&':
		case '|': case ';': case '"': case '_':
		{
			return Token(ch);        // let each character represent itself
		}

		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch);         // put digit back into the input stream         
			int val;
			cin >> val;              // read a floating-point number
			return Token('8', val);   // let '8' represent "a number"
		}

		default:
			;//error("Bad token");
		}
		if (isalpha(ch) && islower(ch)) { //is ch an alphabetical character?
			return Token('9', ch);	//let '9' represent "a string"
		}
		else if (isalpha(ch) && isupper(ch)) {
			return Token('7', ch);
		}
	}
	else {
		return Token('0');
	}
}