#include <QtTest>
#include "../Serial Readout/mainwindow.h"
#include <QString>


class Unit : public QObject
{
    Q_OBJECT

public:
    Unit();
    ~Unit();
    Ui::MainWindow *WindowObj;

private slots:
    void test_case1();

private:
//    MainWindow WindowObj;


};

Unit::Unit()
{
    WindowObj;
}

Unit::~Unit()
{

}

void Unit::test_case1()
{
    QString here="";

    WindowObj->updateProgressbar(here);
}

QTEST_APPLESS_MAIN(Unit)

#include "tst_unit.moc"
