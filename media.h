#ifndef MEDIA_H
#define MEDIA_H

#include <QString>
#include <QMediaPlayer>

class Audio{
public:
    Audio(QString path, int volume = 80);
    ~Audio(){}
    void play();
    void setVolume(int volume);
    int getVolume();
private:
    int volume;
    bool status;
    QMediaPlayer* audio;
};

#endif // MEDIA_H
