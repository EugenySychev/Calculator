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
    CalcItem * item{nullptr};
    if (ok)
    {
        item = new CalcItem();
        item->value = val;
        item->known = true;
    } else {
        // processing ()
        if (processExpression("sin(", str))
        {
            qDebug() << "Sin replaced " << str;
            return analyze(str);
        } else if (processExpression("cos(", str)) {

            qDebug() << "cos replaced " << str;
            return analyze(str);
        } else if (processExpression("tan(", str)) {
            return analyze(str);
        }



        while (str.contains('(') && str.contains(')'))
        {
            processExpression("(", str);
        }
        item = new CalcItem();
        item->isGrad = mDegRadMode;
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
            return analyze(str.replace("π", QString::number(M_PI, 'g', PRECISION)));
        }
        if (str.contains("e")) {
            return analyze(str.replace("e", QString::number(M_E, 'g', PRECISION)));
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

bool CalcEngine::processExpression(const QString expr, QString& str)
{
    int first = str.indexOf(expr);
    if (first == -1)
        return false;
    first += expr.length();

    int second = str.indexOf(")", first);
    if (second == -1)
        return false;
    qDebug() << "CHeck " << str << " for " << expr << " res = " << first << " and " << second;

    QString midstr = str.mid(first, second - first);
    CalcItem* intItem = getByExpr(midstr, expr);
    intItem->isGrad = mDegRadMode;
    intItem->calc();
    qDebug() << "Replaced " << expr+midstr+")";
    str = str.replace(expr+midstr+")", QString::number(intItem->value, 'g', PRECISION));
    qDebug() << " to " << QString::number(intItem->value, 'g', PRECISION);
    delete intItem;
    return true;

}

CalcItem* CalcEngine::getByExpr(QString source, QString expr)
{
    CalcItem* item{nullptr};
    if (!source.isEmpty()) {
        item = new CalcItem;
        item->isGrad = mDegRadMode;
        item->lex = expr;
        item->left = analyze(source);
    }

    return item;
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
        item->isGrad = mDegRadMode;
        item->lex = sign;
        item->left = analyze(left);
        item->right = analyze(right);
    }
    return item;

}

