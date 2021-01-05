#include <iostream>
#include <sstream>
#include <fstream>
#include "my_interpreter.h"
#include "tests.h"

using namespace std;

int main() {
	srand(static_cast<unsigned>(time(0)));
    RunTests();
    cout << string(40, 205) << "\nTests were completed successfully\n" << string(40, 205) << '\n';
    
    string file_name = "pr.txt";
    ifstream pr(file_name);

    MyInterpreter m(pr, cin, cout);
    m.run();
    
	return 0;
}
