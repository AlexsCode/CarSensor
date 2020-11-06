#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readSerial();
    void updatetext(const QString);
    void updateProgressbar(const QString);

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;

    //Arduino info
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
    QString ReadData;
    QByteArray serialIn;
    QString serialBuffer;
    QStringList bufferSplit;
    QStringList serialLineSplit;
    QString rightSensorstr;
    QString leftSensorstr;
    double leftSensorint;
    double rightSensorint;
    double invertedleftSensorint;
    double invertedrightSensorint;
    QString danger = "QProgressBar::chunk {background: red }";
    QString safe = "QProgressBar::chunk { background: green} ";
    QString semidanger ="QProgressBar::chunk{ background: orange}";
    QString error = "QProgressBar::chunk { background: blue}; ";

};

#endif // MAINWINDOW_H
