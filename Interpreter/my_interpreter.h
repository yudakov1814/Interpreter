#pragma once
#include "lexical_analyzer.h"
#include "generator_ops.h"
#include "interpreter_ops.h"

class MyInterpreter
{
public:
    MyInterpreter(std::istream&, std::istream&, std::ostream&);
    void run();
private:
    void init_debug_view(std::istream&);
    void print_exception(const std::string&, debugInfo);

    std::istream& program;
    std::istream& input_stream;
    std::ostream& output_stream;
    std::vector<lexeme> lexemes;
    std::vector<std::string> debug_view;
    OPS ops;
};
