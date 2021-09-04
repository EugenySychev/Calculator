#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QKeyEvent>


class Calculator : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString interrim_string READ getInterString NOTIFY interrimChanged)
    Q_PROPERTY(int cursorPosition READ getCurrentCursorPosition WRITE onCursorPositionChanged NOTIFY cursorPositionChanged)
    explicit Calculator(QObject *parent = nullptr);


    QString getInterString();
    int getCurrentCursorPosition();
public slots:
    void onClick(QString str);
    void onPressed(int event);
    void onCursorPositionChanged(int);
signals:
    void interrimChanged();
    void cursorPositionChanged();

private:
    QString mInterString;
    int mCurrentCursorPosition;
};

#endif // CALCULATOR_H
