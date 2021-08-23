#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QObject *parent)
    : QObject(parent)
    , mInterString{"0"}

{
}

QString Calculator::getInterString()
{
    return mInterString;
}

void Calculator::onClick(QString str)
{
    int intVal;
    bool isNumber = false;
    intVal = str.toInt(&isNumber);
    qDebug() << intVal << isNumber;
    if (isNumber)
    {
        mInterString += str;
        emit interrimChanged();
    }
}

