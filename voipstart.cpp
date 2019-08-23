#include "voipstart.h"
#include "voipaccount.h"
#include "voipcall.h"

namespace voip {

voipStart::voipStart(QObject *parent) : QObject(parent), acc(new voipAccount(this))
{
    // Endpoint init
    try {
        ep.libCreate();
    } catch (pj::Error &err) {
        // FIXME: handle this
        Q_UNUSED(err);
    }
    pj::EpConfig ep_config;
    ep_config.logConfig.level = 5;
    ep_config.uaConfig.maxCalls = 1;
    ep.libInit(ep_config);

    // Transport init
    pj::TransportConfig trans_config;
    trans_config.port = 5060;
    ep.transportCreate(PJSIP_TRANSPORT_UDP, trans_config);

    // Start library
    ep.libStart();
    qDebug() << "PJSUA started!" << endl;

    connect(acc, SIGNAL(incomingCall(pj::OnIncomingCallParam*)), this, SLOT(onIncomingCall(pj::OnIncomingCallParam*)));
}

void voipStart::initAccount()
{
    acc->registerAsClient();
}

void voipStart::makeAudioCall()
{
    pj::Call *newCall = new voipCall(*acc);
    this->acc->calls.append(newCall);

    pj::CallOpParam p(true);
    p.opt.audioCount = 1;
    p.opt.videoCount = 0;
    try {
        newCall->makeCall("sip:1000@10.0.0.160", p);
    } catch(...) {
        qDebug() << "*** Making call failed" << endl;
    }
}

void voipStart::hangup()
{
    ep.hangupAllCalls();
    qDebug() << "*** Hanging up the call" << endl;
}

void voipStart::answer()
{
    pj::Call *newCall = acc->calls[0];

    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_OK;
    newCall->answer(callOpParam);
}

void voipStart::reject()
{
    pj::Call *newCall = acc->calls[0];

    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_DECLINE;
    newCall->hangup(callOpParam);
    newCall = nullptr;
}

void voipStart::setVolume(float volume)
{
    if (acc->calls.count() != 0){
        for (unsigned i = 0; i < acc->calls.count(); i++){
            voipCall *newCall = (voipCall *)acc->calls[i];
            newCall->setVolume(volume);
        }
    }
}

void voipStart::onIncomingCall(pj::OnIncomingCallParam *iprm)
{
    // append to call active calls
    activeCallParams.append(iprm);
    qDebug() << "Receiving signals succeed!" << endl;
}


}
