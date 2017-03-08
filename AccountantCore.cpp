#include <AccountantCore.h>
#include <QList>
#include <QMessageBox>

AccountantCore::AccountantCore()
{

}

double AccountantCore::calcCurrentCapital(QList<double> &buyPriceArr)
{
    double cur_stock;
    double stock_total = 0;

    try {

     if(!buyPriceArr.isEmpty()) {
         foreach(cur_stock, buyPriceArr) {
             stock_total += cur_stock;
         }
     }

    } catch (...) {
        err_handler("Something went wrong in calcCurrentCapital!");
        return -1;
    }

    return stock_total;
}


double AccountantCore::calcRiskPercentPerTrade(double totalPrice, double numStocks, double stopLoss) {
    double riskp;
    try {
       riskp = 100 - (((totalPrice - (numStocks * stopLoss))/totalPrice) * 100);
    } catch(...) {
        err_handler("Something went wrong in calcRiskPercent(single)");
        return -1;
    }

    return riskp;
}

QList<double> AccountantCore::calcRiskPercentPerTrade(QList<double>&totalPrice, QList<double>&numStocks, QList<double>&stopLoss) {
    QList<double> riskp;
    double cur_calc;
    try {
        for(int i=0;i<totalPrice.size();i++) {
            cur_calc = 100 - (((totalPrice.at(i) - (numStocks.at(i) * stopLoss.at(i)))/totalPrice.at(i)) * 100);
            riskp.append(cur_calc);
        }
    } catch(...) {
        err_handler("Something went wrong in calcRiskPercent(multiple)");
    }

    return riskp;
}


double AccountantCore::calcCapitalRiskPerecent(QList<double>&numStocks, QList<double>&stopLoss) {
    double total_capital = getTotalCapital();
    double risked_capital = 0;
    double risked_capital_per;

    try {
        for(int i=0;i<numStocks.size();i++) {
            risked_capital += numStocks.at(i)*stopLoss.at(i);
        }

        risked_capital_per = (risked_capital/total_capital) * 100;

    } catch(...) {
        err_handler("Something went wrong in calcCapitalRiskPercent");
        return -1;
    }

    return risked_capital_per;

}

double AccountantCore::getTotalCapital() {
    double cur_capital = 20000;
    return cur_capital;
}

double AccountantCore::getFreeCapital(QList<double>&totalPrice) {
    double total_capital = getTotalCapital();
    double running_capital = 0;

    try {
        for(int i=0;i<totalPrice.size();i++) {
            running_capital += totalPrice.at(i);
        }

    } catch(...) {
        err_handler("Something went wrong in getFreeCapital");
        return -1;
    }

    return(total_capital-running_capital);

}


void AccountantCore::err_handler(QString errMsg, QString errCode) {
    flashMsg(errCode + ":" + errMsg);
}

void AccountantCore::flashMsg(QString displayMsg) {
   QMessageBox Msgbox;
        Msgbox.setText(displayMsg);
        Msgbox.exec();
}
