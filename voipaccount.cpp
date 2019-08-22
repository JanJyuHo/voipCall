#include "voipaccount.h"
#include "voipcall.h"

#include <QDebug>

namespace voip {

voipAccount::voipAccount(QObject *parent)
    : QObject{parent}
{

}

voipAccount::~voipAccount()
{
    // Remove all calls
    qDeleteAll(this->calls);
}

void voipAccount::registerAsClient()
{
    pj::AccountConfig acc_cfg;
    acc_cfg.idUri = "sip:1002@10.0.0.160";
    acc_cfg.regConfig.registrarUri = "sip:10.0.0.160";
    acc_cfg.sipConfig.authCreds.push_back(pj::AuthCredInfo("digest","*", "1002" ,0,"1234"));
    try {
        this->create(acc_cfg);
    } catch(...) {
        qDebug() << "Adding account failed" << endl;
    }
}

pj::Call *voipAccount::getCall(int callId)
{
    for (int i = 0; i < this->calls.length(); i++) {
        if (this->calls.at(i)->getId() == callId) {
            return this->calls.at(i);
        }
    }
    return nullptr;
}

bool voipAccount::removeCall(pj::Call *call)
{
    return this->calls.removeOne(call);
}

void voipAccount::onRegState(pj::OnRegStateParam &prm)
{
    qDebug() << "\n==";
    pj::AccountInfo ai = getInfo();
    if (ai.regIsActive) {
        qDebug() << "*** Register: code=" << prm.code << endl;
    } else {
        qDebug() << "*** Unregister: code=" << prm.code << endl;
    }
}

void voipAccount::onIncomingCall(pj::OnIncomingCallParam &iprm)
{
    pj::Call *call = new voipCall(*this, iprm.callId);
    this->calls.append(call);

    qDebug() << "\n==";
    qDebug() << "*** incoming call"<< endl;

    emit incomingCall(&iprm);
}


}
