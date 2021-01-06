#include <iostream>
#include <fstream>
#include "analyzer.h"
#include "generator.h"
#include "interpreter.h"

using namespace std;

int main() {
	string file_name = "program.txt";
	ifstream pr = ifstream(file_name);

	string program_text;
	getline(pr, program_text, '\0');

	try
	{
		auto lexemes = analyze(program_text);
		auto ops = generate(lexemes);
		interpret(ops);
	}
	catch (const exception& ex)
	{
		cerr << ex.what() << endl;
	}
	
	return 0;
}