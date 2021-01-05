#include <sstream>
#include "my_interpreter.h"
#include "interpret_exception.h"

using namespace std;

MyInterpreter::MyInterpreter(istream& pr, istream& in, ostream& out)
: program(pr)
, input_stream(in)
, output_stream(out)
{}

void MyInterpreter::run() {
    string s(istreambuf_iterator<char>(program), {});
    stringstream program_for_debug_view(s);
    stringstream program_for_run(s);
    init_debug_view(program_for_debug_view);
    bool was_exception = false;

    try
    {
        lexemes = analyze_text(program_for_run);
    }
    catch (const MyInterpretException& my_ex)
    {
        was_exception = true;
        cerr << "Lexical analyzer exception\n";
        print_exception(my_ex.what(), my_ex.debug_info);
    }
    catch (const std::exception& ex)
    {
        was_exception = true;
        cerr << "Unknown lexical analyzer exception\n";
        cerr << ex.what();
    }

    if (was_exception == false) {
        try
        {
            ops = generate_ops(lexemes);
        }
        catch (const MyInterpretException& my_ex)
        {
            was_exception = true;
            cerr << "Generator exception\n";
            print_exception(my_ex.what(), my_ex.debug_info);
        }
        catch (const std::exception& ex)
        {
            was_exception = true;
            cerr << "Unknown generator exception\n";
            cerr << ex.what();
        }
    }

    if (was_exception == false) {
        try
        {
            interpret_ops(ops, input_stream, output_stream);
        }
        catch (const MyInterpretException& my_ex)
        {
            was_exception = true;
            cerr << "Interpretator exception\n";
            print_exception(my_ex.what(), my_ex.debug_info);
        }
        catch (const std::exception& ex)
        {
            was_exception = true;
            cerr << "Unknown interpretator exception\n";
            cerr << ex.what();
        }
    }
}

void MyInterpreter::print_exception(const string& msg, debugInfo debugInfo) {
    int row = debugInfo.row - 1;
    int col = debugInfo.col;
    for (int i = -2; i <= 2; ++i) {
        if (0 <= row + i && row + i < debug_view.size()) {
            cerr << row + i + 1 << ": " << debug_view[row + i] << '\n';
        }
        if (i == 0) {
            cerr << string(col + 1, ' ') << "/|\\\n";
            cerr << string(col + 2, ' ') << "|\n";
            cerr << string(col + 2, ' ') << msg << ", (" << row + 1 << ", " << col << ")\n";;
        }
    }
}

void MyInterpreter::init_debug_view(istream& program) {
    string line;
    while(getline(program, line)) {
        debug_view.push_back(line);
    }
    debug_view.push_back("");
}
