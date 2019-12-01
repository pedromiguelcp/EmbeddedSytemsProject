#ifndef DDRIVER_H
#define DDRIVER_H
#include <QObject>
#include <QString>
#include <QFile>

class DDriver
{
public:
    DDriver();
    void setDDriverPath(QString path);
    void setLedStripColor(QString id_color);

 protected:
     QString colorid;
     QFile ddriver;
};

#endif // DDRIVER_H
