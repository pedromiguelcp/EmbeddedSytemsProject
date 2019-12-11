#include "carinterface.h"
#include <signal.h>
#include <string.h>
#include <QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QString>

CarInterface::CarInterface()
{
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  check if the product ID and the vendor ID match those of the STM
                if((STM_product_id == serialPortInfo.productIdentifier())
                        && (STM_vendor_id == serialPortInfo.vendorIdentifier())){
                    STM_port_name = serialPortInfo.portName();
                    break;
                }
            }
        }

    serial = new QSerialPort(STM_port_name);
    qDebug() << QString(STM_port_name);

    if (!serial->open(QIODevice::ReadWrite))
        qDebug() << QString("failed to connect: failed to open port %1").arg(serial->errorString());

    if (!serial->setBaudRate(QSerialPort::Baud115200))
        qDebug() << QString("failed to connect: failed to setBaudRate(115200) %1").arg(serial->errorString());

    if (!serial->setStopBits(QSerialPort::OneStop))
        qDebug() << QString("failed to connect: failed to set QSerialPort::OneStop %1").arg(serial->errorString());

    if (!serial->setParity(QSerialPort::NoParity))
        qDebug() << QString("failed to connect: failed to set QSerialPort::NoParity %1").arg(serial->errorString());

    if (!serial->setDataBits(QSerialPort::Data8))
        qDebug() << QString("failed to connect: failed to set QSerialPort::Data8 %1").arg(serial->errorString());


    if (!serial->isOpen())
        qDebug() << QString("Device is not open!");
    else
        qDebug() << QString("Device is open!");

    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(readSerial()));
}

void CarInterface::sendCommandSTM(QString command)
{
    qDebug() << "Command for STM: " << command;
    if (serial->isOpen())
        serial->close();
    serial->open(QIODevice::ReadWrite);
    serial->write(command.toUtf8());
}

void CarInterface::readSerial()
{
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     * 1(v96r2692e0\r)
     * s(para)
     * 3(b70\r)
     * 4(t20\r)
     */
    serialData = serial->readAll();
    serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
    serialData.clear();
    int sizebuff = serialBuffer.size();

    if(serialBuffer[sizebuff - 1] == "\r")
    {
        //serialBuffer[serialBuffer.length() -1] = '\0';

        processCarInfo(serialBuffer);
        serialBuffer.clear();
    }
}

void CarInterface::requestBrightness()
{
    sendCommandSTM("1");
}

void CarInterface::requestTemperature()
{
    sendCommandSTM("4");
}

void CarInterface::processCarInfo(QString carinfo)
{
    qDebug() << "Information to be parsed: " << carinfo;
    carinfo.chop(1);
    if(carinfo[0] == "v")
    {
        int rpmindex = carinfo.indexOf("r");
        int enginetempindex = carinfo.indexOf("e");

        carinformations.speed = carinfo.mid(1, (rpmindex - 1)).toInt();
        carinformations.rpm = carinfo.mid(rpmindex + 1, (enginetempindex - rpmindex - 1)).toInt();
        carinformations.enginetemperature = carinfo.mid(enginetempindex + 1).toInt();

        /*qDebug() << "New speed: " << carinformations.speed;
        qDebug() << "New rpm: " << carinformations.rpm;
        qDebug() << "New enginetemperature: " << carinformations.enginetemperature;*/
    }
    else if(carinfo[0] == "b")
    {
        carinformations.brightness = carinfo.mid(1).toInt();
        //qDebug() << "New bright: " << carinformations.brightness;
    }
    else if(carinfo[0] == "t")
    {
        carinformations.cartemperatue = carinfo.mid(1).toInt();
        //qDebug() << "New car temperature: " << carinformations.cartemperatue;
    }
}

