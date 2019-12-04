#ifndef UARTSTM_H
#define UARTSTM_H
#include <QObject>
#include <QtDebug>
#include <QSerialPort>
#include <QByteArray>


class UartSTM : public QObject
{
    Q_OBJECT   

public:
    UartSTM();
    Q_INVOKABLE  void sendCommandSTM(QString command);
    QSerialPort *serial;

    void requestBrightness();
    void requestTemperature();

 /*************************************************************/

    int val() const {
        return m_val;
    }

    void UpdateCarInfo() {
        m_val += 5;
    }

/*************************************************************/

private slots:
    void readSerial();

private:
    int m_val=0;

    static const quint16 STM_product_id = 14155;
    static const quint16 STM_vendor_id = 1155;
    QString STM_port_name;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;
};

#endif // UARTSTM_H
