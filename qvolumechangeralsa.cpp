#include "qvolumechangeralsa.h"
#include <QDebug>

// http://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code

const char *QVolumeChangerAlsa::CARD = "default";
const char *QVolumeChangerAlsa::SELEM_NAME = "Master";


static long GetAlsaVolume(qreal vol, long min, long max)
{
    return (max - min) * vol + min;
}

static qreal GetQtVolume(long val, long min, long max)
{
    return static_cast<qreal>(val - min) / static_cast<qreal>(max - min);
}

QVolumeChangerAlsa::QVolumeChangerAlsa(QObject *parent) : QVolumeChanger(parent), handle_(0), elem_(0)
{
    if(snd_mixer_open(&this->handle_, 0) < 0) {
        qDebug() << "snd_mixer_open error";
        goto error;
    }

    if(snd_mixer_attach(this->handle_, this->CARD)) {
        qDebug() << "snd_mixer_attach error";
        goto error;
    }

    if(snd_mixer_selem_register(this->handle_, NULL, NULL) < 0) {
        qDebug() << "snd_mixer_selem_register error";
        goto error;
    }

    if(snd_mixer_load(this->handle_) < 0) {
        qDebug() << "snd_mixer_load error";
        goto error;
    }

    snd_mixer_selem_id_t *id;
    snd_mixer_selem_id_alloca(&id);
    snd_mixer_selem_id_set_index(id, 0);
    snd_mixer_selem_id_set_name(id, this->SELEM_NAME);

    if((this->elem_ = snd_mixer_find_selem(this->handle_, id)) == 0) {
        qDebug() << "snd_mixer_find_selem error";
        goto error;
    }

    snd_mixer_selem_get_playback_volume_range(this->elem_, &this->min_, &this->max_);

    long val;
    if(snd_mixer_selem_get_playback_volume(this->elem_, SND_MIXER_SCHN_MONO, &val) < 0) {
        qDebug() << "snd_mixer_selem_get_playback_volume error";
        this->m_Volume = 0;
        this->m_Mute = true;
    }
    else {
        this->m_Volume = GetQtVolume(val, this->min_, this->max_);
        this->m_Mute = (val == this->min_);
    }

    return;

error:
    if(this->handle_) {
        snd_mixer_close(this->handle_);
        this->handle_ = 0;
    }
    return;
}

QVolumeChangerAlsa::~QVolumeChangerAlsa()
{
    if(this->handle_) {
        snd_mixer_close(this->handle_);
        this->handle_ = 0;
    }
}

void QVolumeChangerAlsa::setVolume(qreal volume)
{
    if(this->handle_ == 0) {
        return;
    }
    this->m_Volume = volume;
    snd_mixer_selem_set_playback_volume_all(this->elem_, GetAlsaVolume(this->m_Volume, this->min_, this->max_));
    emit this->volumeChanged();
}

qreal QVolumeChangerAlsa::volume() const
{
    return this->m_Volume;
}

void QVolumeChangerAlsa::setMute(bool mute)
{
    if(this->handle_ == 0) {
        return;
    }
    this->m_Mute = mute;
    snd_mixer_selem_set_playback_volume_all(this->elem_, this->m_Mute ? this->min_ : GetAlsaVolume(this->m_Volume, this->min_, this->max_));
    emit this->muteChanged();
}

bool QVolumeChangerAlsa::mute() const
{
    return this->m_Mute;
}
