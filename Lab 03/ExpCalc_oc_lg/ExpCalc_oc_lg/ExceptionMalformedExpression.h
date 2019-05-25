#include <exception>

class ExceptionMalformedExpression : public std::exception
{
public:
	const char* what() const { return "Error: Malformed expression - allowed characters: +, -, *, /, %, (, ). Operators and operands must be separated by spaces."; }
};