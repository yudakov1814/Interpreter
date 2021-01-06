#pragma once
#include <unordered_map>
#include <stack>
#include <vector>
#include <string>
#include "analyzer.h"

using namespace std;

enum class ops_type {
    VARIABLE,
    NUMBER,
    OPERATION,
    ERROR
};

enum class ops_operation {
    READ,
    WRITE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LESS, 
    ASSIGN,
    MORE,
    EQUAL,
    LESS_OR_EQUAL,
    MORE_OR_EQUAL,
    NOT_EQUAL,
    J, // just jump
    JF, // jump if false
    I, // index
    ERROR
};

enum class ops_state {
    S, // → intIP | arrayAP | aH = E; Q | read(aH); Q | write(E); Q | if (C) { SQ }KZQ | while (C) { SQ }Q
    Q, // → aH = E; Q | read(aH); Q | write(E); Q | if (C) { SQ }KZQ | while (C) { SQ }Q | λ
    A, // → aH = E; | read(aH); | write(E); | if (C) { SQ }KZ | while (C) { SQ }
    I, // → aM
    M, // → ,aM | ;
    P, // → a[k]N
    N, // → ,a[k]N | ;
    H, // → [E] | λ
    C, // → (E)VUL | aHVUL | kVUL
    L, // → <EZ | >EZ | == EZ | ≤EZ | ≥EZ | !=EZ
    K, // → else { SQ } | λ
    E, // → (E)VU | aHVU | kVU
    U, // → + TU | -TU | λ
    T, // → (E)V | aHV | kV
    V, // → *FV | /FV | λ
    F, // → (E) | aH | k
    Z, // → λ
    ERROR // ошибочное состояние
};

enum class generator_task
{
    EMPTY,
    VARIABLE,
    NUM,
    READ,
    WRITE,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LESS,
    ASSIGN,
    MORE,
    EQUAL,
    LESS_OR_EQUAL,
    MORE_OR_EQUAL,
    NOT_EQUAL,
    I,
    TASK1, // use with IF and WHILE
    TASK2, // use with ELSE
    TASK3, // use with IF
    TASK4, // use with WHILE
    TASK5, // use with WHILE
    TASK6, // use with INT
    TASK7, // use with ARRAY
    TASK8, // use with VARS
    TASK9, // use with VARS
};

struct magazine_item
{
    bool is_terminal;
    lexemeType lexeme;
    ops_state state;

    magazine_item(lexemeType lexeme) : is_terminal(true), lexeme(lexeme), state(ops_state::ERROR) {}
    magazine_item(ops_state state) : is_terminal(false), lexeme(lexemeType::ERROR), state(state) {}
};

struct ops_item {
    ops_type type = ops_type::ERROR;
    ops_operation operation = ops_operation::ERROR;
    string var_name;
    int index = 0;
    int num = 0;
    int line = -1;
    int pos = -1;

    ops_item(string name, const lexeme& l)
    {
        type = ops_type::VARIABLE;
        var_name = name;
        line = l.line;
        pos = l.pos;
    }

    ops_item(ops_operation op, const lexeme& l)
    {
        type = ops_type::OPERATION;
        operation = op;
        line = l.line;
        pos = l.pos;
    }

    ops_item(int number, const lexeme& l)
    {
        type = ops_type::NUMBER;
        num = number;
        line = l.line;
        pos = l.pos;
    }

    ops_item(int number, int l, int p)
    {
        type = ops_type::NUMBER;
        num = number;
        line = l;
        pos = p;
    }
};

struct OPS
{
    vector<ops_item> items;
    unordered_map<string, long long int> vars;
    unordered_map<string, vector<long long int>> arrs;
};

enum class table {
    ARRAY,
    VARIABLE,
};

void next_state(ops_state state, stack<magazine_item>& magazine, stack<generator_task>& generator, const lexeme& lexeme);
void run_generator_task(generator_task task, OPS& ops, lexeme& lexeme, stack<int>& marks, table& t, string&);
OPS generate(vector<lexeme>&);