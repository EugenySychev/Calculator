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
    Q_PROPERTY(int cursorPosition READ getCurrentCursorPosition WRITE onCursorPositionChanged NOTIFY interrimChanged)
    Q_PROPERTY(QString result_string READ getResultString NOTIFY resultStringChanged)
    Q_PROPERTY(bool memory_is_empty READ getMemoryIsEmpty NOTIFY interrimChanged)
    Q_PROPERTY(QString degRadMode READ getDegRadMode NOTIFY degRadModeChanged)
    explicit Calculator(QObject *parent = nullptr);


    QString getInterString();
    int getCurrentCursorPosition();
    QString getResultString();
    bool getMemoryIsEmpty();
    QString getDegRadMode();

public slots:
    void onClick(QString str);
    void onPressed(int event);
    void onCursorPositionChanged(int);

signals:
    void interrimChanged();
    void cursorPositionChanged();
    void resultStringChanged();
    void memoryChanged();
    void degRadModeChanged();

private:
    QString mInterString;
    int mCurrentCursorPosition;
    CalcEngine engine;
    bool mMemoryIsEmpty;
    double mMemValue;
    bool mDegRadMode;

    void calculate();
    void processAppendString(const QString str);
    void checkFirstInput();
    QString cropPrecision(QString res);

};

#endif // CALCULATOR_H
