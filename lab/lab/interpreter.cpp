#include <stack>
#include <stdexcept>
#include <iostream>
#include "interpreter.h"

using namespace std;

int get_num(ops_item& item, OPS& ops) {
    if (item.type == ops_type::NUMBER)
    {
        return item.num;
    }
    else if (item.type == ops_type::VARIABLE)
    {
        if (ops.vars.count(item.var_name))
        {
            return ops.vars[item.var_name];
        }
        else
        {
            return ops.arrs[item.var_name][item.index];
        }
    }
    else
    {
        string msg = "Interpreter error; Variable or number was expected; line = "
            + to_string(item.line) + ", pos = " + to_string(item.pos);
        throw runtime_error(msg);
    }
}

int set_num(ops_item& item, int num, OPS& ops) {
    if (ops.vars.count(item.var_name))
    {
        ops.vars[item.var_name] = num;
    }
    else if (ops.arrs.count(item.var_name))
    {
        ops.arrs[item.var_name][item.index] = num;
    }
    else
    {
        string msg = "Interpreter error; Variable was expected; line = "
            + to_string(item.line) + ", pos = " + to_string(item.pos);
        throw runtime_error(msg);
    }
}

void interpret(OPS& ops)
{
    stack<ops_item> magazine;
    auto& ops_items = ops.items;
    auto& vars = ops.vars;
    auto& arrs = ops.arrs;

    for (size_t i = 0; i < ops_items.size(); ++i)
    {
        switch (ops_items[i].type)
        {
        case ops_type::VARIABLE:
        {
            if (!arrs.count(ops_items[i].var_name) && !vars.count(ops_items[i].var_name))
            {
                string msg = "Interpreter error; Unknown variable; line = "
                    + to_string(ops_items[i].line) + ", pos = " + to_string(ops_items[i].pos);
                throw runtime_error(msg);
            }
            magazine.push(ops_items[i]);
            break;
        }
        case ops_type::NUMBER:
        {
            magazine.push(ops_items[i]);
            break;
        }
        case ops_type::OPERATION:
        {
            switch (ops_items[i].operation)
            {
            case ops_operation::READ:
            {
                int number;
                cin >> number;
                ops_item a = magazine.top(); magazine.pop();
                set_num(a, number, ops);
                break;
            }
            case ops_operation::WRITE:
            {
                ops_item a = magazine.top(); magazine.pop();
                cout << get_num(a, ops) << endl;
                break;
            }
            case ops_operation::PLUS:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                int result = get_num(a, ops) + get_num(b, ops);

                magazine.emplace(result, a.line, a.pos);
                break;
            }
            case ops_operation::MINUS:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                int result = get_num(a, ops) - get_num(b, ops);

                magazine.emplace(result, a.line, a.pos);
                break;
            }
            case ops_operation::MULTIPLY:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                int result = get_num(a, ops) * get_num(b, ops);

                magazine.emplace(result, a.line, a.pos);
                break;
            }
            case ops_operation::DIVIDE:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                int result = get_num(a, ops) / get_num(b, ops);

                magazine.emplace(result, a.line, a.pos);
                break;
            }
            case ops_operation::LESS:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                magazine.emplace((get_num(a, ops) < get_num(b, ops)), a.line, a.pos);
                break;
            }
            case ops_operation::ASSIGN:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                set_num(a, get_num(b, ops), ops);
                break;
            }
            case ops_operation::MORE:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                magazine.emplace((get_num(a, ops) > get_num(b, ops)), a.line, a.pos);
                break;
            }
            case ops_operation::EQUAL:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                magazine.emplace((get_num(a, ops) == get_num(b, ops)), a.line, a.pos);
                break;
            }
            case ops_operation::LESS_OR_EQUAL:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                magazine.emplace((get_num(a, ops) <= get_num(b, ops)), a.line, a.pos);
                break;
            }
            case ops_operation::MORE_OR_EQUAL:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                magazine.emplace((get_num(a, ops) >= get_num(b, ops)), a.line, a.pos);
                break;
            }
            case ops_operation::NOT_EQUAL:
            {
                ops_item b = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                magazine.emplace((get_num(a, ops) != get_num(b, ops)), a.line, a.pos);
                break;
            }
            case ops_operation::J:
            {
                ops_item metka = magazine.top(); magazine.pop();

                i = get_num(metka, ops) - 1;
                break;
            }
            case ops_operation::JF:
            {
                ops_item metka = magazine.top(); magazine.pop();
                ops_item a = magazine.top(); magazine.pop();

                if (get_num(a, ops) == 0) {
                    i = get_num(metka, ops) - 1;
                }
                break;
            }
            case ops_operation::I:
            {
                ops_item idx = magazine.top(); magazine.pop();
                ops_item arr = magazine.top(); magazine.pop();

                arr.index = get_num(idx, ops);

                magazine.push(arr);
                break;
            }
            default:
            {
                string msg = "Interpreter error; Unknown operation; line = "
                    + to_string(ops_items[i].line) + ", pos = " + to_string(ops_items[i].pos);
                throw runtime_error(msg);
            }
            }
            break;
        }
        default:
        {
            string msg = "Interpreter error; Unknown ops item; line = "
                + to_string(ops_items[i].line) + ", pos = " + to_string(ops_items[i].pos);
            throw runtime_error(msg);
        }
        }
    }
}
