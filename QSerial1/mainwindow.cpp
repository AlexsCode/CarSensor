#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";
    serialBuffer="";

    qDebug() << "Number of Availible Ports: "<< QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
            if(serialPortInfo.hasVendorIdentifier()){
                qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
            }
            qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
            if(serialPortInfo.hasProductIdentifier()){
                qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
            }}
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
                if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                    if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                        arduino_port_name = serialPortInfo.portName();
                        arduino_is_available = true;
                    }
                }
            }
        }

    if(arduino_is_available){
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()),this,SLOT(readSerial()));
    }
    else {
        qDebug()<<"port error, no arduino found";
    }

}//end setup

MainWindow::~MainWindow()
{
    if(arduino->isOpen()){
            arduino->close();}
    delete ui;

}

void MainWindow::readSerial(){
    QByteArray serialIn = arduino->readAll();
    serialBuffer += QString::fromStdString(serialIn.toStdString());
    //qDebug()<<serialBuffer;
    bufferSplit = serialBuffer.split("\n");
    if(bufferSplit.length()>=3){
        qDebug()<<bufferSplit[1];
        //static QString serialline2 = bufferSplit[1];
        MainWindow::updatetext(bufferSplit[1]);
        MainWindow::updateProgressbar(bufferSplit[1]);
        serialBuffer="";
    }
}

void MainWindow::updatetext(const QString reading)
{


}

void MainWindow::updateProgressbar(const QString valuein)
{   serialLineSplit.clear();
    leftSensorstr ="";
    rightSensorstr="";
    serialLineSplit = valuein.split(" "); // spliting the serial line
    leftSensorstr=serialLineSplit[0]; // assigning left and right to separate String var
    rightSensorstr=serialLineSplit[1];
    leftSensorstr.remove(0,5);
    rightSensorstr.remove(0,5);
    leftSensorint = leftSensorstr.toDouble();
    rightSensorint = rightSensorstr.toDouble();
    //QString debug_rightSensorint =QString::number(rightSensorint);
   // ui->textEdit->setText(debug_rightSensorint);
    ui->progressBar->setRange(0, 100);
    ui->progressBar_2->setRange(0,100);
    ui->progressBar->setInvertedAppearance(0);
    ui->progressBar_2->setInvertedAppearance(0);
    ui->progressBar->setStyleSheet(error);
    ui->progressBar_2->setStyleSheet(error);
    ui->progressBar->setTextVisible(1);
    ui->progressBar_2->setTextVisible(1);
    //inverter
    //invertedrightSensorint=100-rightSensorint;
    //invertedleftSensorint=100-leftSensorint;

    if(rightSensorint>10&&rightSensorint<500){
        if(leftSensorint>10&&leftSensorint<500){

            ui->progressBar->setValue(leftSensorint);
            ui->progressBar_2->setValue(rightSensorint);

            if(leftSensorint<30){
                ui->progressBar->setStyleSheet(danger);}
            else if (leftSensorint<50&&leftSensorint>=30) {
                ui->progressBar->setStyleSheet(semidanger);
            }
            else if (leftSensorint>50) {
                ui->progressBar->setStyleSheet(safe);
            }
            if(rightSensorint<30){
                ui->progressBar_2->setStyleSheet(danger);}

            else if (rightSensorint<50&&leftSensorint>=30) {
                ui->progressBar_2->setStyleSheet(semidanger);
            }
            else if (rightSensorint>50) {
                ui->progressBar_2->setStyleSheet(safe);
            }

             qDebug()<<"Graph Reset";
    }}
    else {
        qDebug()<<"Error on read value";
    }



}
