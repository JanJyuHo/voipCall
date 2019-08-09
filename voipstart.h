#ifndef VOIPSTART_H
#define VOIPSTART_H

#include <QObject>
#include <QList>
#include <pjsua2.hpp>
#include <QDebug>

namespace voip {

class voipAccount;

class voipStart : public QObject
{
    Q_OBJECT
public:
    explicit voipStart(QObject *parent = 0);
    Q_INVOKABLE void initAccount();
    Q_INVOKABLE void makeAudioCall();
    Q_INVOKABLE void hangup();
    Q_INVOKABLE void answer();
    Q_INVOKABLE void reject();

signals:
    void incomingCall(const QString &info);

private slots:
    void onIncomingCall(pj::OnIncomingCallParam *iprm);

private:
    voipAccount *acc;
    pj::Endpoint ep;
    QList<pj::OnIncomingCallParam*> activeCallParams;
};

}

#endif // VOIPSTART_H
