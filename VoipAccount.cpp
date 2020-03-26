#include "VoipAccount.h"
#include "VoipCall.h"

#include <QDebug>

namespace voip {

VoipAccount::VoipAccount(QObject *parent)
    : QObject{parent}
{

}

VoipAccount::~VoipAccount()
{
    // Remove all calls
    qDeleteAll(this->calls);
}

void VoipAccount::registerAsClient()
{
    pj::AccountConfig acc_cfg;
    acc_cfg.idUri = "sip:1000@192.168.80.128;transport=udp";
    acc_cfg.regConfig.registrarUri = "sip:192.168.80.128;transport=udp";
    acc_cfg.sipConfig.authCreds.push_back(pj::AuthCredInfo("digest","*", "1000" ,0,"1234"));
//    acc_cfg.natConfig.iceEnabled = true;
//    acc_cfg.natConfig.turnEnabled = true;
//    acc_cfg.natConfig.turnConnType = PJ_TURN_TP_TCP;
//    acc_cfg.natConfig.turnServer = "47.91.217.14:3478";
//    acc_cfg.natConfig.turnUserName = "enigma";
//    acc_cfg.natConfig.turnPassword = "123a2487fa989ebf";
    try {
        this->create(acc_cfg);
    } catch(...) {
        qDebug() << "Adding account failed" << endl;
    }
}

pj::Call *VoipAccount::getCall(int callId)
{
    for (int i = 0; i < this->calls.length(); i++) {
        if (this->calls.at(i)->getId() == callId) {
            return this->calls.at(i);
        }
    }
    return nullptr;
}

bool VoipAccount::removeCall(pj::Call *call)
{
    return this->calls.removeOne(call);
}

void VoipAccount::onRegState(pj::OnRegStateParam &prm)
{
    qDebug() << "\n==";
    pj::AccountInfo ai = getInfo();
    if (ai.regIsActive) {
        qDebug() << "*** Register: code=" << prm.code << endl;
    } else {
        qDebug() << "*** Unregister: code=" << prm.code << endl;
    }
}

void VoipAccount::onIncomingCall(pj::OnIncomingCallParam &iprm)
{
    pj::Call *call = new VoipCall(*this, iprm.callId);
    this->calls.append(call);

    qDebug() << "\n==";
    qDebug() << "*** incoming call"<< endl;

    emit incomingCall(&iprm);
    pj::CallOpParam callOpParam;
    callOpParam.statusCode = PJSIP_SC_OK;
    call->answer(callOpParam);
}


}
