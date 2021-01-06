#pragma once
#include <string>
#include <vector>

using namespace std;

enum class lexemeType
{
	VARIABLE,
	NUMBER,
	INT,
	ARRAY,
	IF,
	ELSE,
	WHILE,
	READ,
	WRITE,
	LEFT_BRACE,
	RIGHT_BRACE,
	LEFT_SQUARE_BRACKET,
	RIGHT_SQUARE_BRACKET,
	LEFT_ROUND_BRACKET,
	RIGHT_ROUND_BRACKET,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	SEMICOLON,
	COMMA,
	LESS,
	ASSIGN,
	MORE,
	EQUAL,
	LESS_OR_EQUAL,
	MORE_OR_EQUAL,
	NOT_EQUAL,
	FINISH,
	ERROR
};

struct lexeme
{
	lexemeType lexeme_type;
	string value;
	int line;
	int pos;
};

lexeme get_next_lexeme(const string&, int&);
vector<lexeme> analyze(const string&);