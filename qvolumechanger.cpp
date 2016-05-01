#include "qvolumechanger.h"
#include <QDebug>

QVolumeChanger::QVolumeChanger(QObject *parent) : QObject(parent)
{

}

qreal QVolumeChanger::volume() const
{
    return this->m_Volume;
}

void QVolumeChanger::setVolume(qreal volume)
{
    qDebug() << "volume change to" << volume;
    this->m_Volume = volume;
    emit this->volumeChanged();
}

bool QVolumeChanger::mute() const
{
    return this->m_Mute;
}

void QVolumeChanger::setMute(bool mute)
{
    qDebug() << "mute state changed to" << mute;
    this->m_Mute = mute;
    emit this->muteChanged();
}
