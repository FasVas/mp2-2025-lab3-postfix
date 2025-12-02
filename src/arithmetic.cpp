// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include <cmath>
#include <stdexcept>
#include "stack.h"


Arithmetic::Arithmetic() : infix_line(""), postfix_line(""), x_var(0), y_var(0), z_var(0) {}

Arithmetic::Arithmetic(const std::string& expr) : infix_line(expr), postfix_line(""), x_var(0), y_var(0), z_var(0) {
    convertToPostfix();
}

void Arithmetic::setInfixExpression(const std::string& expr) 
{
    infix_line = expr;
    postfix_line = "";
}

std::string Arithmetic::getInfixExpression() const 
{
    return infix_line;
}

std::string Arithmetic::getPostfixExpression() const 
{
    return postfix_line;
}

void Arithmetic::setVariableX(double value) 
{
    x_var = value;
}

void Arithmetic::setVariableY(double value) 
{
    y_var = value;
}

void Arithmetic::setVariableZ(double value) 
{
    z_var = value;
}

double Arithmetic::getVariableX() const 
{
    return x_var;
}

double Arithmetic::getVariableY() const 
{
    return y_var;
}

double Arithmetic::getVariableZ() const 
{
    return z_var;
}

bool Arithmetic::isOperator(char c) const 
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Arithmetic::isFunction(const std::string& token) const 
{
    return token == "sin" || token == "cos" || token == "tg" ||
        token == "log" || token == "exp";
}

bool Arithmetic::isVariable(char c) const 
{
    return c == 'x' || c == 'y' || c == 'z';
}

int Arithmetic::getPrecedence(char op) const 
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/')
    {
        return 2;
    }
    if (op == '^')
    {
        return 3;
    }
    return 0;
}

bool Arithmetic::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Arithmetic::isLetter(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::string Arithmetic::extractNumber(const std::string& expr, int& pos) const {
    std::string number = "";
    bool hasDecimal = false;

    while (pos < expr.length() && (isDigit(expr[pos]) || expr[pos] == '.')) {
        if (expr[pos] == '.') {
            if (hasDecimal) break;
            hasDecimal = true;
        }
        number += expr[pos];
        pos++;
    }
    pos--;
    return number;
}

std::string Arithmetic::extractToken(const std::string& expr, int& pos) const 
{
    std::string token = "";

    while (pos < expr.length() && isLetter(expr[pos])) 
    {
        token += expr[pos];
        pos++;
    }
    pos--;
    return token;
}

double Arithmetic::getVariableValue(char var) const 
{
    if (var == 'x')
    {
        return x_var;
    }
    if (var == 'y')
    {
        return y_var;
    }
    if (var == 'z')
    {
        return z_var;
    }
    throw std::runtime_error("Unknown variable");
}

void Arithmetic::convertToPostfix() {
    TStack<char> operators;
    TStack<std::string> functions;
    postfix_line = "";

    for (int i = 0; i < infix_line.length(); i++) 
    {
        char c = infix_line[i];

        if (c == ' ')
        {
            continue;
        }

        if (isDigit(c)) 
        {
            postfix_line += extractNumber(infix_line, i);
            postfix_line += ' ';
        }
        else if (isVariable(c)) 
        {
            postfix_line += c;
            postfix_line += ' ';
        }
        else if (isLetter(c)) 
        {
            std::string token = extractToken(infix_line, i);
            if (isFunction(token)) 
            {
                functions.add(token);
            }
            else 
            {
                throw std::runtime_error("Unknown function: " + token);
            }
        }
        else if (c == '(') 
        {
            operators.add(c);
        }
        else if (c == ')') 
        {
            while (!operators.cat() && operators.nice() != '(') 
            {
                postfix_line += operators.steal();
                postfix_line += ' ';
            }
            if (operators.cat()) 
            {
                throw std::runtime_error("Mismatched parentheses");
            }
            operators.steal();

            if (!functions.cat()) 
            {
                postfix_line += functions.steal();
                postfix_line += ' ';
            }
        }
        else if (isOperator(c)) 
        {
            while (!operators.cat() && operators.nice() != '(' &&
                getPrecedence(operators.nice()) >= getPrecedence(c)) 
            {
                postfix_line += operators.nice();
                postfix_line += ' ';
            }
            operators.add(c);
        }
    }

    while (!operators.cat()) 
    {
        if (operators.nice() == '(') 
        {
            throw std::runtime_error("Parentheses are invalid");
        }
        postfix_line += operators.steal();
        postfix_line += ' ';
    }
}

double Arithmetic::applyOperator(char op, double a, double b) const 
{
    switch (op)
    {
    case '+':
    {
        return a + b;
    }
    case '-':
    {
        return a - b;

    }
    case '*':
    {
        return a * b;
    }
    case '/':
    {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    case '^':
    {
        return pow(a, b);
    }
    default:
    {
        throw std::runtime_error("Unknown operator");
    }
    }
}

double Arithmetic::applyFunction(const std::string& func, double arg) const 
{
    if (func == "sin")
    {
        return sin(arg);
    }
    if (func == "cos")
    {
        return cos(arg);
    }
    if (func == "tg")
    {
        return tan(arg);
    }
    if (func == "log") 
    {
        if (arg <= 0)
        {
            throw std::runtime_error("Logarifm of negative number or zero");
        }
        return log(arg);
    }
    if (func == "exp")
    {
        return exp(arg);
    }
    throw std::runtime_error("Unknown function: " + func);
}

double Arithmetic::calculate() const {
    if (postfix_line.empty()) 
    {
        throw std::runtime_error("Postfix expression is empty");
    }

    TStack<double> values;
    std::string token = "";

    for (int i = 0; i < postfix_line.length(); i++) 
    {
        char c = postfix_line[i];

        if (c == ' ')
        {
            if (!token.empty())
            {
                if (isFunction(token))
                {
                    if (values.cat())
                    {
                        throw std::runtime_error("Not enough operands for function");
                    }
                    double arg = values.steal();
                    values.add(applyFunction(token, arg));
                }
                else if (token.length() == 1 && isVariable(token[0]))
                {
                    values.add(getVariableValue(token[0]));
                }
                else
                {
                    double value = 0;
                    bool negative = false;
                    int start = 0;

                    if (token[0] == '-')
                    {
                        negative = true;
                        start = 1;
                    }

                    for (int j = start; j < token.length(); j++)
                    {
                        if (token[j] == '.') continue;
                        value = value * 10 + (token[j] - '0');
                    }

                    int decimalPos = -1;
                    for (int j = 0; j < token.length(); j++)
                    {
                        if (token[j] == '.')
                        {
                            decimalPos = j;
                            break;
                        }
                    }

                    if (decimalPos != -1)
                    {
                        int decimals = token.length() - decimalPos - 1;
                        value /= pow(10, decimals);
                    }

                    if (negative) value = -value;
                    values.add(value);
                }
                token = "";
            }
            continue;
        }

        if (isOperator(c)) {
            if (values.count() < 2) {
                throw std::runtime_error("Not enough operands for operator");
            }
            double b = values.steal();
            double a = values.steal();
            values.add(applyOperator(c, a, b));
        }
        else {
            token += c;
        }
    }

    if (values.count() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return values.nice();
}

bool Arithmetic::validate() const {
    int parentheses = 0;

    for (int i = 0; i < infix_line.length(); i++) {
        char c = infix_line[i];
        if (c == '(') parentheses++;
        if (c == ')') parentheses--;
        if (parentheses < 0) return false;
    }

    return parentheses == 0;
}
