#ifndef CALC_ELEM_H
#define CALC_ELEM_H

#include <QString>
#include <qmath.h>

struct CalcItem {
    QString lex;
    double value = 0.0;
    bool known = false;
    CalcItem* left;
    CalcItem* right;
    bool isGrad;

    void calc() {
        if (left)
            if (!left->known)
                left->calc();
        if (right)
            if (!right->known)
                right->calc();

        if (left && right)
        {
            if (lex == "*")
            {
                value = left->value * right->value;
            } else if (lex == "/") {
                value = left->value / right->value;
            } else if (lex == "+") {
                value = left->value + right->value;
            } else if (lex == "-") {
                value = left->value - right->value;
            } else if (lex == "mod") {
                value = (int)left->value % (int)right->value;
            } else if (lex == "sin") {
                value = qSin(isGrad? qDegreesToRadians(left->value) : left->value);
            } else if (lex == "cos") {
                value = qCos(isGrad? qDegreesToRadians(left->value) : left->value);
            } else if (lex == "tan") {
                value = qTan(isGrad? qDegreesToRadians(left->value) : left->value);
            } else if (lex == "asin") {
                value = qAsin(isGrad? qDegreesToRadians(left->value) : left->value);
            } else if (lex == "acos") {
                value = qAcos(isGrad? qDegreesToRadians(left->value) : left->value);
            } else if (lex == "atan") {
                value = qAtan(isGrad? qDegreesToRadians(left->value) : left->value);
            } else if (lex == "!") {
                double res = 0;
                if (left->value == 0)
                    res = 1;
                else
                    for (int i = 1; i < left->value; i++)
                        res *= i;
                value = res;
            } else if (lex == "%") {
                value = left->value / 100;
            }
        }
        known = true;
    }
};


#endif // CALC_ELEM_H
