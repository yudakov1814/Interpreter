#pragma once
#include <map>
#include <stack>
#include <vector>
#include <string>
#include "lexical_analyzer.h"
#include "interpret_exception.h"

enum class typeOPS {
    VARIABLE, // variable
    NUMBER, // number
    OPERATION, // operation
    ERROR, // error type
};

enum class operationOPS {
    READ, // read
    WRITE, // write
    PLUS, // +
    MINUS, // -
    MULTIPLY, // *
    DIVIDE, // /
    LESS, // <
    ASSIGN, // =
    MORE, // >
    EQUAL, // ==
    LESS_OR_EQUAL, // <=
    MORE_OR_EQUAL, // >=
    NOT_EQUAL, // !=
    J, // just jump
    JF, // jump if false
    I, // index
    ERROR // error operation
};

enum class opsMachineState {
    P, // → intIP | arrayAP | aH = E; Q | read(aH); Q | write(E); Q | if (C) { SQ }KZQ | while (C) { SQ }Q
    I, // → aM
    M, // → ,aM | ;
    A, // → a[k]N
    N, // → ,a[k]N | ;
    Q, // → aH = E; Q | read(aH); Q | write(aH); Q | if (C) { SQ }KZQ | while (C) { SQ }Q | λ
    S, // → aH = E; | read(aH); | write(aH); | if (C) { SQ }KZ | while (C) { SQ }
    H, // → [E] | λ
    C, // → (E)VUD | aHVUD | kVUD
    D, // → <EZ | >EZ | == EZ | ≤EZ | ≥EZ | !=EZ
    K, // → else { SQ } | λ
    E, // → (E)VU | aHVU | kVU
    U, // → + TU | -TU | λ
    T, // → (E)V | aHV | kV
    V, // → *FV | /FV | λ
    F, // → (E) | aH | k
    Z, // → λ
    ERROR // ошибочное состояние
};

enum class generatorTask
{
    EMPTY, // пустое действие
    VARIABLE, // записать идентификатор переменной
    NUM, // записать целое число без знака
    READ, // записать оператор чтения из потока
    WRITE, // записать оператор записи в поток
    PLUS, // записать +
    MINUS, // записать -
    MULTIPLY, // записать *
    DIVIDE, // записать /
    LESS, // записать <
    ASSIGN, // записать =
    MORE, // записать >
    EQUAL, // записать ==
    LESS_OR_EQUAL, // записать <=
    MORE_OR_EQUAL, // записать >=
    NOT_EQUAL, // записать !=
    I, // index
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

struct magazineItem
{
    bool is_terminal;
    lexemeType lexeme;
    opsMachineState state;
    
    magazineItem(lexemeType lexeme): is_terminal(true), lexeme(lexeme), state(opsMachineState::ERROR) {}
    magazineItem(opsMachineState state) : is_terminal(false), lexeme(lexemeType::ERROR), state(state) {}
};

struct itemOPS {
    typeOPS type = typeOPS::ERROR;
    operationOPS operation = operationOPS::ERROR;
    std::string var_name;
    long long int* var = nullptr;
    long long int num = 0;
    debugInfo debug_info;

    itemOPS(std::string name, const lexeme& l)
        : type(typeOPS::VARIABLE)
        , var_name(name)
        , debug_info(l.debug_info)
    {}

    itemOPS(operationOPS op, const lexeme& l)
        : type(typeOPS::OPERATION)
        , operation(op)
        , debug_info(l.debug_info)
    {}

    itemOPS(long long int num, const lexeme& l)
        : type(typeOPS::NUMBER)
        , num(num)
        , debug_info(l.debug_info)
    {}

    itemOPS(long long int num, debugInfo debug_info)
        : type(typeOPS::NUMBER)
        , num(num)
        , debug_info(debug_info)
    {}
};

struct OPS
{
    std::vector<itemOPS> items;
    std::map<std::string, long long int> vars;
    std::map<std::string, std::vector<long long int>> arrs;
};

enum class table {
    ARRAY,
    VARIABLE,
};

bool is_overflow(long long int);

void do_next_state(opsMachineState state, std::stack<magazineItem>& magazine,
                 std::stack<generatorTask>& generator, const lexeme& lexeme);
void do_generator_task(generatorTask task, OPS& ops, lexeme& lexeme,
                     std::stack<int>& marks, table& t, std::string&);
OPS generate_ops(std::vector<lexeme>&);

std::ostream& operator<<(std::ostream&, const typeOPS&);
std::ostream& operator<<(std::ostream&, const operationOPS&);
std::ostream& operator<<(std::ostream&, const generatorTask&);
std::ostream& operator<<(std::ostream&, const OPS& ops);
