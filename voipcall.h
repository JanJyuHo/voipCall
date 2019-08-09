#ifndef VOIPCALL_H
#define VOIPCALL_H

#include "voipaccount.h"

#include <pjsua2.hpp>
#include <QDebug>

namespace voip {

class voipCall : public pj::Call
{
public:
    explicit voipCall(pj::Account &acc, int call_Id = PJSUA_INVALID_ID);
    ~voipCall();
    virtual void onCallState(pj::OnCallStateParam &prm);
    virtual void onCallMediaState(pj::OnCallMediaStateParam &prm);
    virtual void onCallTransferRequest(pj::OnCallTransferRequestParam &prm);
    virtual void onCallReplaced(pj::OnCallReplacedParam &prm);

private:
    voipAccount *account;
    int callId;
    pj::AudioMediaPlayer *wav_player;
};

}


#endif // VOIPCALL_H
