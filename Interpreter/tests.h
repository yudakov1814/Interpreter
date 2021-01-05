#pragma once
#include "my_interpreter.h"

bool operator==(const lexeme lhs, const lexeme rhs);
bool LexicalAnalyzerSimpleTest();
bool LexicalAnalyzerHardTest();
bool RunLexicalAnalyzerTests();

bool RunInterpreterOPSTests();

bool VarArrTest();
bool ReadWriteTest();
bool WhileTest();
bool IfTest();
bool ExpressionTest();
bool SortTest();
bool RunMyInterpreterTests();

void RunTests();
