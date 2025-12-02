// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

#include <cmath>
#include <string>

const double EPSILON = 1e-6;

class ArithmeticTest : public ::testing::Test
{
protected:
    Arithmetic expr;

    bool areEqual(double a, double b) 
    {
        return std::fabs(a - b) < EPSILON;
    }
};



TEST_F(ArithmeticTest, DefaultConstructor)
{
    EXPECT_EQ(expr.getInfixExpression(), "");
    EXPECT_EQ(expr.getPostfixExpression(), "");
}
TEST_F(ArithmeticTest, ConstructorWithExpression)
{
    Arithmetic e("2 + 3");
    EXPECT_EQ(e.getInfixExpression(), "2 + 3");
    EXPECT_FALSE(e.getPostfixExpression().empty());
}
TEST_F(ArithmeticTest, SetGetInfixExpression)
{
    expr.setInfixExpression("1 + 2");
    EXPECT_EQ(expr.getInfixExpression(), "1 + 2");
}
TEST_F(ArithmeticTest, SetInfixClearsPostfix)
{
    expr.setInfixExpression("1 + 2");
    expr.convertToPostfix();
    EXPECT_FALSE(expr.getPostfixExpression().empty());

    expr.setInfixExpression("3 + 4");
    EXPECT_EQ(expr.getPostfixExpression(), "");
}
TEST_F(ArithmeticTest, VariableGettersSetters)
{
    expr.setVariableX(1.5);
    expr.setVariableY(3.5);
    expr.setVariableZ(5.5);

    EXPECT_DOUBLE_EQ(expr.getVariableX(), 1.5);
    EXPECT_DOUBLE_EQ(expr.getVariableY(), 3.5);
    EXPECT_DOUBLE_EQ(expr.getVariableZ(), 5.5);
}
TEST_F(ArithmeticTest, DefaultVariableValues)
{
    EXPECT_DOUBLE_EQ(expr.getVariableX(), 0.0);
    EXPECT_DOUBLE_EQ(expr.getVariableY(), 0.0);
    EXPECT_DOUBLE_EQ(expr.getVariableZ(), 0.0);
}
TEST_F(ArithmeticTest, Addition)
{
    expr.setInfixExpression("2 + 3");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, Subtraction)
{
    expr.setInfixExpression("3 - 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, Multiplication)
{
    expr.setInfixExpression("3 * 4");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 12.0));
}
TEST_F(ArithmeticTest, Division)
{
    expr.setInfixExpression("15 / 5");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 3.0));
}
TEST_F(ArithmeticTest, Power)
{
    expr.setInfixExpression("2 ^ 3");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 8.0));
}
TEST_F(ArithmeticTest, PowerOfZero)
{
    expr.setInfixExpression("5 ^ 0");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, MultiplicationPriority)
{
    expr.setInfixExpression("7 + 3 * 3");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 16.0));
}
TEST_F(ArithmeticTest, DivisionPriority)
{
    expr.setInfixExpression("2 + 6 / 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, PowerPriority)
{
    expr.setInfixExpression("3 + 3 ^ 3");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 30.0));
}
TEST_F(ArithmeticTest, LeftAssociativity)
{
    expr.setInfixExpression("10 - 5 - 3");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 2.0));
}
TEST_F(ArithmeticTest, SimpleParentheses)
{
    expr.setInfixExpression("(2 + 2) * 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 8.0));
}
TEST_F(ArithmeticTest, NestedParentheses)
{
    expr.setInfixExpression("((2 + 3) * (4 + 1))");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 25.0));
}
TEST_F(ArithmeticTest, MultipleParentheses) 
{
    expr.setInfixExpression("(5 + 3) * 2 - 4 / (1 + 1)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 14.0));
}
TEST_F(ArithmeticTest, DeeplyNestedParentheses)
{
    expr.setInfixExpression("(((1 + 2)))");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 3.0));
}
TEST_F(ArithmeticTest, DecimalAddition)
{
    expr.setInfixExpression("3.5 + 1.5");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, DecimalMultiplication)
{
    expr.setInfixExpression("2.5 * 2.0");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, DecimalDivision)
{
    expr.setInfixExpression("10 / 4");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 2.5));
}
TEST_F(ArithmeticTest, SmallDecimals) {
    expr.setInfixExpression("0.001 + 0.002");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 0.003));
}



TEST_F(ArithmeticTest, SinZero)
{
    expr.setInfixExpression("sin(0)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 0.0));
}
TEST_F(ArithmeticTest, SinPiOver2) {
    expr.setInfixExpression("sin(1.5707963267948966)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, SinWithExpression)
{
    expr.setInfixExpression("sin(3.14159265 / 2)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, CosZero)
{
    expr.setInfixExpression("cos(0)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, CosPi)
{
    expr.setInfixExpression("cos(3.14159265)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), -1.0));
}
TEST_F(ArithmeticTest, TanZero)
{
    expr.setInfixExpression("tg(0)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 0.0));
}
TEST_F(ArithmeticTest, TanPiOver4)
{
    expr.setInfixExpression("tg(0.7853981633974483)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, LogE)
{
    expr.setInfixExpression("log(2.718281828)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, LogOne)
{
    expr.setInfixExpression("log(1)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 0.0));
}
TEST_F(ArithmeticTest, LogWithExpression)
{
    expr.setInfixExpression("log(10 / 2)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), std::log(5.0)));
}
TEST_F(ArithmeticTest, ExpZero)
{
    expr.setInfixExpression("exp(0)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, ExpOne)
{
    expr.setInfixExpression("exp(1)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), std::exp(1.0)));
}



TEST_F(ArithmeticTest, SinPlusCos)
{
    expr.setInfixExpression("sin(0) + cos(0)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 1.0));
}
TEST_F(ArithmeticTest, ComplexWithFunctions)
{
    expr.setInfixExpression("2 * sin(0) + 3 * cos(0)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 3.0));
}
TEST_F(ArithmeticTest, FunctionComposition)
{
    expr.setInfixExpression("exp(log(5))");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, NestedFunctions)
{
    expr.setInfixExpression("sin(cos(0))");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), std::sin(1.0)));
}




TEST_F(ArithmeticTest, x_var)
{
    expr.setVariableX(5.0);
    expr.setInfixExpression("x + 3");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 8.0));
}
TEST_F(ArithmeticTest, y_var)
{
    expr.setVariableY(10.0);
    expr.setInfixExpression("y * 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 20.0));
}
TEST_F(ArithmeticTest, z_var)
{
    expr.setVariableZ(7.0);
    expr.setInfixExpression("z - 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, AllThreeVariables)
{
    expr.setVariableX(2.0);
    expr.setVariableY(3.0);
    expr.setVariableZ(4.0);
    expr.setInfixExpression("x + y * z");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 14.0));
}
TEST_F(ArithmeticTest, VariablesInParentheses)
{
    expr.setVariableX(5.0);
    expr.setVariableY(3.0);
    expr.setInfixExpression("(x + y) * 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 16.0));
}

TEST_F(ArithmeticTest, VariablesWithFunctions)
{
    expr.setVariableX(0.0);
    expr.setInfixExpression("sin(x) + 5");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, VariableMultipleUse)
{
    expr.setVariableX(5.0);
    expr.setInfixExpression("x + x * x");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 30.0));
}
TEST_F(ArithmeticTest, NegativeVariables)
{
    expr.setVariableX(-5.0);
    expr.setVariableY(3.0);
    expr.setInfixExpression("x + y");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), -2.0));
}
TEST_F(ArithmeticTest, VariableInExp)
{
    expr.setVariableX(1.0);
    expr.setInfixExpression("exp(x)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), std::exp(1.0)));
}
TEST_F(ArithmeticTest, ComplexVariableExpression)
{
    expr.setVariableX(2.0);
    expr.setVariableY(3.0);
    expr.setVariableZ(4.0);
    expr.setInfixExpression("x ^ 2 + y * z - 5");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 11.0));
}





TEST_F(ArithmeticTest, ValidSimpleExpression)
{
    expr.setInfixExpression("(2 + 3)");
    EXPECT_TRUE(expr.validate());
}
TEST_F(ArithmeticTest, ValidNestedExpression)
{
    expr.setInfixExpression("((2 + 3) * (4 - 1))");
    EXPECT_TRUE(expr.validate());
}
TEST_F(ArithmeticTest, ValidExpressionNoParentheses)
{
    expr.setInfixExpression("2 + 3 * 4");
    EXPECT_TRUE(expr.validate());
}
TEST_F(ArithmeticTest, InvalidMissingOpenParenthesis)
{
    expr.setInfixExpression("2 + 3)");
    EXPECT_FALSE(expr.validate());
}
TEST_F(ArithmeticTest, InvalidMissingCloseParenthesis)
{
    expr.setInfixExpression("(2 + 3");
    EXPECT_FALSE(expr.validate());
}
TEST_F(ArithmeticTest, InvalidClosingBeforeOpening)
{
    expr.setInfixExpression(")2 + 3(");
    EXPECT_FALSE(expr.validate());
}
TEST_F(ArithmeticTest, EmptyExpressionValid)
{
    expr.setInfixExpression("");
    EXPECT_TRUE(expr.validate());
}




TEST_F(ArithmeticTest, DivisionByZeroError)
{
    expr.setInfixExpression("5 / 0");
    expr.convertToPostfix();
    EXPECT_THROW(expr.calculate(), std::runtime_error);
}
TEST_F(ArithmeticTest, DivisionByZeroInExpression)
{
    expr.setInfixExpression("10 / (5 - 5)");
    expr.convertToPostfix();
    EXPECT_THROW(expr.calculate(), std::runtime_error);
}
TEST_F(ArithmeticTest, LogNegativeError)
{
    expr.setInfixExpression("log(-1)");
    expr.convertToPostfix();
    EXPECT_THROW(expr.calculate(), std::runtime_error);
}
TEST_F(ArithmeticTest, LogZeroError)
{
    expr.setInfixExpression("log(0)");
    expr.convertToPostfix();
    EXPECT_THROW(expr.calculate(), std::runtime_error);
}
TEST_F(ArithmeticTest, MismatchedParenthesesError)
{
    expr.setInfixExpression("(2 + 3");
    EXPECT_THROW(expr.convertToPostfix(), std::runtime_error);
}
TEST_F(ArithmeticTest, ExtraClosingParenthesesError)
{
    expr.setInfixExpression("2 + 3))");
    EXPECT_THROW(expr.convertToPostfix(), std::runtime_error);
}
TEST_F(ArithmeticTest, UnknownFunctionError)
{
    expr.setInfixExpression("foo(5)");
    EXPECT_THROW(expr.convertToPostfix(), std::runtime_error);
}
TEST_F(ArithmeticTest, EmptyPostfixError)
{
    EXPECT_THROW(expr.calculate(), std::runtime_error);
}
TEST_F(ArithmeticTest, NotEnoughOperandsError)
{
    expr.setInfixExpression("5 +");
    expr.convertToPostfix();
    EXPECT_THROW(expr.calculate(), std::runtime_error);
}



TEST_F(ArithmeticTest, SimplePostfixConversion)
{
    expr.setInfixExpression("2 + 3");
    expr.convertToPostfix();
    std::string postfix = expr.getPostfixExpression();
    EXPECT_FALSE(postfix.empty());
}
TEST_F(ArithmeticTest, PostfixContainsElements)
{
    expr.setInfixExpression("2 + 3 * 4");
    expr.convertToPostfix();
    std::string postfix = expr.getPostfixExpression();
    EXPECT_NE(postfix.find("2"), std::string::npos);
    EXPECT_NE(postfix.find("3"), std::string::npos);
    EXPECT_NE(postfix.find("4"), std::string::npos);
    EXPECT_NE(postfix.find("*"), std::string::npos);
    EXPECT_NE(postfix.find("+"), std::string::npos);
}
TEST_F(ArithmeticTest, PostfixWithFunction)
{
    expr.setInfixExpression("sin(0)");
    expr.convertToPostfix();
    std::string postfix = expr.getPostfixExpression();
    EXPECT_NE(postfix.find("sin"), std::string::npos);
}
TEST_F(ArithmeticTest, PostfixWithVariable)
{
    expr.setInfixExpression("x + 5");
    expr.convertToPostfix();
    std::string postfix = expr.getPostfixExpression();
    EXPECT_NE(postfix.find("x"), std::string::npos);
}



TEST_F(ArithmeticTest, SingleNumber)
{
    expr.setInfixExpression("42");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 42.0));
}
TEST_F(ArithmeticTest, SingleDecimal)
{
    expr.setInfixExpression("3.14");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 3.14));
}
TEST_F(ArithmeticTest, ExpressionWithSpaces)
{
    expr.setInfixExpression("  2   +   3  ");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, ChainedDivisions)
{
    expr.setInfixExpression("100 / 10 / 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}
TEST_F(ArithmeticTest, LongAdditionSequence)
{
    expr.setInfixExpression("1 + 2 + 3 + 4 + 5");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 15.0));
}
TEST_F(ArithmeticTest, NumberInParentheses)
{
    expr.setInfixExpression("(42)");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 42.0));
}
TEST_F(ArithmeticTest, LargeNumbers)
{
    expr.setInfixExpression("123456 + 654321");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 777777.0));
}
TEST_F(ArithmeticTest, ZeroInOperations)
{
    expr.setInfixExpression("0 + 0 * 0 + 5");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 5.0));
}



TEST_F(ArithmeticTest, VeryComplexExpression)
{
    expr.setInfixExpression("((5 + 3) * 2 - 4 / 2) ^ 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 196.0));
}
TEST_F(ArithmeticTest, AllOperatorsTogether)
{
    expr.setInfixExpression("1 + 2 * 3 ^ 2 - 4 / 2");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 17.0));
}
TEST_F(ArithmeticTest, ComplexWithVariablesAndFunctions)
{
    expr.setVariableX(2.0);
    expr.setVariableY(3.0);
    expr.setInfixExpression("sin(0) * x + cos(0) * y");
    expr.convertToPostfix();
    EXPECT_TRUE(areEqual(expr.calculate(), 3.0));
}
