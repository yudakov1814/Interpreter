#include <sstream>
#include "generator_ops.h"
#include "interpret_exception.h"

using namespace std;

bool is_overflow(long long int i) {
    return i != static_cast<int>(i);
}

ostream& operator<<(ostream& out, const typeOPS& type) {
    switch (type)
    {
    case typeOPS::VARIABLE:
        out << "variable";
        break;
    case typeOPS::NUMBER:
        out << "number";
        break;
    case typeOPS::OPERATION:
        out << "operation";
        break;
    case typeOPS::ERROR:
        out << "error type";
        break;
    default:
        out << "unknown type";
        break;
    }

    return out;
}

ostream& operator<<(ostream& out, const operationOPS& op) {
    switch (op)
    {
    case operationOPS::READ:
        out << "r";
        break;
    case operationOPS::WRITE:
        out << "w";
        break;
    case operationOPS::PLUS:
        out << "+";
        break;
    case operationOPS::MINUS:
        out << "-";
        break;
    case operationOPS::MULTIPLY:
        out << "*";
        break;
    case operationOPS::DIVIDE:
        out << "/";
        break;
    case operationOPS::LESS:
        out << "<";
        break;
    case operationOPS::ASSIGN:
        out << "=";
        break;
    case operationOPS::MORE:
        out << ">";
        break;
    case operationOPS::EQUAL:
        out << "==";
        break;
    case operationOPS::LESS_OR_EQUAL:
        out << "<=";
        break;
    case operationOPS::MORE_OR_EQUAL:
        out << ">=";
        break;
    case operationOPS::NOT_EQUAL:
        out << "!=";
        break;
    case operationOPS::J:
        out << "j";
        break;
    case operationOPS::JF:
        out << "jf";
        break;
    case operationOPS::I:
        out << "i";
        break;
    case operationOPS::ERROR:
        out << "error operation";
        break;
    default:
        out << "unknown operation";
        break;
    }

    return out;
}

ostream& operator<<(ostream& out, const generatorTask& task) {
    switch (task)
    {
    case generatorTask::EMPTY:
        out << "epmty";
        break;
    case generatorTask::VARIABLE:
        out << "variable";
        break;
    case generatorTask::NUM:
        out << "number";
        break;
    case generatorTask::READ:
        out << "read";
        break;
    case generatorTask::WRITE:
        out << "write";
        break;
    case generatorTask::PLUS:
        out << "+";
        break;
    case generatorTask::MINUS:
        out << "-";
        break;
    case generatorTask::MULTIPLY:
        out << "*";
        break;
    case generatorTask::DIVIDE:
        out << "/";
        break;
    case generatorTask::LESS:
        out << "<";
        break;
    case generatorTask::ASSIGN:
        out << "=";
        break;
    case generatorTask::MORE:
        out << ">";
        break;
    case generatorTask::EQUAL:
        out << "==";
        break;
    case generatorTask::LESS_OR_EQUAL:
        out << "<=";
        break;
    case generatorTask::MORE_OR_EQUAL:
        out << ">=";
        break;
    case generatorTask::NOT_EQUAL:
        out << "!=";
        break;
    case generatorTask::I:
        out << "index";
        break;
    case generatorTask::TASK1:
        out << "task1";
        break;
    case generatorTask::TASK2:
        out << "task2";
        break;
    case generatorTask::TASK3:
        out << "task3";
        break;
    case generatorTask::TASK4:
        out << "task4";
        break;
    case generatorTask::TASK5:
        out << "task5";
        break;
    case generatorTask::TASK6:
        out << "task6";
        break;
    case generatorTask::TASK7:
        out << "task7";
        break;
    case generatorTask::TASK8:
        out << "task8";
        break;
    case generatorTask::TASK9:
        out << "task9";
        break;
    default:
        out << "unknown task";
        break;
    }

    return out;
}

void do_next_state(opsMachineState state, stack<magazineItem>& magazine, stack<generatorTask>& generator, const lexeme& lexeme) {
    switch (state)
    {
        case opsMachineState::P:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::INT:
                {
                    magazine.emplace(opsMachineState::P);
                    magazine.emplace(opsMachineState::I);
                    magazine.emplace(lexemeType::INT);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK6);
                    break;
                }
                case lexemeType::ARRAY:
                {
                    magazine.emplace(opsMachineState::P);
                    magazine.emplace(opsMachineState::A);
                    magazine.emplace(lexemeType::ARRAY);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK7);
                    break;
                }
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::ASSIGN);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::ASSIGN);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::READ:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::READ);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::READ);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::WRITE:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::WRITE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::WRITE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::IF:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::K);
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::C);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::IF);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK3);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK1);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::WHILE:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::C);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::WHILE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK5);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK1);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK4);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::INT << "', ";
                    ss << "'" << lexemeType::ARRAY << "', ";
                    ss << "'" << lexemeType::VARIABLE << "', ";
                    ss << "'" << lexemeType::READ << "', ";
                    ss << "'" << lexemeType::WRITE << "', ";
                    ss << "'" << lexemeType::IF << "', ";
                    ss << "'" << lexemeType::WHILE << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::I:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::M);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK8);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::VARIABLE << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::M:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::COMMA:
                {
                    magazine.emplace(opsMachineState::M);
                    magazine.emplace(lexemeType::VARIABLE);
                    magazine.emplace(lexemeType::COMMA);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK8);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::SEMICOLON:
                {
                    magazine.emplace(lexemeType::SEMICOLON);
                    
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::COMMA << "', ";
                    ss << "'" << lexemeType::ARRAY << "', ";
                    ss << "'" << lexemeType::SEMICOLON << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::A:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::N);
                    magazine.emplace(lexemeType::RIGHT_SQUARE_BRACKET);
                    magazine.emplace(lexemeType::NUMBER);
                    magazine.emplace(lexemeType::LEFT_SQUARE_BRACKET);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK9);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK8);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::VARIABLE << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::N:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::COMMA:
                {
                    magazine.emplace(opsMachineState::N);
                    magazine.emplace(lexemeType::RIGHT_SQUARE_BRACKET);
                    magazine.emplace(lexemeType::NUMBER);
                    magazine.emplace(lexemeType::LEFT_SQUARE_BRACKET);
                    magazine.emplace(lexemeType::VARIABLE);
                    magazine.emplace(lexemeType::COMMA);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK9);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK8);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::SEMICOLON:
                {
                    magazine.emplace(lexemeType::SEMICOLON);
                    
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::COMMA << "', ";
                    ss << "'" << lexemeType::SEMICOLON << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::Q:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::ASSIGN);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::ASSIGN);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::READ:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::READ);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::READ);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::WRITE:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::WRITE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::WRITE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::IF:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::K);
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::C);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::IF);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK3);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK1);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::WHILE:
                {
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::C);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::WHILE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK5);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK1);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK4);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case opsMachineState::S:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::ASSIGN);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::ASSIGN);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::READ:
                {
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::READ);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::READ);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::WRITE:
                {
                    magazine.emplace(lexemeType::SEMICOLON);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::WRITE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::WRITE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::IF:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::K);
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::C);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::IF);
                    
                    generator.emplace(generatorTask::TASK3);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK1);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::WHILE:
                {
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::C);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    magazine.emplace(lexemeType::WHILE);
                    
                    generator.emplace(generatorTask::TASK5);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK1);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK4);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::VARIABLE << "', ";
                    ss << "'" << lexemeType::READ << "', ";
                    ss << "'" << lexemeType::WRITE << "', ";
                    ss << "'" << lexemeType::IF << "', ";
                    ss << "'" << lexemeType::WHILE << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::H:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::LEFT_SQUARE_BRACKET:
                {
                    magazine.emplace(lexemeType::RIGHT_SQUARE_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_SQUARE_BRACKET);
                    
                    generator.emplace(generatorTask::I);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case opsMachineState::C:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::LEFT_ROUND_BRACKET:
                {
                    magazine.emplace(opsMachineState::D);
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::D);
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::NUMBER:
                {
                    magazine.emplace(opsMachineState::D);
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(lexemeType::NUMBER);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::NUM);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::LEFT_ROUND_BRACKET << "', ";
                    ss << "'" << lexemeType::VARIABLE << "', ";
                    ss << "'" << lexemeType::NUMBER << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::D:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::LESS:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LESS);
                    
                    generator.emplace(generatorTask::LESS);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::MORE:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::MORE);
                    
                    generator.emplace(generatorTask::MORE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::EQUAL:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::EQUAL);
                    
                    generator.emplace(generatorTask::EQUAL);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::LESS_OR_EQUAL:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LESS_OR_EQUAL);
                    
                    generator.emplace(generatorTask::LESS_OR_EQUAL);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::MORE_OR_EQUAL:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::MORE_OR_EQUAL);
                    
                    generator.emplace(generatorTask::MORE_OR_EQUAL);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::NOT_EQUAL:
                {
                    magazine.emplace(opsMachineState::Z);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::NOT_EQUAL);
                    
                    generator.emplace(generatorTask::NOT_EQUAL);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::LESS << "', ";
                    ss << "'" << lexemeType::MORE << "', ";
                    ss << "'" << lexemeType::EQUAL << "', ";
                    ss << "'" << lexemeType::LESS_OR_EQUAL << "', ";
                    ss << "'" << lexemeType::MORE_OR_EQUAL << "', ";
                    ss << "'" << lexemeType::NOT_EQUAL << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::K:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::ELSE:
                {
                    magazine.emplace(lexemeType::RIGHT_BRACE);
                    magazine.emplace(opsMachineState::Q);
                    magazine.emplace(opsMachineState::S);
                    magazine.emplace(lexemeType::LEFT_BRACE);
                    magazine.emplace(lexemeType::ELSE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::TASK2);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case opsMachineState::E:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::LEFT_ROUND_BRACKET:
                {
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::NUMBER:
                {
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(lexemeType::NUMBER);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::NUM);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::LEFT_ROUND_BRACKET << "', ";
                    ss << "'" << lexemeType::VARIABLE << "', ";
                    ss << "'" << lexemeType::NUMBER << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::U:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::PLUS:
                {
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::T);
                    magazine.emplace(lexemeType::PLUS);
                    
                    generator.emplace(generatorTask::PLUS);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::MINUS:
                {
                    magazine.emplace(opsMachineState::U);
                    magazine.emplace(opsMachineState::T);
                    magazine.emplace(lexemeType::MINUS);
                    
                    generator.emplace(generatorTask::MINUS);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case opsMachineState::T:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::LEFT_ROUND_BRACKET:
                {
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::NUMBER:
                {
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(lexemeType::NUMBER);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::NUM);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::LEFT_ROUND_BRACKET << "', ";
                    ss << "'" << lexemeType::VARIABLE << "', ";
                    ss << "'" << lexemeType::NUMBER << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::V:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::MULTIPLY:
                {
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(opsMachineState::F);
                    magazine.emplace(lexemeType::MULTIPLY);
                    
                    generator.emplace(generatorTask::MULTIPLY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::DIVIDE:
                {
                    magazine.emplace(opsMachineState::V);
                    magazine.emplace(opsMachineState::F);
                    magazine.emplace(lexemeType::DIVIDE);
                    
                    generator.emplace(generatorTask::DIVIDE);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case opsMachineState::F:
        {
            switch (lexeme.lexeme_type)
            {
                case lexemeType::LEFT_ROUND_BRACKET:
                {
                    magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
                    magazine.emplace(opsMachineState::E);
                    magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::EMPTY);
                    break;
                }
                case lexemeType::VARIABLE:
                {
                    magazine.emplace(opsMachineState::H);
                    magazine.emplace(lexemeType::VARIABLE);
                    
                    generator.emplace(generatorTask::EMPTY);
                    generator.emplace(generatorTask::VARIABLE);
                    break;
                }
                case lexemeType::NUMBER:
                {
                    magazine.emplace(lexemeType::NUMBER);
                    
                    generator.emplace(generatorTask::NUM);
                    break;
                }
                default:
                {
                    stringstream ss;
                    ss << lexeme.lexeme_type << " was found, BUT expected: ";
                    ss << "'" << lexemeType::LEFT_ROUND_BRACKET << "', ";
                    ss << "'" << lexemeType::VARIABLE << "', ";
                    ss << "'" << lexemeType::NUMBER << "'";
                    throw MyInterpretException(ss.str(), lexeme.debug_info);
                    break;
                }
            }
            break;
        }
        case opsMachineState::Z:
        {
            break;
        }
        case opsMachineState::ERROR:
        default:
            stringstream ss;
            ss << "error lexeme: " << lexeme.lexeme_type << endl;
            throw MyInterpretException(ss.str(), lexeme.debug_info);
            break;
    }
}

void do_generator_task(generatorTask task, OPS& ops, lexeme& lexeme,
                     stack<int>& marks, table& t, string& last_name) {
    switch (task)
    {
        case generatorTask::EMPTY:
            break;
        case generatorTask::VARIABLE:
            ops.items.emplace_back(lexeme.value, lexeme);
            break;
        case generatorTask::NUM:
        {
            long long int num = stoll(lexeme.value);
            if (is_overflow(num)) {
                stringstream ss;
                ss << "number overflow";
                throw MyInterpretException(ss.str(), lexeme.debug_info);
            }
            ops.items.emplace_back(num, lexeme);
            break;
        }
        case generatorTask::READ:
            ops.items.emplace_back(operationOPS::READ, lexeme);
            break;
        case generatorTask::WRITE:
            ops.items.emplace_back(operationOPS::WRITE, lexeme);
            break;
        case generatorTask::PLUS:
            ops.items.emplace_back(operationOPS::PLUS, lexeme);
            break;
        case generatorTask::MINUS:
            ops.items.emplace_back(operationOPS::MINUS, lexeme);
            break;
        case generatorTask::MULTIPLY:
            ops.items.emplace_back(operationOPS::MULTIPLY, lexeme);
            break;
        case generatorTask::DIVIDE:
            ops.items.emplace_back(operationOPS::DIVIDE, lexeme);
            break;
        case generatorTask::LESS:
            ops.items.emplace_back(operationOPS::LESS, lexeme);
            break;
        case generatorTask::ASSIGN:
            ops.items.emplace_back(operationOPS::ASSIGN, lexeme);
            break;
        case generatorTask::MORE:
            ops.items.emplace_back(operationOPS::MORE, lexeme);
            break;
        case generatorTask::EQUAL:
            ops.items.emplace_back(operationOPS::EQUAL, lexeme);
            break;
        case generatorTask::LESS_OR_EQUAL:
            ops.items.emplace_back(operationOPS::LESS_OR_EQUAL, lexeme);
            break;
        case generatorTask::MORE_OR_EQUAL:
            ops.items.emplace_back(operationOPS::MORE_OR_EQUAL, lexeme);
            break;
        case generatorTask::NOT_EQUAL:
            ops.items.emplace_back(operationOPS::NOT_EQUAL, lexeme);
            break;
        case generatorTask::I:
            ops.items.emplace_back(operationOPS::I, lexeme);
            break;
        case generatorTask::TASK1:
        {
            marks.push(static_cast<int>(ops.items.size()));
            ops.items.emplace_back(0, lexeme);
            ops.items.emplace_back(operationOPS::JF, lexeme);
            break;
        }
        case generatorTask::TASK2:
        {
            int place = marks.top(); marks.pop();
            marks.push(static_cast<int>(ops.items.size()));
            ops.items.emplace_back(0, lexeme);
            ops.items.emplace_back(operationOPS::J, lexeme);
            ops.items[place].num = static_cast<int>(ops.items.size());
            break;
        }
        case generatorTask::TASK3:
        {
            int place = marks.top(); marks.pop();
            ops.items[place].num = ops.items.size();
            break;
        }
        case generatorTask::TASK4:
        {
            marks.push(static_cast<int>(ops.items.size()));
            break;
        }
        case generatorTask::TASK5:
        {
            int place = marks.top(); marks.pop();
            ops.items.emplace_back(marks.top(), lexeme); marks.pop();
            ops.items.emplace_back(operationOPS::J, lexeme);
            ops.items[place].num = static_cast<int>(ops.items.size());
            break;
        }
        case generatorTask::TASK6:
        {
            t = table::VARIABLE;
            break;
        }
        case generatorTask::TASK7:
        {
            t = table::ARRAY;
            break;
        }
        case generatorTask::TASK8:
        {
            string name = lexeme.value;
            
            if (ops.arrs.count(name) || ops.vars.count(name)) {
                stringstream ss;
                ss << "redefinition variable: " << lexeme.value;
                throw MyInterpretException(ss.str(), lexeme.debug_info);
            }
            
            if (t == table::VARIABLE) {
                ops.vars.insert({name, 0});
            } else {
                ops.arrs.insert({name, vector<long long int>()});
                last_name = name;
            }
            
            break;
        }
        case generatorTask::TASK9:
        {
            long long int num = stoll(lexeme.value);
            if (is_overflow(num)) {
                stringstream ss;
                ss << "number overflow";
                throw MyInterpretException(ss.str(), lexeme.debug_info);
            }
            
            ops.arrs[last_name].resize(static_cast<int>(num));
            break;
        }
        default: {
            stringstream ss;
            ss << "unknown generator task: " << task;
            throw MyInterpretException(ss.str(), lexeme.debug_info);
            break;
        }
    }
}

OPS generate_ops(vector<lexeme>& input) {
    // create variables 
    stack<magazineItem> magazine;
    stack<generatorTask> generator_ops;
    stack<int> marks;
    string last_name;
    table t;
    OPS result;

    // init variables
    magazine.emplace(opsMachineState::P);
    generator_ops.push(generatorTask::EMPTY);
    t = table::VARIABLE;
    auto current_lexeme = input.begin();
    
    for (; !generator_ops.empty() && !magazine.empty() ;)
    {
        // do generator task 
        do_generator_task(generator_ops.top(), result, *current_lexeme, marks, t, last_name);
        generator_ops.pop();
        
        // do next state or read lexeme
        magazineItem current_magazine_item = magazine.top(); magazine.pop();
        if (current_magazine_item.is_terminal) {
            
            if (current_lexeme->lexeme_type == lexemeType::FINISH) {
                stringstream ss;
                ss << "all lexemes are read, BUT in magazine: " << current_magazine_item.lexeme;
                throw MyInterpretException(ss.str(), current_lexeme->debug_info);
            }
            
            // read lexeme
            if (current_magazine_item.lexeme == current_lexeme->lexeme_type) {
                ++current_lexeme;
                continue;
            }
            else {
                stringstream ss;
                ss << current_lexeme->lexeme_type << " was found, BUT expected: ";
                ss << current_magazine_item.lexeme;
                throw MyInterpretException(ss.str(), current_lexeme->debug_info);
            }
        }
        else {
            // do next state
            do_next_state(current_magazine_item.state, magazine, generator_ops, *current_lexeme);
        }
    }
    
    if (current_lexeme->lexeme_type != lexemeType::FINISH) {
        stringstream ss;
        ss << "list unrecognized lexemes:\n[";
        for (auto it = current_lexeme; it->lexeme_type != lexemeType::FINISH; ++it) {
            if (it != current_lexeme) {
                ss << ", ";
            }
            ss << *it;
        }
        ss << "]\n";
        throw MyInterpretException(ss.str(), current_lexeme->debug_info);
    }
    
    return result;
}
