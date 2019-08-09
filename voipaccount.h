#ifndef VOIPACCOUNT_H
#define VOIPACCOUNT_H

#include <QObject>
#include <pjsua2.hpp>
#include <QDebug>

namespace voip {
class voipAccount : public QObject, public pj::Account
{
    Q_OBJECT
public:
    explicit voipAccount(QObject *parent = 0);
    ~voipAccount();

    void registerAsClient();

    pj::Call* getCall(int callId);
    bool removeCall(pj::Call *call);

    virtual void onRegState(pj::OnRegStateParam &prm);
    virtual void onIncomingCall(pj::OnIncomingCallParam &iprm);

public:
    QList<pj::Call*> calls;

signals:
    void incomingCall(pj::OnIncomingCallParam *iprm);
};
}

//Q_DECLARE_METATYPE(pj::OnIncomingCallParam*)
#endif // VOIPACCOUNT_H
