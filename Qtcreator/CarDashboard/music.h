#ifndef MUSIC_H
#define MUSIC_H
#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDir>

using namespace std;

class Music
{
public:
    Music(pid_t musicDaemonPID);

    Q_INVOKABLE void setnewSong(QString song);

    void setNewstorageDevie(QString newDevice);

    QString getSongs();

    QString getcurrentSong();

    void pauseCurrentSong();

    void resumeCurrentSong();

private:
    QDir usbpath;
    QString currentsong;
    pid_t musicDaemonPID;
};

#endif // MUSIC_H
