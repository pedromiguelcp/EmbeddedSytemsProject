#include "ddriver.h"
#include <QDebug>

DDriver::DDriver()
{
    this->ddriver.setFileName("/dev/LedStrips");
    setLedStripColor("0");
}

void DDriver::setLedStripColor(QString colorNumber)
{
    this->ddriver.open(QIODevice::WriteOnly);

    this->ddriver.write(colorNumber.toStdString().c_str(), colorNumber.size());

    this->ddriver.close();

    this->colorid.append(colorNumber.toStdString().c_str());
}

void DDriver::setDDriverPath(QString path)
{
    this->ddriver.setFileName(path);
}
