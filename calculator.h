#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString interrim_string READ getInterString NOTIFY interrimChanged)
    explicit Calculator(QObject *parent = nullptr);


    QString getInterString();
public slots:
    void onClick(QString str);

signals:
    void interrimChanged();

private:
    QString mInterString;
};

#endif // CALCULATOR_H
