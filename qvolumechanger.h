#ifndef QVOLUMECHANGER_H
#define QVOLUMECHANGER_H

#include <QObject>

class QVolumeChanger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)

protected:
    qreal m_Volume;
    bool m_Mute;

public:
    explicit QVolumeChanger(QObject *parent = 0);
    explicit QVolumeChanger(const QVolumeChanger &other) : m_Volume(other.m_Volume), m_Mute(other.m_Mute) {}

    virtual void setVolume(qreal volume);
    virtual qreal volume() const;
    virtual void setMute(bool mute);
    virtual bool mute() const;

signals:
    void volumeChanged();
    void muteChanged();

public slots:

};

Q_DECLARE_METATYPE(QVolumeChanger)

#endif // QVOLUMECHANGER_H
