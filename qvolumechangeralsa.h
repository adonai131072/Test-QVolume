#ifndef QVOLUMECHANGERALSA_H
#define QVOLUMECHANGERALSA_H

#include "qvolumechanger.h"
#include <alsa/asoundlib.h>

class QVolumeChangerAlsa : public QVolumeChanger
{
    Q_OBJECT

    snd_mixer_t *handle_;
    snd_mixer_elem_t *elem_;
    long min_;
    long max_;

    static const char *CARD;
    static const char *SELEM_NAME;

public:

    explicit QVolumeChangerAlsa(QObject *parent = 0);
    explicit QVolumeChangerAlsa(const QVolumeChangerAlsa &other) : QVolumeChanger(other) {}

    ~QVolumeChangerAlsa();

    virtual void setVolume(qreal volume);
    virtual qreal volume() const;
    virtual void setMute(bool mute);
    virtual bool mute() const;
};

Q_DECLARE_METATYPE(QVolumeChangerAlsa)

#endif // QVOLUMECHANGERALSA_H
