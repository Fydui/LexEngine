#include "media.h"


Audio::Audio(QString path, int volume)
{
    audio  = new QMediaPlayer;
    audio->setMedia(QUrl::fromLocalFile(path));
    setVolume(volume);
    this->status = status;
    play();
}

void Audio::play()
{
    audio->play();
}

void Audio::setVolume(int volume)
{
    audio->setVolume(volume);
    this->volume = volume;
}

int Audio::getVolume()
{
   return volume;
}

