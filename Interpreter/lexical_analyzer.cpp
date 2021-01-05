#include <sstream>
#include "lexical_analyzer.h"
using namespace std;

bool ischar(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

ostream& operator<<(ostream& out, const lexemeType& lexeme_type) {
    switch (lexeme_type) {
    case lexemeType::VARIABLE:
        out << "variable";
        break;
    case lexemeType::NUMBER:
        out << "numbber";
        break;
    case lexemeType::INT:
        out << "int";
        break;
    case lexemeType::ARRAY:
        out << "array";
        break;
    case lexemeType::IF:
        out << "if";
        break;
    case lexemeType::ELSE:
        out << "else";
        break;
    case lexemeType::WHILE:
        out << "while";
        break;
    case lexemeType::READ:
        out << "read";
        break;
    case lexemeType::WRITE:
        out << "write";
        break;
    case lexemeType::LEFT_BRACE:
        out << "{";
        break;
    case lexemeType::RIGHT_BRACE:
        out << "}";
        break;
    case lexemeType::LEFT_SQUARE_BRACKET:
        out << "[";
        break;
    case lexemeType::RIGHT_SQUARE_BRACKET:
        out << "]";
        break;
    case lexemeType::LEFT_ROUND_BRACKET:
        out << "(";
        break;
    case lexemeType::RIGHT_ROUND_BRACKET:
        out << ")";
        break;
    case lexemeType::PLUS:
        out << "+";
        break;
    case lexemeType::MINUS:
        out << "-";
        break;
    case lexemeType::MULTIPLY:
        out << "*";
        break;
    case lexemeType::DIVIDE:
        out << "/";
        break;
    case lexemeType::SEMICOLON:
        out << ";";
        break;
    case lexemeType::COMMA:
        out << ",";
        break;
    case lexemeType::LESS:
        out << "<";
        break;
    case lexemeType::ASSIGN:
        out << "=";
        break;
    case lexemeType::MORE:
        out << ">";
        break;
    case lexemeType::EQUAL:
        out << "==";
        break;
    case lexemeType::LESS_OR_EQUAL:
        out << "<=";
        break;
    case lexemeType::MORE_OR_EQUAL:
        out << ">=";
        break;
    case lexemeType::NOT_EQUAL:
        out << "!=";
        break;
    case lexemeType::FINISH:
        out << "finish";
        break;
    case lexemeType::ERROR:
        out << "error";
        break;
    default:
        out << "unknown";
        break;
    }
    return out;
}

ostream& operator<<(ostream& out, const lexeme& lexeme) {
    out << "{ lexeme type: '" << lexeme.lexeme_type << "', value: '" << lexeme.value
        << "', row: " << lexeme.debug_info.row << ", col: " << lexeme.debug_info.col << " }";
    return out;
}

ostream& operator<<(ostream& out, const vector<lexeme>& v) {
    out << "Lexemes:\n";
    for (auto& l : v) {
        out << l << '\n';
    }
    return out;
}

istream& operator>>(istream& in, lexeme& lexeme) {
    lexeme.lexeme_type = lexemeType::ERROR;
    lexeme.value = "";
    lexeme.debug_info = {-1, -1};
    
    while (isspace(in.peek())) {
        in.get();
    }
    
    if (!in) {
        return in;
    }
    
    char ch;
    ch = in.get();
    lexeme.value = ch;
    
    if (ischar(ch)) {
        lexeme.lexeme_type = lexemeType::VARIABLE;
        while (ischar(in.peek()) || isdigit(in.peek())) {
            lexeme.value += in.get();
        }
        if (lexeme.value == "int") {
            lexeme.lexeme_type = lexemeType::INT;
        }
        else if (lexeme.value == "array") {
            lexeme.lexeme_type = lexemeType::ARRAY;
        }
        else if (lexeme.value == "if") {
            lexeme.lexeme_type = lexemeType::IF;
        }
        else if (lexeme.value == "else") {
            lexeme.lexeme_type = lexemeType::ELSE;
        }
        else if (lexeme.value == "while") {
            lexeme.lexeme_type = lexemeType::WHILE;
        }
        else if (lexeme.value == "read") {
            lexeme.lexeme_type = lexemeType::READ;
        }
        else if (lexeme.value == "write") {
            lexeme.lexeme_type = lexemeType::WRITE;
        }
    }
    else if (isdigit(ch)) {
        lexeme.lexeme_type = lexemeType::NUMBER;
        while (isdigit(in.peek())) {
            lexeme.value += in.get();
        }
        if (ischar(in.peek())) {
            while (ischar(in.peek())) {
                lexeme.value += in.get();
            }
            lexeme.lexeme_type = lexemeType::ERROR;
        }
    }
    else if (ch == '{') {
        lexeme.lexeme_type = lexemeType::LEFT_BRACE;
    }
    else if (ch == '}') {
        lexeme.lexeme_type = lexemeType::RIGHT_BRACE;
    }
    else if (ch == '[') {
        lexeme.lexeme_type = lexemeType::LEFT_SQUARE_BRACKET;
    }
    else if (ch == ']') {
        lexeme.lexeme_type = lexemeType::RIGHT_SQUARE_BRACKET;
    }
    else if (ch == '(') {
        lexeme.lexeme_type = lexemeType::LEFT_ROUND_BRACKET;
    }
    else if (ch == ')') {
        lexeme.lexeme_type = lexemeType::RIGHT_ROUND_BRACKET;
    }
    else if (ch == '+') {
        lexeme.lexeme_type = lexemeType::PLUS;
    }
    else if (ch == '-') {
        lexeme.lexeme_type = lexemeType::MINUS;
    }
    else if (ch == '*') {
        lexeme.lexeme_type = lexemeType::MULTIPLY;
    }
    else if (ch == '/') {
        lexeme.lexeme_type = lexemeType::DIVIDE;
    }
    else if (ch == ';') {
        lexeme.lexeme_type = lexemeType::SEMICOLON;
    }
    else if (ch == ',') {
        lexeme.lexeme_type = lexemeType::COMMA;
    }
    else if (ch == '<') {
        lexeme.lexeme_type = lexemeType::LESS;
        if (in.peek() == '=') {
            in.get();
            lexeme.lexeme_type = lexemeType::LESS_OR_EQUAL;
            lexeme.value = "<=";
        }
    }
    else if (ch == '=') {
        lexeme.lexeme_type = lexemeType::ASSIGN;
        if (in.peek() == '=') {
            in.get();
            lexeme.lexeme_type = lexemeType::EQUAL;
            lexeme.value = "==";
        }
    }
    else if (ch == '>') {
        lexeme.lexeme_type = lexemeType::MORE;
        if (in.peek() == '=') {
            in.get();
            lexeme.lexeme_type = lexemeType::MORE_OR_EQUAL;
            lexeme.value = ">=";
        }
    }
    else if (ch == '!' && in.peek() == '=') {
        in.get();
        lexeme.lexeme_type = lexemeType::NOT_EQUAL;
        lexeme.value = "!=";
    }
    
    return in;
}

vector<lexeme> analyze_text(istream& in) {
    vector<lexeme> result;
    lexeme lexeme;
    int current_row = 1;
    int current_col = 1;
    
    while(in) {
        while (isspace(in.peek())){
            switch (in.get()) {
                case ' ':
                    ++current_col;
                    break;
                case '\f':
                case '\n':
                case '\v':
                    ++current_row; current_col = 1;
                    break;
                case '\t':
                    current_col += 4;
                    break;
            }
        }
        
        if(in >> lexeme) {
            lexeme.debug_info.row = current_row;
            lexeme.debug_info.col = current_col;
            
            if (lexeme.lexeme_type == lexemeType::ERROR) {
                stringstream ss;
                ss << "lexical analyzer error" << endl;
                ss << lexeme << endl;
                throw MyInterpretException(ss.str(), current_row, current_col);
            }
            
            current_col += lexeme.value.size();
            
            result.push_back(lexeme);
        }
    }
    
    lexeme.lexeme_type = lexemeType::FINISH;
    lexeme.value = "finish lexeme";
    lexeme.debug_info.row = current_row;
    lexeme.debug_info.col = current_col;
    result.push_back(lexeme);
    
    return result;
}
