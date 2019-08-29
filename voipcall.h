#ifndef VOIPCALL_H
#define VOIPCALL_H

#include "voipaccount.h"

#include <QObject>
#include <pjsua2.hpp>
#include <QDebug>

namespace voip {

class voipCall : public QObject, public pj::Call
{
    Q_OBJECT
public:
    explicit voipCall(pj::Account &acc, int call_Id = PJSUA_INVALID_ID, QObject *parent = 0);
    ~voipCall();
    virtual void onCallState(pj::OnCallStateParam &prm);
    virtual void onCallMediaState(pj::OnCallMediaStateParam &prm);
    virtual void onCallTransferRequest(pj::OnCallTransferRequestParam &prm);
    virtual void onCallReplaced(pj::OnCallReplacedParam &prm);
    void setVolume(float volume);

signals:
    void callStateChanged(const QString &state);

private:
    voipAccount *account;
    int callId;
    pj::AudioMediaPlayer *wav_player;
    pj::AudioMedia *aud_med;
    pj::AudDevManager &mgr = pj::Endpoint::instance().audDevManager();
};

}


#endif // VOIPCALL_H
