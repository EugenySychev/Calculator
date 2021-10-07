#ifndef CALCENGINE_H
#define CALCENGINE_H

#include <QtMath>
#include <QStringList>
#include <QDebug>
#include "calc_elem.h"

class CalcEngine
{
public:
    CalcEngine();

    double calculate();

    void setExpression(QString exprString);

    void setDegRadMode(bool degRadMode);
private:
    CalcItem *root;
    QString mExprString;
    bool mDegRadMode;
    CalcItem *analyze(QString str);
    CalcItem*  getBySign(const QString &sourceString, QChar sign);
};

#endif // CALCENGINE_H
