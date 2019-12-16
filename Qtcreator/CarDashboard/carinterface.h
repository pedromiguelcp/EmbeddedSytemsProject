#ifndef CARINTERFACE_H
#define CARINTERFACE_H
#include <QObject>
#include <QtDebug>
#include <QSerialPort>
#include <QByteArray>

struct carstatus_t{
    int speed;
    int rpm;
    int cartemperatue;
    int enginetemperature;
    int distancetoobjects;
    int brightness;
};


class CarInterface : public QObject
{
    Q_OBJECT
public:
    CarInterface();
    Q_INVOKABLE  void sendCommandSTM(QString command);
    QSerialPort *serial;

    void requestBrightness();
    void requestTemperature();

 /*************************************************************/

    int speed() const {
        return carinformations.speed;
    }
    int rpm() const {
        return carinformations.rpm;
    }
    int cartemperatue() const {
        return carinformations.cartemperatue;
    }
    int enginetemperature() const {
        return carinformations.enginetemperature;
    }
    int distancetoobjects() const {
        return carinformations.distancetoobjects;
    }
    int brightness() const {
        return carinformations.brightness;
    }

    void UpdateCarInfo() {
        carinformations.speed = 53;
        carinformations.rpm = 1250;
        carinformations.cartemperatue = 24;
        carinformations.enginetemperature = 45;
        carinformations.distancetoobjects += 5;
        carinformations.brightness = 66;
    }

    void processCarInfo(QString carinfo);

/*************************************************************/

private slots:
    void readSerial();

private:
    carstatus_t carinformations;
    int m_val=0;

    static const quint16 STM_product_id = 14155;// 8963
    static const quint16 STM_vendor_id = 1155;// 1659
    QString STM_port_name;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;

};

#endif // CARINTERFACE_H
