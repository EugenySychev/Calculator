#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QKeyEvent>
#include "calcengine.h"

class Calculator : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString interrim_string READ getInterString NOTIFY interrimChanged)
    Q_PROPERTY(int cursorPosition READ getCurrentCursorPosition WRITE onCursorPositionChanged NOTIFY cursorPositionChanged)
    Q_PROPERTY(QString result_string READ getResultString NOTIFY resultStringChanged)
    explicit Calculator(QObject *parent = nullptr);


    QString getInterString();
    int getCurrentCursorPosition();
    QString getResultString();
public slots:
    void onClick(QString str);
    void onPressed(int event);
    void onCursorPositionChanged(int);
signals:
    void interrimChanged();
    void cursorPositionChanged();
    void resultStringChanged();
private:
    QString mInterString;
    int mCurrentCursorPosition;
    CalcEngine engine;

    void calculate();
};

#endif // CALCULATOR_H
