#ifndef VOIPSTART_H
#define VOIPSTART_H

#include <QObject>
#include <QList>
#include <pjsua2.hpp>
#include <QDebug>

namespace voip {

class voipAccount;

class voipCall;

class voipStart : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit voipStart(QObject *parent = 0);
    Q_INVOKABLE void initAccount();
    Q_INVOKABLE void makeAudioCall();
    Q_INVOKABLE void hangup();
    Q_INVOKABLE void answer();
    Q_INVOKABLE void reject();
    Q_INVOKABLE void setVolume(float volume);
    QString state() const;
    void setState(const QString &state);

signals:
    void incomingCall(const QString &info);
    void stateChanged(const QString &state);

private slots:
    void onIncomingCall(pj::OnIncomingCallParam *iprm);

private:
    QString callState;
    voipAccount *acc;
    voipCall *call;
    pj::Endpoint ep;
    QList<pj::OnIncomingCallParam*> activeCallParams;
};

}

#endif // VOIPSTART_H
