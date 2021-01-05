#include <sstream>
#include <algorithm>
#include "tests.h"

using namespace std;

bool operator==(const lexeme lhs, const lexeme rhs) {
    return lhs.lexeme_type == rhs.lexeme_type &&
        lhs.value == rhs.value;
}

bool LexicalAnalyzerSimpleTest() {
    stringstream ss;
    ss << "int i, j;" << endl;
    ss << "array arr[5];" << endl;
    ss << "i = 1;" << endl;

    vector<lexeme> ans = {
        {lexemeType::INT, "int", 0, 0},
        {lexemeType::VARIABLE, "i", 0, 0},
        {lexemeType::COMMA, ",", 0, 0},
        {lexemeType::VARIABLE, "j", 0, 0},
        {lexemeType::SEMICOLON, ";", 0, 0},
        {lexemeType::ARRAY, "array", 0, 0},
        {lexemeType::VARIABLE, "arr", 0, 0},
        {lexemeType::LEFT_SQUARE_BRACKET, "[", 0, 0},
        {lexemeType::NUMBER, "5", 0, 0},
        {lexemeType::RIGHT_SQUARE_BRACKET, "]", 0, 0},
        {lexemeType::SEMICOLON, ";", 0, 0},
        {lexemeType::VARIABLE, "i", 0, 0},
        {lexemeType::ASSIGN, "=", 0, 0},
        {lexemeType::NUMBER, "1", 0, 0},
        {lexemeType::SEMICOLON, ";", 0, 0},
        {lexemeType::FINISH, "finish lexeme", 0, 0},
    };
    
    try {
        vector<lexeme> result = analyze_text(ss);
        return result == ans;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
}

bool LexicalAnalyzerHardTest() {
    stringstream ss;
    vector<lexeme> ans;

    for (int i = 0; i < 10'000; ++i) {
        switch (rand() % 30)
        {
        case 0:
            ss << "varname ";
            ans.emplace_back(lexeme{ lexemeType::VARIABLE, "varname" });
            break;
        case 1:
            ss << "123 ";
            ans.emplace_back(lexeme{ lexemeType::NUMBER, "123" });
            break;
        case 2:
            ss << "int ";
            ans.emplace_back(lexeme{ lexemeType::INT, "int" });
            break;
        case 3:
            ss << "array ";
            ans.emplace_back(lexeme{ lexemeType::ARRAY, "array" });
        case 4:
            ss << "if ";
            ans.emplace_back(lexeme{ lexemeType::IF, "if" });
        case 6:
            ss << "else ";
            ans.emplace_back(lexeme{ lexemeType::ELSE, "else" });
            break;
        case 7:
            ss << "while ";
            ans.emplace_back(lexeme{ lexemeType::WHILE, "while" });
            break;
        case 8:
            ss << "read ";
            ans.emplace_back(lexeme{ lexemeType::READ, "read" });
            break;
        case 9:
            ss << "write ";
            ans.emplace_back(lexeme{ lexemeType::WRITE, "write" });
            break;
        case 10:
            ss << '{';
            ans.emplace_back(lexeme{ lexemeType::LEFT_BRACE, "{" });
            break;
        case 11:
            ss << '}';
            ans.emplace_back(lexeme{ lexemeType::RIGHT_BRACE, "}" });
            break;
        case 12:
            ss << '[';
            ans.emplace_back(lexeme{ lexemeType::LEFT_SQUARE_BRACKET, "[" });
            break;
        case 13:
            ss << ']';
            ans.emplace_back(lexeme{ lexemeType::RIGHT_SQUARE_BRACKET, "]" });
            break;
        case 14:
            ss << '(';
            ans.emplace_back(lexeme{ lexemeType::LEFT_ROUND_BRACKET, "(" });
            break;
        case 15:
            ss << ')';
            ans.emplace_back(lexeme{ lexemeType::RIGHT_ROUND_BRACKET, ")" });
            break;
        case 16:
            ss << '+';
            ans.emplace_back(lexeme{ lexemeType::PLUS, "+" });
            break;
        case 17:
            ss << '-';
            ans.emplace_back(lexeme{ lexemeType::MINUS, "-" });
            break;
        case 18:
            ss << '*';
            ans.emplace_back(lexeme{ lexemeType::MULTIPLY, "*" });
            break;
        case 19:
            ss << '/';
            ans.emplace_back(lexeme{ lexemeType::DIVIDE, "/" });
            break;
        case 20:
            ss << ';';
            ans.emplace_back(lexeme{ lexemeType::SEMICOLON, ";" });
            break;
        case 21:
            ss << ',';
            ans.emplace_back(lexeme{ lexemeType::COMMA, "," });
            break;
        case 22:
            ss << "< ";
            ans.emplace_back(lexeme{ lexemeType::LESS, "<" });
            break;
        case 23:
            ss << "= ";
            ans.emplace_back(lexeme{ lexemeType::ASSIGN, "=" });
            break;
        case 24:
            ss << "> ";
            ans.emplace_back(lexeme{ lexemeType::MORE, ">" });
            break;
        case 25:
            ss << "== ";
            ans.emplace_back(lexeme{ lexemeType::EQUAL, "==" });
            break;
        case 26:
            ss << "<= ";
            ans.emplace_back(lexeme{ lexemeType::LESS_OR_EQUAL, "<=" });
            break;
        case 27:
            ss << ">= ";
            ans.emplace_back(lexeme{ lexemeType::MORE_OR_EQUAL, ">=" });
            break;
        case 28:
            ss << "!= ";
            ans.emplace_back(lexeme{ lexemeType::NOT_EQUAL, "!=" });
            break;
        default:
            ss << ' ';
            break;
        }
    }

    try {
        vector<lexeme> result = analyze_text(ss);
        ans.push_back(lexeme{ lexemeType::FINISH, "finish lexeme" });
        return result == ans;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
}

bool RunLexicalAnalyzerTests() {
    bool is_ok = true;
    if (LexicalAnalyzerSimpleTest()) {
        cout << "simple test: OK\n";
    } else {
        is_ok = false;
        cout << "simple test: WRONG\n";
    }
    if (LexicalAnalyzerHardTest()) {
        cout << "hard test: OK\n";
    } else {
        is_ok = false;
        cout << "hard test: WRONG\n";
    }
    return is_ok;
}

bool RunGeneratorOPSTests() {
    bool is_ok = true;
    if (LexicalAnalyzerSimpleTest()) {
        cout << "simple test: OK\n";
    } else {
        is_ok = false;
        cout << "simple test: WRONG\n";
    }
    if (LexicalAnalyzerHardTest()) {
        cout << "hard test: OK\n";
    } else {
        is_ok = false;
        cout << "hard test: WRONG\n";
    }
    return is_ok;
}

bool RunInterpreterOPSTests() {
    return true;
}

bool VarArrTest() {
    stringstream pr;
    stringstream in;
    stringstream out;
    
    pr << "int a; array b[3];";
    pr << "int g, c; array kk[22], e[11];";
    pr << "g = 1;";
    
    try {
        MyInterpreter m(pr, in, out);
        m.run();
        int write_num;
        out >> write_num;
        return true;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
    return true;
}

bool ReadWriteTest() {
    stringstream pr;
    stringstream in;
    stringstream out;
    int num = 10;
    
    pr << "int a;";
    pr << "read(a);";
    pr << "write(a);";
    
    in << num;
    
    try {
        MyInterpreter m(pr, in, out);
        m.run();
        int write_num;
        out >> write_num;
        return num == write_num;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
    return true;
}

bool WhileTest() {
    stringstream pr;
    stringstream in;
    stringstream out;
    
    pr << "int a; array arr[10];     \n";
    pr << "a = 0;                    \n";
    pr << "while (a < 10)            \n";
    pr << "{                         \n";
    pr << "    arr[a] = a;           \n";
    pr << "    a = a + 1;            \n";
    pr << "}                         \n";
    pr << "if (a > 5)                \n";
    pr << "{                         \n";
    pr << "    a = 0;                \n";
    pr << "}                         \n";
    pr << "while (a < 10)            \n";
    pr << "{                         \n";
    pr << "    write(arr[a]);        \n";
    pr << "    a = a + 1;            \n";
    pr << "}                         \n";
    
    MyInterpreter m(pr, in, out);
    
    try {
        vector<int> ans(10);
        vector<int> result(10);
        
        for(int i = 0; i < 10; ++i) {
            ans[i] = i;
        }
        m.run();
        for(int i = 0; i < 10; ++i) {
            out >> result[i];
        }
        return ans == result;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
}

bool IfTest() {
    stringstream pr;
    stringstream in;
    stringstream out;
    
    pr << "int a, b, c;";
    pr << "a = 5;";
    pr << "b = 3;";
    pr << "c = 2;";
    pr << "if(a < c){a = c;} else {";
    pr << "if (b >= c) {a = c;} else {c = b;} b = c;";
    pr << "}";
    pr << "write(a);";
    pr << "write(b);";
    pr << "write(c);";
    
    MyInterpreter m(pr, in, out);
    
    try {
        m.run();
        int a, b, c;
        out >> a >> b >> c;
        return a == 2 && b == 2 && c == 2;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
}

bool ExpressionTest() {
    stringstream pr;
    stringstream in;
    stringstream out;
    
    pr << "array arr[10]; int a, b;";
    pr << "a = 17; b = 6;";
    pr << "arr[0] = (10 / a + b) - 3 * 2 + 1;";
    pr << "arr[1] = b - (a * 2 - b) * 33;";
    pr << "arr[2] = a * b - 2 * (22 / 11 + b);";
    pr << "arr[3] = (arr[2] - 2) * (b - 3);";
    pr << "arr[4] = ((((a - 2) - 2) - b) / 2);";
    pr << "arr[5] = (2 - (15345 / (b * (a + 2))));";
    pr << "arr[6] = 33 * a / b + 2 - 3 * b / a - b;";
    pr << "arr[7] = b + (a + b) * (a - b) - a;";
    pr << "arr[8] = 23 + arr[1] - (arr[b] * 22) / (arr[0]);";
    pr << "arr[9] = 1 + 2 / 3 * 5 - 22;";
    pr << "a = 0;";
    pr << "while (a < 10)";
    pr << "{";
    pr << "    write(arr[a]);";
    pr << "    a = a + 1;";
    pr << "}";
    
    MyInterpreter m(pr, in, out);
    
    try {
        int a = 17, b = 6;
        vector<int> arr(10);
        arr[0] = (10 / a + b) - 3 * 2 + 1;
        arr[1] = b - (a * 2 - b) * 33;
        arr[2] = a * b - 2 * (22 / 11 + b);
        arr[3] = (arr[2] - 2) * (b - 3);
        arr[4] = ((((a - 2) - 2) - b) / 2);
        arr[5] = (2 - (15345 / (b * (a + 2))));
        arr[6] = 33 * a / b + 2 - 3 * b / a - b;
        arr[7] = b + (a + b) * (a - b) - a;
        arr[8] = 23 + arr[1] - (arr[b] * 22) / (arr[0]);
        arr[9] = 1 + 2 / 3 * 5 - 22;
        vector<int> result(10);
        m.run();
        
        for (int i = 0; i < 10; ++i) {
            out >> result[i];
        }
        return arr == result;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
}

bool SortTest() {
    stringstream pr;
    stringstream in;
    stringstream out;
    
    int n = 100;
    vector<int> ans(n);
    vector<int> result(n);
    
    in << n << endl;
    
    for (int i = 0, num; i < n; ++i) {
        num = rand();
        in << num << " ";
        ans[i] = num;
    }
    
    sort(begin(ans), end(ans));
    
    pr << "   array arr[100];                    " << endl;
    pr << "   int n, i, j, temp;                 " << endl;
    pr << "                                      " << endl;
    pr << "   read(n);                           " << endl;
    pr << "   i = 0;                             " << endl;
    pr << "   while(i < n) {                     " << endl;
    pr << "      read(arr[i]);                   " << endl;
    pr << "      i = i + 1;                      " << endl;
    pr << "   }                                  " << endl;
    pr << "                                      " << endl;
    pr << "   i = 0;                             " << endl;
    pr << "   while (i < n - 1) {                " << endl;
    pr << "      j = 0;                          " << endl;
    pr << "      while (j < n - i - 1) {         " << endl;
    pr << "         if (arr[j] > arr[j + 1]) {   " << endl;
    pr << "            temp = arr[j];            " << endl;
    pr << "            arr[j] = arr[j + 1];      " << endl;
    pr << "            arr[j + 1] = temp;        " << endl;
    pr << "         }                            " << endl;
    pr << "         j = j + 1;                   " << endl;
    pr << "      }                               " << endl;
    pr << "      i = i + 1;                      " << endl;
    pr << "   }                                  " << endl;
    pr << "                                      " << endl;
    pr << "   i = 0;                             " << endl;
    pr << "   while (i < n) {                    " << endl;
    pr << "      write(arr[i]);                  " << endl;
    pr << "      i = i + 1;                      " << endl;
    pr << "   }                                  " << endl;
    
    MyInterpreter m(pr, in, out);
    
    
    try {
        m.run();
        for (int i = 0; i < n; ++i) {
            out >> result[i];
        }
        return ans == result;
    } catch (exception& ex) {
        cout << ex.what();
        return false;
    }
}


bool RunMyInterpreterTests() {
    bool is_ok = true;
    if (VarArrTest()) {
        cout << "variable and array test: OK\n";
    } else {
        is_ok = false;
        cout << "variable and array test: WRONG\n";
    }
    if (ReadWriteTest()) {
        cout << "read and write test: OK\n";
    } else {
        is_ok = false;
        cout << "read and write test: WRONG\n";
    }
    if (IfTest()) {
        cout << "if test: OK\n";
    } else {
        is_ok = false;
        cout << "if test: WRONG\n";
    }
    if (WhileTest()) {
        cout << "while test: OK\n";
    } else {
        is_ok = false;
        cout << "while test: WRONG\n";
    }
    if (ExpressionTest()) {
        cout << "expression test: OK\n";
    } else {
        is_ok = false;
        cout << "expression test: WRONG\n";
    }
    if (SortTest()) {
        cout << "sort test: OK\n";
    } else {
        is_ok = false;
        cout << "sort test: WRONG\n";
    }
    return is_ok;
}

void RunTests() {
    cout << "lexical analyzer tests is running...\n";
    if (RunLexicalAnalyzerTests()) {
        cout << "general verdict: OK\n\n" ;
    } else {
        cout << "general verdict: WRONG\n\n" ;
    }
    
    cout << "interpreter tests is running...\n";
    if (RunMyInterpreterTests()) {
        cout << "general verdict: OK\n\n" ;
    } else {
        cout << "general verdict: WRONG\n\n" ;
    }
}
