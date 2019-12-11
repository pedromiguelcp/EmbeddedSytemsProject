#include "ledstripinterface.h"
#include <QDebug>


LedStripInterface::LedStripInterface()
{
    this->ddriver.setFileName("/dev/LedStrips");
    setLedStripColor("0");
}

void LedStripInterface::setLedStripColor(QString colorNumber)
{
    this->ddriver.open(QIODevice::WriteOnly);

    this->ddriver.write(colorNumber.toStdString().c_str(), colorNumber.size());

    this->ddriver.close();

    this->colorid.append(colorNumber.toStdString().c_str());
}

void LedStripInterface::setDDriverPath(QString path)
{
    this->ddriver.setFileName(path);
}
