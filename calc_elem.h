#ifndef CALC_ELEM_H
#define CALC_ELEM_H

#include <QString>

struct CalcItem {
    QString lex;
    double value = 0.0;
    bool known = false;
    CalcItem* left;
    CalcItem* right;

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
            }
        }
        known = true;
    }
};


#endif // CALC_ELEM_H
