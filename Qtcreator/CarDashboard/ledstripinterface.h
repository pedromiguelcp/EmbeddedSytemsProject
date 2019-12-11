#ifndef LEDSTRIPINTERFACE_H
#define LEDSTRIPINTERFACE_H
#include <QObject>
#include <QString>
#include <QFile>

class LedStripInterface
{
public:
    LedStripInterface();
    void setDDriverPath(QString path);
    void setLedStripColor(QString id_color);

 protected:
     QString colorid;
     QFile ddriver;
};

#endif // LEDSTRIPINTERFACE_H
