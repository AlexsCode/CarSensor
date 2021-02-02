#include <QtTest>

// add necessary includes here

class Unit : public QObject
{
    Q_OBJECT

public:
    Unit();
    ~Unit();

private slots:
    void test_case1();

};

Unit::Unit()
{

}

Unit::~Unit()
{

}

void Unit::test_case1()
{

}

QTEST_APPLESS_MAIN(Unit)

#include "tst_unit.moc"
