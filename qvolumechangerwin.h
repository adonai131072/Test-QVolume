#ifndef QVOLUMECHANGERWIN_H
#define QVOLUMECHANGERWIN_H

#include "qvolumechanger.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>

class QVolumeChangerWin : public QVolumeChanger
{
    Q_OBJECT

    IAudioEndpointVolume *endpointVolume_;
public:

    explicit QVolumeChangerWin(QObject *parent = 0);
    explicit QVolumeChangerWin(const QVolumeChangerWin &other) : QVolumeChanger(other) {}

    ~QVolumeChangerWin();

    virtual void setVolume(qreal volume);
    virtual qreal volume() const;
    virtual void setMute(bool mute);
    virtual bool mute() const;
};

Q_DECLARE_METATYPE(QVolumeChangerWin)

#endif // QVOLUMECHANGERWIN_H
