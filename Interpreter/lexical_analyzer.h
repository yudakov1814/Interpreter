#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "interpret_exception.h"

enum class lexemeType
{
	VARIABLE, // variable
	NUMBER, // number
	INT, // int
	ARRAY, // array
	IF, // if
	ELSE, // else
	WHILE, // while
	READ, // read
	WRITE, // write
	LEFT_BRACE, // {
	RIGHT_BRACE, // }
	LEFT_SQUARE_BRACKET, // [
	RIGHT_SQUARE_BRACKET, // ]
	LEFT_ROUND_BRACKET, // (
	RIGHT_ROUND_BRACKET, // )
	PLUS, // +
	MINUS, // -
	MULTIPLY, // *
	DIVIDE, // /
	SEMICOLON, // ;
	COMMA, // ,
	LESS, // <
	ASSIGN, // =
	MORE, // >
	EQUAL, // ==
	LESS_OR_EQUAL, // <=
	MORE_OR_EQUAL, // >=
	NOT_EQUAL, // !=
    FINISH, // last lexeme
	ERROR // error lexeme
};

struct lexeme
{
	lexemeType lexeme_type;
	std::string value;
	debugInfo debug_info;
};

std::istream& operator>>(std::istream&, lexeme&);
std::vector<lexeme> analyze_text(std::istream&);

std::ostream& operator<<(std::ostream&, const lexemeType&);
std::ostream& operator<<(std::ostream&, const lexeme&);
std::ostream& operator<<(std::ostream&, const std::vector<lexeme>&);