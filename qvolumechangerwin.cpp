#include "qvolumechangerwin.h"
#include <QDebug>

// http://www.codeproject.com/Tips/233484/Change-Master-Volume-in-Visual-Cplusplus

QVolumeChangerWin::QVolumeChangerWin(QObject *parent) : QVolumeChanger(parent), endpointVolume_(0)
{
    HRESULT hr = 0;

    ::CoInitialize(0);

    IMMDeviceEnumerator *deviceEnumerator = 0;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), 0, CLSCTX_INPROC_SERVER,
                          __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = 0;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = 0;

    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
         CLSCTX_INPROC_SERVER, 0, (LPVOID *)&this->endpointVolume_);
    defaultDevice->Release();
    defaultDevice = 0;

    if(this->endpointVolume_ == 0) {
        return;
    }

    float vol_;
    BOOL mute_;
    this->endpointVolume_->GetMasterVolumeLevelScalar(&vol_);
    this->m_Volume = static_cast<qreal>(vol_);
    this->endpointVolume_->GetMute(&mute_);
    this->m_Mute = (mute_ == TRUE);

}

QVolumeChangerWin::~QVolumeChangerWin()
{
    if(this->endpointVolume_) {
        this->endpointVolume_->Release();
    }
    CoUninitialize();
}

void QVolumeChangerWin::setVolume(qreal volume)
{
    if(this->endpointVolume_ == 0) {
        return;
    }
    this->endpointVolume_->SetMasterVolumeLevelScalar(volume, 0);
    this->m_Volume = volume;
    emit this->volumeChanged();
}

qreal QVolumeChangerWin::volume() const
{
    return this->m_Volume;
}

void QVolumeChangerWin::setMute(bool mute)
{
    if(this->endpointVolume_ == 0) {
        return;
    }
    this->m_Mute = mute;
    this->endpointVolume_->SetMute(this->m_Mute ? TRUE : FALSE, 0);
    emit this->muteChanged();
}

bool QVolumeChangerWin::mute() const
{
    return this->m_Mute;
}
