#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

/**
 * @brief Main window contructor and Environment setup
 * @param parent QT created Object.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Generic Setup
    ui->setupUi(this);

    //Ardunio being the name as not to confuse what the serial is communicating with.
    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";
    serialBuffer="";

    //Device Configuration to allow for Vendor setup on specific boards.
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

    //Checks the current port is the requested board and configures the serial port.
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
    //Serial port must be closed before main obj deletion to prevent bugs on serial.
    if(arduino->isOpen()){
            arduino->close();}
    delete ui;

}
/**
 * @brief Serial reading from ardunio, reading as array into a buffer then split as to indicate where new inputs start.
 * buffer is split with
 */
void MainWindow::readSerial(){
    QByteArray serialIn = arduino->readAll(); //this saves current info from the arduino into ByteArray
    serialBuffer += QString::fromStdString(serialIn.toStdString()); //String is easiest way to lump this data.
    bufferSplit = serialBuffer.split("\n"); //Stringlist provides best supported array of string information

    if(bufferSplit.length()>=3){ //Adds a future component requirement to make sure buffer is filled.

        MainWindow::updatetext(bufferSplit[1]);
        MainWindow::updateProgressbar(bufferSplit[1]);
        serialBuffer=""; //resetting serial buffer.
    }
}

/**
 * @brief Function for updating the distance away text overlay on the progressbars.
 * @param reading - passed arg of distance.
 */
void MainWindow::updatetext(const QString reading)
{


}

/**
 * @brief Progress Bar updater function, changing progress bar size and colour to correspond to serial data.
 * @param data passed in string form of sensor output.
 * @details contains limits and debug code.
 */
void MainWindow::updateProgressbar(const QString valuein)
{
    //Clearing string list and string buffers.
    serialLineSplit.clear();
    leftSensorstr ="";
    rightSensorstr="";

    //using the passed parameter to add values into the stringlist.
    // spliting the serial line which contains left and right sensor data.
    serialLineSplit = valuein.split(" ");

    // assigning left and right to separate String vars
    leftSensorstr=serialLineSplit[0];
    rightSensorstr=serialLineSplit[1];

    //Cutting out pre-amble information from string.
    leftSensorstr.remove(0,5);
    rightSensorstr.remove(0,5);

    //Converting from strings into Doubles for high precision data.
    leftSensorint = leftSensorstr.toDouble();
    rightSensorint = rightSensorstr.toDouble();

    //Setting up the GUI Progress bars appearance and ranges
    ui->progressBar->setRange(0, 100);
    ui->progressBar_2->setRange(0,100);
    ui->progressBar->setInvertedAppearance(0);
    ui->progressBar_2->setInvertedAppearance(0);
    ui->progressBar->setStyleSheet(error);
    ui->progressBar_2->setStyleSheet(error);
    ui->progressBar->setTextVisible(1);
    ui->progressBar_2->setTextVisible(1);

    //imposing limits which catagories into different coloured bars. Alerting for danger.
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
    }}
    else {
        qDebug()<<"Error on read value";
    }



}
