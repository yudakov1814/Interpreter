#include <stdexcept>
#include "analyzer.h"

bool ischar(char ch) {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

lexeme get_next_lexeme(const string& text, int& cur_idx) {
	char cur_ch = text[cur_idx];
	cur_idx++;

	lexeme result;
	result.value = cur_ch;

	if (ischar(cur_ch)) {
		result.lexeme_type = lexemeType::VARIABLE;
		cur_ch = text[cur_idx];
		while (cur_idx < text.size() && ischar(cur_ch) || isdigit(cur_ch)) {
			result.value += cur_ch;
			cur_idx++;
			cur_ch = text[cur_idx];
		}
		if (result.value == "int") {
			result.lexeme_type = lexemeType::INT;
		}
		else if (result.value == "array") {
			result.lexeme_type = lexemeType::ARRAY;
		}
		else if (result.value == "if") {
			result.lexeme_type = lexemeType::IF;
		}
		else if (result.value == "else") {
			result.lexeme_type = lexemeType::ELSE;
		}
		else if (result.value == "while") {
			result.lexeme_type = lexemeType::WHILE;
		}
		else if (result.value == "read") {
			result.lexeme_type = lexemeType::READ;
		}
		else if (result.value == "write") {
			result.lexeme_type = lexemeType::WRITE;
		}
	}
	else if (isdigit(cur_ch)) {
		result.lexeme_type = lexemeType::NUMBER;
		cur_ch = text[cur_idx];
		while (cur_idx < text.size() && isdigit(cur_ch)) {
			result.value += cur_ch;
			cur_idx++;
			cur_ch = text[cur_idx];
		}
		if (cur_idx < text.size() && ischar(cur_ch)) {
			while (cur_idx < text.size() && ischar(cur_ch)) {
				result.value += cur_ch;
				++cur_idx;
				cur_ch = text[cur_idx];
			}
			result.lexeme_type = lexemeType::ERROR;
		}
	}
	else if (cur_ch == '{') {
		result.lexeme_type = lexemeType::LEFT_BRACE;
	}
	else if (cur_ch == '}') {
		result.lexeme_type = lexemeType::RIGHT_BRACE;
	}
	else if (cur_ch == '[') {
		result.lexeme_type = lexemeType::LEFT_SQUARE_BRACKET;
	}
	else if (cur_ch == ']') {
		result.lexeme_type = lexemeType::RIGHT_SQUARE_BRACKET;
	}
	else if (cur_ch == '(') {
		result.lexeme_type = lexemeType::LEFT_ROUND_BRACKET;
	}
	else if (cur_ch == ')') {
		result.lexeme_type = lexemeType::RIGHT_ROUND_BRACKET;
	}
	else if (cur_ch == '+') {
		result.lexeme_type = lexemeType::PLUS;
	}
	else if (cur_ch == '-') {
		result.lexeme_type = lexemeType::MINUS;
	}
	else if (cur_ch == '*') {
		result.lexeme_type = lexemeType::MULTIPLY;
	}
	else if (cur_ch == '/') {
		result.lexeme_type = lexemeType::DIVIDE;
	}
	else if (cur_ch == ';') {
		result.lexeme_type = lexemeType::SEMICOLON;
	}
	else if (cur_ch == ',') {
		result.lexeme_type = lexemeType::COMMA;
	}
	else if (cur_ch == '<') {
		result.lexeme_type = lexemeType::LESS;
		if (cur_idx < text.size() && text[cur_idx] == '=') {
			cur_idx++;
			result.lexeme_type = lexemeType::LESS_OR_EQUAL;
			result.value = "<=";
		}
	}
	else if (cur_ch == '=') {
		result.lexeme_type = lexemeType::ASSIGN;
		if (cur_idx < text.size() && text[cur_idx] == '=') {
			cur_idx++;
			result.lexeme_type = lexemeType::EQUAL;
			result.value = "==";
		}
	}
	else if (cur_ch == '>') {
		result.lexeme_type = lexemeType::MORE;
		if (cur_idx < text.size() && text[cur_idx] == '=') {
			cur_idx++;
			result.lexeme_type = lexemeType::MORE_OR_EQUAL;
			result.value = ">=";
		}
	}
	else if (cur_ch == '!' && cur_idx + 1 < text.size() && text[cur_idx + 1] == '=') {
		cur_idx++;
		result.lexeme_type = lexemeType::NOT_EQUAL;
		result.value = "!=";
	}

	return result;
}

vector<lexeme> analyze(const string& text) {
	vector<lexeme> result;
	lexeme cur_lexeme;
	int cur_line = 1;
	int cur_pos = 1;
	int cur_idx = 0;

	while (cur_idx < text.size()) {
		while (isspace(text[cur_idx])) {
			switch (text[cur_idx++]) {
			case ' ':
				++cur_pos;
				break;
			case '\f':
			case '\n':
			case '\v':
				++cur_line; cur_pos = 1;
				break;
			case '\t':
				cur_pos += 4;
				break;
			}
		}

		cur_lexeme = get_next_lexeme(text, cur_idx);
		cur_lexeme.line = cur_line;
		cur_lexeme.pos = cur_pos;

		if (cur_lexeme.lexeme_type == lexemeType::ERROR) {
			string msg = "Analyzer error; line = " + to_string(cur_line) + ", pos = " + to_string(cur_pos);
			throw runtime_error(msg);
		}

		cur_pos += cur_lexeme.value.size();

		result.push_back(cur_lexeme);
	}

	cur_lexeme.lexeme_type = lexemeType::FINISH;
	cur_lexeme.line = cur_line;
	cur_lexeme.pos = cur_pos;
	result.push_back(cur_lexeme);

	return result;
}