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

    void changeMusicVolume(int volume);

    int getMusicVolume();

    void nextSong();

    void previousSong();

private:
    QDir usbpath;
    QStringList musicslist;
    QString currentsong;
    pid_t musicDaemonPID;
    int musicVolume;
    int musicindex;
};

#endif // MUSIC_H
