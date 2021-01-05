#include <stack>
#include <sstream>
#include "interpreter_ops.h"
#include "interpret_exception.h"
using namespace std;

long long int get_num(itemOPS& ops) {
    if (ops.type == typeOPS::VARIABLE) {
        if (ops.var == nullptr) {
            stringstream ss;
            ss << "use [index] for arrays '" << ops.var_name << "'";
            throw MyInterpretException(ss.str(), ops.debug_info);
        }
        return *ops.var;
    }
    else if (ops.type == typeOPS::NUMBER) {
        return ops.num;
    }
    else {
        stringstream ss;
        ss << "'" << ops.type << "' was found, BUT expected: '" << typeOPS::VARIABLE << "' or '" << typeOPS::NUMBER << "'";
        throw MyInterpretException(ss.str(), ops.debug_info);
    }
}

void interpret_ops(OPS& ops, istream& in, ostream& out)
{
    stack<itemOPS> magazine;
    auto& ops_items = ops.items;
    auto& vars = ops.vars;
    auto& arrs = ops.arrs;
    
    for (size_t i = 0; i < ops_items.size(); ++i)
    {
        switch (ops_items[i].type)
        {
            case typeOPS::VARIABLE:
            {
                if (vars.count(ops_items[i].var_name)) {
                    ops_items[i].var = &vars[ops_items[i].var_name];
                }
                else if (!arrs.count(ops_items[i].var_name)) {
                    stringstream ss;
                    ss << "unknown variable name: '" << ops_items[i].var_name << "'";
                    throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                }
                magazine.push(ops_items[i]);
                break;
            }
            case typeOPS::NUMBER:
            {
                magazine.push(ops_items[i]);
                break;
            }
            case typeOPS::OPERATION:
            {
                switch (ops_items[i].operation)
                {
                    case operationOPS::READ:
                    {
                        long long int read;
                        in >> read;
                        if (is_overflow(read)) {
                            stringstream ss;
                            ss << "number overflow";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }
                        
                        itemOPS a = magazine.top(); magazine.pop();
                        if (a.type != typeOPS::VARIABLE) {
                            stringstream ss;
                            ss << "'" << a.type << "' was found, BUT expected: '" << typeOPS::VARIABLE << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }
                        else if (a.var == nullptr) {
                            stringstream ss;
                            ss << "use [index] for arrays '" << a.var_name << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }

                        *a.var = read;
                        break;
                    }
                    case operationOPS::WRITE:
                    {
                        itemOPS a = magazine.top(); magazine.pop();
                        out << get_num(a) << endl;
                        break;
                    }
                    case operationOPS::PLUS:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        long long int result = get_num(a) + get_num(b);

                        if (is_overflow(result)) {
                            throw out_of_range("integer overflow, str 63");
                        }
                        
                        magazine.emplace(result, a.debug_info);
                        break;
                    }
                    case operationOPS::MINUS:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        long long int result = get_num(a) - get_num(b);
                        if (is_overflow(result)) {
                            stringstream ss;
                            ss << "number overflow";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }
                        
                        magazine.emplace(result, a.debug_info);
                        break;
                    }
                    case operationOPS::MULTIPLY:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        long long int result = get_num(a) * get_num(b);
                        if (is_overflow(result)) {
                            stringstream ss;
                            ss << "number overflow";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }
                        
                        magazine.emplace(result, a.debug_info);
                        break;
                    }
                    case operationOPS::DIVIDE:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        if (get_num(b) == 0) {
                            stringstream ss;
                            ss << "division by zero";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }

                        itemOPS a = magazine.top(); magazine.pop();
                        long long int result = get_num(a) / get_num(b);
                        if (is_overflow(result)) {
                            stringstream ss;
                            ss << "number overflow";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }
                        
                        magazine.emplace(result, a.debug_info);
                        break;
                    }
                    case operationOPS::LESS:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        magazine.emplace(static_cast<long long int>(get_num(a) < get_num(b)), a.debug_info);
                        break;
                    }
                    case operationOPS::ASSIGN:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        if (a.type != typeOPS::VARIABLE) {
                            stringstream ss;
                            ss << "'" << a.type << "' was found, BUT expected: '" << typeOPS::VARIABLE << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }
                        else if (a.var == nullptr) {
                            stringstream ss;
                            ss << "use [index] for arrays '" << a.var_name << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }

                        *a.var = get_num(b);
                        break;
                    }
                    case operationOPS::MORE:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        magazine.emplace(static_cast<long long int>(get_num(a) > get_num(b)), a.debug_info);
                        break;
                    }
                    case operationOPS::EQUAL:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        magazine.emplace(static_cast<long long int>(get_num(a) == get_num(b)), a.debug_info);
                        break;
                    }
                    case operationOPS::LESS_OR_EQUAL:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        magazine.emplace(static_cast<long long int>(get_num(a) <= get_num(b)), a.debug_info);
                        break;
                    }
                    case operationOPS::MORE_OR_EQUAL:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        magazine.emplace(static_cast<long long int>(get_num(a) >= get_num(b)), a.debug_info);
                        break;
                    }
                    case operationOPS::NOT_EQUAL:
                    {
                        itemOPS b = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        magazine.emplace(static_cast<long long int>(get_num(a) != get_num(b)), a.debug_info);
                        break;
                    }
                    case operationOPS::J:
                    {
                        itemOPS metka = magazine.top(); magazine.pop();
                        
                        i = static_cast<int>(get_num(metka)) - 1;
                        break;
                    }
                    case operationOPS::JF:
                    {
                        itemOPS metka = magazine.top(); magazine.pop();
                        itemOPS a = magazine.top(); magazine.pop();
                        
                        if (get_num(a) == 0) {
                            i = static_cast<int>(get_num(metka)) - 1;
                        }
                        break;
                    }
                    case operationOPS::I:
                    {
                        itemOPS idx = magazine.top(); magazine.pop();
                        itemOPS arr = magazine.top(); magazine.pop();
                        
                        if (arr.type != typeOPS::VARIABLE) {
                            stringstream ss;
                            ss << "'" << arr.type << "' was found, BUT expected: '" << typeOPS::VARIABLE << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }

                        if (!arrs.count(arr.var_name)) {
                            stringstream ss;
                            ss << "no array called '" << arr.var_name << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }

                        auto& mass = arrs[arr.var_name];
                        int index = static_cast<int>(get_num(idx));

                        if (index < 0 || mass.size() <= index) {
                            stringstream ss;
                            ss << "out of range [" << 0 << ", " << mass.size() << "] for array '" << arr.var_name << "'";
                            throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        }

                        arr.var = &mass[index];
                        magazine.push(arr);
                        break;
                    }
                    default:
                    {
                        stringstream ss;
                        ss << "'" << ops_items[i].type << "' was found";
                        throw MyInterpretException(ss.str(), ops_items[i].debug_info);
                        break;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}
