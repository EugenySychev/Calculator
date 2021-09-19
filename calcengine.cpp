#include "calcengine.h"

#include <QLatin1Literal>

CalcEngine::CalcEngine()
    : root{nullptr}
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

void CalcEngine::setExpression(QString exprString)
{
    mExprString = exprString;
    root = analyze(mExprString);
}

CalcItem* CalcEngine::analyze(const QString str)
{
    bool ok = false;
    double val = str.toDouble(&ok);
    CalcItem * item = new CalcItem();

    if (ok)
    {
        item->value = val;
    } else {
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

CalcItem* CalcEngine::getBySign(const QString& sourceString, QChar sign)
{
    CalcItem * item{nullptr};
    QString left, right;
    int i = sourceString.indexOf(sign);
    if (i != -1)
    {
        left = sourceString.left(i);
        right = sourceString.mid(i + 1);
    }
    if (!left.isEmpty() && !right.isEmpty() && sign != 0)
    {
        qDebug() << "Found " << sign << " for " << left << " and " << right;
        item = new CalcItem;
        item->lex = sign;
        item->left = analyze(left);
        item->right = analyze(right);
    }
    return item;

}

