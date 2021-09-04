#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QObject *parent)
    : QObject(parent)
    , mInterString{"0"}
    , mCurrentCursorPosition{0}

{
}

QString Calculator::getInterString()
{
    return mInterString;
}

int Calculator::getCurrentCursorPosition()
{
    qDebug() << "Read to qml" << mCurrentCursorPosition;
    return mCurrentCursorPosition;
}

void Calculator::onPressed(int event)
{
    qDebug() << event;
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
    qDebug() << "From Qml " << position;
    mCurrentCursorPosition = position;
}

void Calculator::onClick(QString str)
{
    int intVal;
    bool isNumber = false;
    intVal = str.toInt(&isNumber);
    qDebug() << intVal << isNumber << QChar(str.at(0)) << mCurrentCursorPosition;
    if (isNumber)
    {
        if (mInterString == "0")
        {
            mInterString.clear();
        }
        mInterString.insert(mCurrentCursorPosition, QChar(str.at(0)));
        mCurrentCursorPosition++;
        emit cursorPositionChanged();
        emit interrimChanged();
    }
}
