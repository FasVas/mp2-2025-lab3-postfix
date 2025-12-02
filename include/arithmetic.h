// объявление функций и классов для вычисления арифметических выражений
#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <string>


class Arithmetic
{
public:

	Arithmetic();
	Arithmetic(const std::string& expr);

	void setInfixExpression(const std::string& expr);
	std::string getInfixExpression() const;
	std::string getPostfixExpression() const;

	void setVariableX(double value);
	void setVariableY(double value);
	void setVariableZ(double value);
	double getVariableX() const;
	double getVariableY() const;
	double getVariableZ() const;

	void convertToPostfix();
	double calculate() const;

	bool validate() const;


private:
	std::string infix_line;
	std::string postfix_line;
	double x_var, y_var, z_var;

	bool isOperator(char c) const;           // +, -, *, /, ^ и т.д.
	bool isFunction(const std::string& token) const; // sin, cos, log
	bool isVariable(char c) const;           // x, y, z
	int getPrecedence(char op) const;        // Приоритет операций
	bool isDigit(char c) const;              // 0-9
	bool isLetter(char c) const;             // a-z, A-Z

	std::string extractNumber(const std::string& expr, int& pos) const;
	std::string extractToken(const std::string& expr, int& pos) const;

	double applyOperator(char op, double a, double b) const;
	double applyFunction(const std::string& func, double arg) const;
	double getVariableValue(char var) const;


};
#endif
