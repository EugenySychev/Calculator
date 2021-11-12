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
    mDegRadMode = degRadMode;
}

void CalcEngine::setExpression(QString exprString)
{
    mExprString = exprString;
    root = analyze(mExprString);
}

CalcItem* CalcEngine::analyze(QString str)
{
    bool ok = false;
    bool isPerc = str.endsWith("%");
    double val = str.left(str.length() - (isPerc ? 1 : 0)).toDouble(&ok);
    CalcItem * item{nullptr};
    if (ok)
    {
        item = new CalcItem();
        item->value = val;
        item->known = true;
        item->isPerc = isPerc;
    } else {
        // processing ()
        if (processPostOperator("!", str)) {
            return analyze(str);
        }

        if (processExpression("log(", str)) {
            return analyze(str);
        } else if (processExpression("ln(", str)) {
            return analyze(str);
        } else if (processExpression("√(", str)) {
            return analyze(str);
        }

        if (processExpression("asin(", str)) {
            return analyze(str);
        } else if (processExpression("acos(", str)) {
            return analyze(str);
        } else if (processExpression("atan(", str)) {
            return analyze(str);
        }
        if (processExpression("sin(", str))
        {
            return analyze(str);
        } else if (processExpression("cos(", str)) {
            return analyze(str);
        } else if (processExpression("tan(", str)) {
            return analyze(str);
        }



        while (str.contains('(') && str.contains(')'))
        {
            processExpression("(", str);
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
            return analyze(str.replace("π", QString::number(M_PI, 'f', PRECISION)));
        }
        if (str.contains("e")) {
            return analyze(str.replace("e", QString::number(M_E, 'f', PRECISION)));
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
                    else {
                        item = getBySign(str, '^');
                        if (item)
                            return item;
                        else
                            qDebug() << "Unknown operator ";
                    }
                }
            }
        }
    }
    return item;
}

bool CalcEngine::processPostOperator(const QString op, QString& str)
{
    int second = str.indexOf(op);
    if (second < 0 )
        return false;
    int first = second - 1;
    while ( first >= 0 && (str.mid(first, 1).at(0).isDigit() || str.mid(first, 1).at(0) == "."))
        first--;
    //first++; //step back to one
    QString midstr = str.mid(first, second - first);

    CalcItem* intItem = getByExpr(midstr, op);
    intItem->isGrad = mDegRadMode;
    intItem->calc();
    qDebug() << "Replaced " << midstr + op ;
    str = str.replace(midstr+op, QString::number(intItem->value, 'f', PRECISION));
    qDebug() << " to " << QString::number(intItem->value, 'f', PRECISION);
    delete intItem;
    return true;

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
    str = str.replace(expr+midstr+")", QString::number(intItem->value, 'f', PRECISION));
    qDebug() << " to " << QString::number(intItem->value, 'f', PRECISION);
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

