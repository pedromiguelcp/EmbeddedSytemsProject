#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDir>

using namespace std;

class MusicPlayer
{
public:
    MusicPlayer(pid_t musicDaemonPID);

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

#endif // MUSICPLAYER_H
