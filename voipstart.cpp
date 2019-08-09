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
    pj::Call *call = new voipCall(*acc);
    this->acc->calls.append(call);

    pj::CallOpParam p(true);
    p.opt.audioCount = 1;
    p.opt.videoCount = 0;
    try {
        call->makeCall("sip:1002@192.168.56.129", p);
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
    pj::Call *call = acc->calls[0];

    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_OK;
    call->answer(callOpParam);
}

void voipStart::reject()
{
    pj::Call *call = acc->calls[0];

    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_DECLINE;
    call->hangup(callOpParam);
    call = nullptr;
}

void voipStart::onIncomingCall(pj::OnIncomingCallParam *iprm)
{
    // append to call active calls
    activeCallParams.append(iprm);
    qDebug() << "Receiving signals succeed!" << endl;
}


}
