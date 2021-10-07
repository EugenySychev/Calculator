#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QObject *parent)
    : QObject(parent)
    , mInterString{"0"}
    , mCurrentCursorPosition{0}
    , mMemoryIsEmpty{true}
    , mMemValue{0}
    , mDegRadMode{false}
{
}

QString Calculator::getInterString()
{
    return mInterString;
}

int Calculator::getCurrentCursorPosition()
{
    return mCurrentCursorPosition;
}

QString Calculator::getResultString()
{
    return QString::number(engine.calculate(), 'g', PRECISION);
}

bool Calculator::getMemoryIsEmpty()
{
    return mMemoryIsEmpty;
}

QString Calculator::getDegRadMode()
{
    return mDegRadMode ? "Deg" : "Rad";
}

void Calculator::onPressed(int event)
{
    switch (event) {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        onClick(QString::number(event - 0x30));
        break;
    case Qt::Key_ParenLeft:
        onClick("(");
        break;
    case Qt::Key_ParenRight:
        onClick(")");
        break;
    case Qt::Key_Asterisk:
        onClick("*");
        break;
    case Qt::Key_Plus:
        onClick("+");
        break;
    case Qt::Key_Comma:
        onClick(",");
        break;
    case Qt::Key_Minus:
        onClick("-");
        break;
    case Qt::Key_Slash:
        onClick("/");
        break;
    }
}

void Calculator::onCursorPositionChanged(int position)
{
    mCurrentCursorPosition = position;
}

void Calculator::onClick(QString str)
{
    int intVal;
    bool isNumber = false;
    intVal = str.toInt(&isNumber);
    if (str == "clear")
    {
        mInterString = "0";
        mCurrentCursorPosition = 1;
    } else if (str == "back") {
        mInterString = mInterString.left(mCurrentCursorPosition - 1) + mInterString.mid(mCurrentCursorPosition);
        mCurrentCursorPosition--;
        if (mInterString == "")
        {
            mInterString = "0";
            mCurrentCursorPosition = 1;
        }
    } else if (str == "MR") {
        mInterString = QString::number(mMemValue, 'g', PRECISION);
        mCurrentCursorPosition = mInterString.length();
    } else if (str == "M+") {
        mMemValue += engine.calculate();
        mMemoryIsEmpty = false;
    } else if (str == "M-") {
        mMemValue += engine.calculate();
        mMemoryIsEmpty = false;
    } else if (str == "MC") {
        mMemValue = 0;
        mMemoryIsEmpty = true;
    } else if (str == "=") {
        mInterString = QString::number(engine.calculate(), 'g', PRECISION);
        mCurrentCursorPosition = mInterString.length();
    } else if (str == "+" || str == "-" || str == "/" || str == "*" ) {
        if (mInterString.length() == 0 ||
                (mInterString.right(1) == "+" || mInterString.right(1) == "-"
                 || mInterString.right(1) == "/" || mInterString.right(1) == "*"))
            mInterString = mInterString.remove(mInterString.length() - 1, 1);

        processAppendString(str);
    } else if (str == "(" || str == ")") {
        QString lst = mInterString.right(1);
        if ((str == "(" && (lst == "+" || lst == "-" || lst == "/" || lst == "*")) ||
                (str == ")" && !(lst == "+" || lst == "-" || lst == "/" || lst == "*")))
            processAppendString(str);
    } else if (str == ",") {
        QString lst = mInterString.right(1);
        if (lst[0].isDigit())
        {
            const QLocale & cLocale = QLocale::c();
            str = cLocale.decimalPoint();
            qDebug() << "Point is " << str;
            processAppendString(str);

        }
    } else if (str == "Deg" || str == "Rad") {
        mDegRadMode = !mDegRadMode;
        engine.setDegRadMode(mDegRadMode);
        emit degRadModeChanged();
//    } else if (str == )
    } else {
        if (isNumber)
        {
            if (mInterString == "0")
            {
                mInterString.clear();
            }
        }
            processAppendString(str);

    }
    emit interrimChanged();
    engine.setExpression(mInterString);
    emit resultStringChanged();

}
void Calculator::processAppendString(const QString str)
{
    mInterString.insert(mCurrentCursorPosition, str);
    mCurrentCursorPosition++;
    emit interrimChanged();
}

void Calculator::calculate()
{

}

