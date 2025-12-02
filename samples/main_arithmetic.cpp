// реализация пользовательского приложения

#include "arithmetic.h"
#include <iostream>
#include <iomanip>




using namespace std;

void show()
{
    cout << "1 - enter the line";
    cout << "2 - enter variables";
    cout << "3 - postfix";
    cout << "4 - calculate";
    cout << "5 - end"
};






int main() {
    Arithmetic expr;
    int choice;
    bool hasExpression = false;

    cout << fixed << setprecision(6);

    while (true) {
        show();
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) 
            {
            case 1: 
            {
                cout << "\nEnter an expression:\t";
                string input;
                getline(cin, input);

                expr.setInfixExpression(input);

                if (!expr.validate()) {
                    cout << "Expression is inavlid\n";
                    hasExpression = false;
                }
                else {
                    cout << "Expression is saved.\n";
                    hasExpression = true;
                }
                break;
            }

            case 2: 
            {
                double x, y, z;
                cout << "\nEnter x: ";
                cin >> x;
                cout << "Enter y: ";
                cin >> y;
                cout << "Enter z: ";
                cin >> z;

                expr.setVariableX(x);
                expr.setVariableY(y);
                expr.setVariableZ(z);

                cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
                break;
            }

            case 3: 
            {
                if (!hasExpression) 
                {
                    cout << "need an expression)\n";
                    break;
                }

                expr.convertToPostfix();
                cout << "\nInfix:\t" << expr.getInfixExpression() << endl;
                cout << "Postfix:\t" << expr.getPostfixExpression() << endl;
                break;
            }

            case 4: 
            {
                if (!hasExpression) {
                    cout << "need an expression\n";
                    break;
                }

                expr.convertToPostfix();
                double result = expr.calculate();

                cout << "\nExpression:\t" << expr.getInfixExpression() << endl;
                cout << "Variables:\tx = " << expr.getVariableX()
                    << ", y = " << expr.getVariableY()
                    << ", z = " << expr.getVariableZ() << endl;
                cout << "Postfix:\t" << expr.getPostfixExpression() << endl;
                cout << "Result:\t" << result << endl;
                break;
            }

            case 5:
            {
                return 0;
            }

            default: {
                cout << "invalid\n";
                break;
            }
            }
        }
        catch (const exception& exc) {
            cout << "\nERROR: " << exc.what() << endl;
        }
    }


    return 0;
}

