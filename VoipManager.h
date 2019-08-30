#ifndef VOIPMANAGER_H
#define VOIPMANAGER_H

#include <QObject>
#include <QList>
#include <pjsua2.hpp>
#include <QDebug>

namespace voip {

class VoipAccount;

class VoipCall;

class VoipManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit VoipManager(QObject *parent = 0);
    ~VoipManager();
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
    void onCallStateChanged(const QString &state);

private:
    QString callState;
    VoipAccount *acc;
    pj::Endpoint ep;
    QList<pj::OnIncomingCallParam*> activeCallParams;
};

}

#endif // VOIPMANAGER_H
