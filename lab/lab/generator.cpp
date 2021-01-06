#include <stdexcept>
#include "generator.h"

using namespace std;

void next_state(ops_state state, stack<magazine_item>& magazine, stack<generator_task>& generator, const lexeme& lexeme) {
    switch (state)
    {
    case ops_state::S:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::INT:
        {
            magazine.emplace(ops_state::S);
            magazine.emplace(ops_state::I);
            magazine.emplace(lexemeType::INT);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK6);
            break;
        }
        case lexemeType::ARRAY:
        {
            magazine.emplace(ops_state::S);
            magazine.emplace(ops_state::P);
            magazine.emplace(lexemeType::ARRAY);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK7);
            break;
        }
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::ASSIGN);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::ASSIGN);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::READ:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::READ);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::READ);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::WRITE:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::WRITE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::WRITE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::IF:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::K);
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::C);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::IF);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK3);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK1);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::WHILE:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::C);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::WHILE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK5);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK1);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK4);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::I:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::M);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK8);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::M:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::COMMA:
        {
            magazine.emplace(ops_state::M);
            magazine.emplace(lexemeType::VARIABLE);
            magazine.emplace(lexemeType::COMMA);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK8);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::SEMICOLON:
        {
            magazine.emplace(lexemeType::SEMICOLON);

            generator.emplace(generator_task::EMPTY);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::P:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::N);
            magazine.emplace(lexemeType::RIGHT_SQUARE_BRACKET);
            magazine.emplace(lexemeType::NUMBER);
            magazine.emplace(lexemeType::LEFT_SQUARE_BRACKET);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK9);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK8);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::N:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::COMMA:
        {
            magazine.emplace(ops_state::N);
            magazine.emplace(lexemeType::RIGHT_SQUARE_BRACKET);
            magazine.emplace(lexemeType::NUMBER);
            magazine.emplace(lexemeType::LEFT_SQUARE_BRACKET);
            magazine.emplace(lexemeType::VARIABLE);
            magazine.emplace(lexemeType::COMMA);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK9);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK8);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::SEMICOLON:
        {
            magazine.emplace(lexemeType::SEMICOLON);

            generator.emplace(generator_task::EMPTY);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::Q:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::ASSIGN);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::ASSIGN);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::READ:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::READ);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::READ);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::WRITE:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::WRITE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::WRITE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::IF:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::K);
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::C);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::IF);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK3);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK1);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::WHILE:
        {
            magazine.emplace(ops_state::Q);
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::C);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::WHILE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK5);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK1);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK4);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case ops_state::A:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::VARIABLE:
        {
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::ASSIGN);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::ASSIGN);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::READ:
        {
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::READ);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::READ);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::WRITE:
        {
            magazine.emplace(lexemeType::SEMICOLON);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::WRITE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::WRITE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::IF:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::K);
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::C);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::IF);

            generator.emplace(generator_task::TASK3);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK1);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::WHILE:
        {
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::C);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);
            magazine.emplace(lexemeType::WHILE);

            generator.emplace(generator_task::TASK5);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK1);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK4);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::H:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::LEFT_SQUARE_BRACKET:
        {
            magazine.emplace(lexemeType::RIGHT_SQUARE_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_SQUARE_BRACKET);

            generator.emplace(generator_task::I);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case ops_state::C:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::LEFT_ROUND_BRACKET:
        {
            magazine.emplace(ops_state::L);
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::V);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::L);
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::V);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::NUMBER:
        {
            magazine.emplace(ops_state::L);
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::V);
            magazine.emplace(lexemeType::NUMBER);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::NUM);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::L:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::LESS:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LESS);

            generator.emplace(generator_task::LESS);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::MORE:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::MORE);

            generator.emplace(generator_task::MORE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::EQUAL:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::EQUAL);

            generator.emplace(generator_task::EQUAL);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::LESS_OR_EQUAL:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LESS_OR_EQUAL);

            generator.emplace(generator_task::LESS_OR_EQUAL);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::MORE_OR_EQUAL:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::MORE_OR_EQUAL);

            generator.emplace(generator_task::MORE_OR_EQUAL);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::NOT_EQUAL:
        {
            magazine.emplace(ops_state::Z);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::NOT_EQUAL);

            generator.emplace(generator_task::NOT_EQUAL);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::K:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::ELSE:
        {
            magazine.emplace(lexemeType::RIGHT_BRACE);
            magazine.emplace(ops_state::Q);
            magazine.emplace(ops_state::A);
            magazine.emplace(lexemeType::LEFT_BRACE);
            magazine.emplace(lexemeType::ELSE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::TASK2);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case ops_state::E:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::LEFT_ROUND_BRACKET:
        {
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::V);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::V);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::NUMBER:
        {
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::V);
            magazine.emplace(lexemeType::NUMBER);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::NUM);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::U:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::PLUS:
        {
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::T);
            magazine.emplace(lexemeType::PLUS);

            generator.emplace(generator_task::PLUS);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::MINUS:
        {
            magazine.emplace(ops_state::U);
            magazine.emplace(ops_state::T);
            magazine.emplace(lexemeType::MINUS);

            generator.emplace(generator_task::MINUS);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case ops_state::T:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::LEFT_ROUND_BRACKET:
        {
            magazine.emplace(ops_state::V);
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::V);
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::NUMBER:
        {
            magazine.emplace(ops_state::V);
            magazine.emplace(lexemeType::NUMBER);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::NUM);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::V:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::MULTIPLY:
        {
            magazine.emplace(ops_state::V);
            magazine.emplace(ops_state::F);
            magazine.emplace(lexemeType::MULTIPLY);

            generator.emplace(generator_task::MULTIPLY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::DIVIDE:
        {
            magazine.emplace(ops_state::V);
            magazine.emplace(ops_state::F);
            magazine.emplace(lexemeType::DIVIDE);

            generator.emplace(generator_task::DIVIDE);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case ops_state::F:
    {
        switch (lexeme.lexeme_type)
        {
        case lexemeType::LEFT_ROUND_BRACKET:
        {
            magazine.emplace(lexemeType::RIGHT_ROUND_BRACKET);
            magazine.emplace(ops_state::E);
            magazine.emplace(lexemeType::LEFT_ROUND_BRACKET);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::EMPTY);
            break;
        }
        case lexemeType::VARIABLE:
        {
            magazine.emplace(ops_state::H);
            magazine.emplace(lexemeType::VARIABLE);

            generator.emplace(generator_task::EMPTY);
            generator.emplace(generator_task::VARIABLE);
            break;
        }
        case lexemeType::NUMBER:
        {
            magazine.emplace(lexemeType::NUMBER);

            generator.emplace(generator_task::NUM);
            break;
        }
        default:
        {
            string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }
        }
        break;
    }
    case ops_state::Z:
    {
        break;
    }
    case ops_state::ERROR:
    default:
        string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
        throw runtime_error(msg);
    }
}

void run_generator_task(generator_task task, OPS& ops, lexeme& lexeme,
    stack<int>& marks, table& t, string& last_name) {
    switch (task)
    {
    case generator_task::EMPTY:
        break;
    case generator_task::VARIABLE:
        ops.items.emplace_back(lexeme.value, lexeme);
        break;
    case generator_task::NUM:
    {
        int num = stoi(lexeme.value);
        ops.items.emplace_back(num, lexeme);
        break;
    }
    case generator_task::READ:
        ops.items.emplace_back(ops_operation::READ, lexeme);
        break;
    case generator_task::WRITE:
        ops.items.emplace_back(ops_operation::WRITE, lexeme);
        break;
    case generator_task::PLUS:
        ops.items.emplace_back(ops_operation::PLUS, lexeme);
        break;
    case generator_task::MINUS:
        ops.items.emplace_back(ops_operation::MINUS, lexeme);
        break;
    case generator_task::MULTIPLY:
        ops.items.emplace_back(ops_operation::MULTIPLY, lexeme);
        break;
    case generator_task::DIVIDE:
        ops.items.emplace_back(ops_operation::DIVIDE, lexeme);
        break;
    case generator_task::LESS:
        ops.items.emplace_back(ops_operation::LESS, lexeme);
        break;
    case generator_task::ASSIGN:
        ops.items.emplace_back(ops_operation::ASSIGN, lexeme);
        break;
    case generator_task::MORE:
        ops.items.emplace_back(ops_operation::MORE, lexeme);
        break;
    case generator_task::EQUAL:
        ops.items.emplace_back(ops_operation::EQUAL, lexeme);
        break;
    case generator_task::LESS_OR_EQUAL:
        ops.items.emplace_back(ops_operation::LESS_OR_EQUAL, lexeme);
        break;
    case generator_task::MORE_OR_EQUAL:
        ops.items.emplace_back(ops_operation::MORE_OR_EQUAL, lexeme);
        break;
    case generator_task::NOT_EQUAL:
        ops.items.emplace_back(ops_operation::NOT_EQUAL, lexeme);
        break;
    case generator_task::I:
        ops.items.emplace_back(ops_operation::I, lexeme);
        break;
    case generator_task::TASK1:
    {
        marks.push(ops.items.size());
        ops.items.emplace_back(0, lexeme);
        ops.items.emplace_back(ops_operation::JF, lexeme);
        break;
    }
    case generator_task::TASK2:
    {
        int place = marks.top(); marks.pop();
        marks.push(ops.items.size());
        ops.items.emplace_back(0, lexeme);
        ops.items.emplace_back(ops_operation::J, lexeme);
        ops.items[place].num = ops.items.size();
        break;
    }
    case generator_task::TASK3:
    {
        int place = marks.top(); marks.pop();
        ops.items[place].num = ops.items.size();
        break;
    }
    case generator_task::TASK4:
    {
        marks.push(ops.items.size());
        break;
    }
    case generator_task::TASK5:
    {
        int place = marks.top(); marks.pop();
        ops.items.emplace_back(marks.top(), lexeme); marks.pop();
        ops.items.emplace_back(ops_operation::J, lexeme);
        ops.items[place].num = ops.items.size();
        break;
    }
    case generator_task::TASK6:
    {
        t = table::VARIABLE;
        break;
    }
    case generator_task::TASK7:
    {
        t = table::ARRAY;
        break;
    }
    case generator_task::TASK8:
    {
        string name = lexeme.value;

        if (ops.arrs.count(name) || ops.vars.count(name)) {
            string msg = "Redefine a variable; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
            throw runtime_error(msg);
        }

        if (t == table::VARIABLE) {
            ops.vars.insert({ name, 0 });
        }
        else {
            ops.arrs.insert({ name, vector<long long int>() });
            last_name = name;
        }

        break;
    }
    case generator_task::TASK9:
    {
        int size = stoi(lexeme.value);
        ops.arrs[last_name].resize(size);
        break;
    }
    default: {
        string msg = "Generator error; line = " + to_string(lexeme.line) + ", pos = " + to_string(lexeme.pos);
        throw runtime_error(msg);
    }
    }
}

OPS generate(vector<lexeme>& input) {
    // create variables 
    stack<magazine_item> magazine;
    stack<generator_task> generator_ops;
    stack<int> marks;
    string last_name;
    table t;
    OPS result;

    // init variables
    magazine.emplace(ops_state::S);
    generator_ops.push(generator_task::EMPTY);
    t = table::VARIABLE;
    auto current_lexeme = input.begin();

    for (; !generator_ops.empty() && !magazine.empty();)
    {
        // do generator task 
        run_generator_task(generator_ops.top(), result, *current_lexeme, marks, t, last_name);
        generator_ops.pop();

        // do next state or read lexeme
        magazine_item current_magazine_item = magazine.top(); magazine.pop();
        if (current_magazine_item.is_terminal) {

            if (current_lexeme->lexeme_type == lexemeType::FINISH) {
                string msg = "Generator error; All lexemes are read, BUT magazine is not empty; line = "
                    + to_string(current_lexeme->line) + ", pos = " + to_string(current_lexeme->pos);
                throw runtime_error(msg);
            }

            // read lexeme
            if (current_magazine_item.lexeme == current_lexeme->lexeme_type) {
                ++current_lexeme;
                continue;
            }
            else {
                string msg = "Generator error; Unexpected lexeme; line = "
                    + to_string(current_lexeme->line) + ", pos = " + to_string(current_lexeme->pos);
                throw runtime_error(msg);
            }
        }
        else {
            // do next state
            next_state(current_magazine_item.state, magazine, generator_ops, *current_lexeme);
        }
    }

    if (current_lexeme->lexeme_type != lexemeType::FINISH) {
        string msg = "There are unrecognized lexemes; line = "
            + to_string(current_lexeme->line) + ", pos = " + to_string(current_lexeme->pos);
        throw runtime_error(msg);
    }

    return result;
}
