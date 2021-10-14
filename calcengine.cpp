#include "calcengine.h"

#include <QLatin1Literal>

CalcEngine::CalcEngine()
    : root{nullptr}
    , mDegRadMode{false}
{

}

double CalcEngine::calculate()
{
    if (root)
    {
        root->calc();
        return root->value;
    }
    return 0;
}

void CalcEngine::setDegRadMode(bool degRadMode)
{

}

void CalcEngine::setExpression(QString exprString)
{
    mExprString = exprString;
    root = analyze(mExprString);
}

CalcItem* CalcEngine::analyze(QString str)
{
    bool ok = false;
    double val = str.toDouble(&ok);
    CalcItem * item = new CalcItem();
    if (ok)
    {
        item->value = val;
    } else {
        // processing ()


        while (str.contains("sin(") && str.contains(")"))
        {
//            int first = str.indexOf("sin(")
        }
        while (str.contains('(') && str.contains(')'))
        {
            int first = str.indexOf('(');
            int second = str.indexOf(')', first + 1);
            QString midstr = str.mid(first + 1, second - first - 1);
            CalcItem* intItem = analyze(midstr);
            intItem->calc();
            str = str.replace("("+midstr+")", QString::number(intItem->value));
            delete intItem;
        }

        while (str.contains('|') && str.count('|') > 1)
        {
            int first = str.indexOf('|');
            QString midstr = str.mid(first + 1, str.indexOf('|', first + 1) - first - 1);
            CalcItem* intItem = analyze(midstr);
            intItem->calc();
            str = str.replace("|"+midstr+"|", QString::number(abs(intItem->value)));
            qDebug() << str;
            delete intItem;
        }
        if (str.contains("π")) {
            return analyze(str.replace("π", QString::number(M_PI)));
        }
        if (str.contains("e")) {
            return analyze(str.replace("e", QString::number(M_E)));
        }
        item = getBySign(str, '+');
        if (item)
            return item;
        else {
            item = getBySign(str, '-');
            if (item)
                return item;
            else {
                item = getBySign(str, '*');
                if (item)
                    return item;
                else {
                    item = getBySign(str, '/');
                    if (item)
                        return item;
                }
            }
        }
    }
    return item;
}

QString CalcEngine::processExpression(QString expr, QString str)
{
    int first = str.indexOf(expr) + expr.length();
    int second = str.indexOf(")", first);
    QString midstr = str.mid(first + 1, second - first - 1);
    CalcItem* intItem = analyze(midstr);
    intItem->calc();
    str = str.replace(expr+midstr+")", QString::number(getValueExpr(expr, intItem)));
    delete intItem;
}

double CalcEngine::getValueExpr(QString expr, CalcItem* item)
{

}

CalcItem* CalcEngine::getBySign(const QString& sourceString, QChar sign)
{
    CalcItem * item{nullptr};
    QString left, right;
    int i = sourceString.lastIndexOf(sign);
    if (i != -1)
    {
        left = sourceString.left(i);
        right = sourceString.mid(i + 1);
    }
    if (!left.isEmpty() && !right.isEmpty() && sign != 0)
    {
        item = new CalcItem;
        item->lex = sign;
        item->left = analyze(left);
        item->right = analyze(right);
    }
    return item;

}

